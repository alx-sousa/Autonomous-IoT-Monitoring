#include <WiFi.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#include <esp_now.h>
#include <esp_wifi.h>
#include <HardwareSerial.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "secrets.h"

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID_WIFI, PASS_WIFI);

// Arduino IoT Cloud mirror variables.
// The alarm decision itself is performed locally on the receiver.
float rssiArea;
String estadoPaciente;
bool alarmaCritica;
bool modoPaseoCloud;
bool pacienteLejos;

// OLED configuration.
// Operator-facing V1 messages remain in Spanish to preserve historical behavior.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Non-blocking lifetime control for temporary OLED messages.
unsigned long oledTiempo = 0;
unsigned long oledDuracion = 0;
bool oledActivo = false;

void oledMensaje(const char* txt, unsigned long duracion = 5000) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);
  display.println(txt);
  display.display();

  oledTiempo = millis();
  oledDuracion = duracion;
  oledActivo = (duracion > 0);
}

// RDM6300 RFID reader on UART1.
// The reader frame is validated with the checksum below; this V1 source does
// not implement an authorized-UID allowlist.
HardwareSerial RFID(1);
#define RFID_RX 17
String frame = "";
unsigned long lastRFID = 0;
const int BLOQUEO_RFID = 1500;

// V1 GPIO assignments.
#define BUZZER_PIN 19
#define LED_BLUE 14
#define LED_GREEN 15
#define LED_RED 18

// RSSI state thresholds.
// Enter LEJOS at or below -66 dBm and return to CERCA at or above -59 dBm.
// The separated thresholds implement hysteresis and reduce state oscillation.
const int PUNTO_ALERTA = -66;
const int PUNTO_SALIDA = -59;

// EMA state. alpha = 0.20 weights the newest RSSI sample by 20%.
float rssiFiltrado = -40.0;
float alpha = 0.2;

enum Estado { CERCA, LEJOS };
Estado estadoActual = CERCA;

// Historical V1 state flags.
// alarmaSilenciada is retained for source traceability but is not used by the
// current control path.
bool alarmaSilenciada = false;
bool modoPaseo = false;
int contadorLejos = 0;

// Important V1 behavior: contadorLejos advances in loop() iterations, not only
// when a fresh ESP-NOW frame arrives. See docs/firmware-review.md.
const int CONFIRMACION_LEJOS = 5;

// Critical-distance threshold used by the published V1 alarm logic.
const int UMBRAL_CRITICO = -84;

// Retained from the V1 source; currently not referenced by the control logic.
const int UMBRAL_CRITICO_SALIDA = -80;

// Historical timer/output variables. These are retained unchanged even though
// the current published loop does not use the blue-blink state.
unsigned long tiempoAzul = 0;
bool azulEncendido = false;
bool rojoActivo = false;

// Register read-only cloud properties. Cloud telemetry is secondary to local
// receiver-side decision making.
void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);

  ArduinoCloud.addProperty(rssiArea, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(estadoPaciente, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(alarmaCritica, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(modoPaseoCloud, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(pacienteLejos, READ, 1 * SECONDS, NULL);
}

// Validate the 12-character RDM6300 payload by XORing the first five bytes and
// comparing the result with the final checksum byte.
bool validarChecksum(String data) {
  byte checksum = 0;

  for (int i = 0; i < 10; i += 2) {
    byte value = strtol(data.substring(i, i + 2).c_str(), NULL, 16);
    checksum ^= value;
  }

  byte recibido = strtol(data.substring(10, 12).c_str(), NULL, 16);
  return checksum == recibido;
}

// Parse one RFID frame and toggle walking mode after a valid read.
// BLOQUEO_RFID prevents immediate repeated toggles from the same presentation.
void leerRFID() {
  while (RFID.available()) {
    char c = RFID.read();

    if (c == 0x02) {
      frame = "";
      return;
    }

    if (c == 0x03) {
      if (frame.length() == 12 && validarChecksum(frame)) {
        if (millis() - lastRFID > BLOQUEO_RFID) {
          oledMensaje("TARJETA DETECTADA", 1000);

          digitalWrite(BUZZER_PIN, HIGH);
          delay(160);
          digitalWrite(BUZZER_PIN, LOW);

          modoPaseo = !modoPaseo;

          if (modoPaseo) {
            oledMensaje("PASEO ACTIVADO", 5000);
          } else {
            oledMensaje("PASEO DESACTIVADO", 5000);
          }

          lastRFID = millis();
        }
      } else {
        oledMensaje("ERROR RFID", 5000);
      }

      frame = "";
      return;
    }

    frame += c;
  }
}

// ESP-NOW receive callback.
// Only the received-frame RSSI is consumed here; the payload is not used for
// authentication or application data in this V1 implementation.
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  if (info && info->rx_ctrl) {
    int rssiReal = info->rx_ctrl->rssi;
    rssiFiltrado = (rssiReal * alpha) + (rssiFiltrado * (1.0 - alpha));
  }
}

void setup() {
  Serial.begin(115200);

  // Start cloud telemetry before configuring local peripherals, matching the
  // historical V1 startup sequence.
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // V1 I2C bus: SDA GPIO7, SCL GPIO6.
  Wire.begin(7, 6);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  oledMensaje("INICIANDO");

  // RDM6300 receives at 9600 baud on GPIO17; TX is not used.
  RFID.begin(9600, SERIAL_8N1, RFID_RX, -1);

  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Historical V1 idle LED levels.
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);

  // ESP-NOW starts on channel 1. The transmitter sweeps channels 1..11.
  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ERROR ESPNOW");
  }

  esp_now_register_recv_cb(OnDataRecv);

  oledMensaje("SISTEMA ACTIVADO");
}

void loop() {
  // V1 runs the cloud handler on every loop iteration.
  ArduinoCloud.update();

  unsigned long ahora = millis();

  // Clear only temporary OLED messages; duration 0 leaves a message latched.
  if (oledActivo && (ahora - oledTiempo >= oledDuracion)) {
    display.clearDisplay();
    display.display();
    oledActivo = false;
  }

  leerRFID();

  // Two-state RSSI machine with hysteresis.
  if (estadoActual == CERCA) {
    if (rssiFiltrado <= PUNTO_ALERTA) {
      contadorLejos++;
    } else {
      contadorLejos = 0;
    }

    if (contadorLejos >= CONFIRMACION_LEJOS) {
      estadoActual = LEJOS;
      contadorLejos = 0;
      oledMensaje("PACIENTE LEJOS", 0);
    }
  } else {
    if (rssiFiltrado >= PUNTO_SALIDA) {
      estadoActual = CERCA;
      modoPaseo = false;
      oledMensaje("PACIENTE CERCA", 5000);
    }
  }

  // Critical local alarm is active only while the patient is LEJOS and walking
  // mode has not been enabled by RFID.
  if (estadoActual == LEJOS && !modoPaseo) {
    if (rssiFiltrado <= UMBRAL_CRITICO) {
      digitalWrite(LED_RED, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      oledMensaje("DISTANCIA CRITICA", 0);
    } else {
      digitalWrite(LED_RED, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  // Mirror local state to Arduino IoT Cloud.
  rssiArea = rssiFiltrado;
  pacienteLejos = (estadoActual == LEJOS);
  modoPaseoCloud = modoPaseo;
  alarmaCritica = (rssiFiltrado <= UMBRAL_CRITICO && estadoActual == LEJOS && !modoPaseo);

  if (estadoActual == LEJOS) {
    estadoPaciente = "LEJOS";
  } else {
    estadoPaciente = "CERCA";
  }

  Serial.print("RSSI: ");
  Serial.println(rssiFiltrado);

  // Historical V1 pacing delay retained unchanged.
  delay(20);
}
