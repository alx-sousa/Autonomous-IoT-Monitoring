#include <WiFi.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#include <esp_now.h>
#include <esp_wifi.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PN532.h>

#include "secrets.h"

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID_WIFI, PASS_WIFI);

// Arduino IoT Cloud mirror variables.
// Local alarm logic remains receiver-side.
float rssiPuerta;
bool alarmaPuerta;
String estadoPuerta;

// OLED configuration.
// Operator-facing V1 messages remain in Spanish to preserve historical behavior.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void oledMensaje(const char* txt) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);
  display.println(txt);
  display.display();
}

// V1 I2C pins and PN532 instance.
// The exact Adafruit_PN532 constructor semantics should be verified against the
// library version used for a future rebuild; see docs/firmware-review.md.
#define SDA_PIN 7
#define SCL_PIN 6
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

// V1 alarm outputs.
#define LED_ALARM 20
#define BUZZER_PIN 19

// RSSI approach detection.
// A filtered value at or above -65 dBm begins the near-door confirmation path.
const int PUNTO_ALARMA_PUERTA = -65;
float rssiFiltrado = -84.0;
float alpha = 0.20;
bool alarmaActiva = false;
int contadorCerca = 0;

// Important V1 behavior: contadorCerca advances in loop() iterations, not only
// when a fresh ESP-NOW frame arrives. See docs/firmware-review.md.
const int CONFIRMACION_RECEPTOR = 10;

// RFID read lockout after a successful card event.
unsigned long ultimoRFID = 0;
const int BLOQUEO_RFID = 6000;

// Temporary RSSI lockout after alarm reset.
// This prevents the same nearby transmitter condition from immediately
// re-triggering the door alarm.
bool bloqueoRSSI = false;
unsigned long tiempoDesbloqueo = 0;

// Non-blocking alarm toggling at 150 ms intervals.
unsigned long previoMilisAlarma = 0;
const long intervaloAlarma = 150;
bool estadoAlarma = LOW;

// Register read-only telemetry properties.
void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);

  ArduinoCloud.addProperty(rssiPuerta, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(alarmaPuerta, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(estadoPuerta, READ, 1 * SECONDS, NULL);
}

// ESP-NOW receive callback.
// The V1 receiver uses frame RSSI as the proximity input and applies an EMA.
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  if (info && info->rx_ctrl) {
    int rssiReal = info->rx_ctrl->rssi;
    rssiFiltrado = (rssiReal * alpha) + (rssiFiltrado * (1.0 - alpha));
  }
}

void setup() {
  delay(2000);

  Serial.begin(115200);

  // Start Arduino IoT Cloud using credentials from the local secrets.h file.
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(LED_ALARM, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Shared V1 I2C bus for OLED and PN532.
  Wire.begin(SDA_PIN, SCL_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  oledMensaje("INICIANDO");

  // ESP-NOW begins on channel 1; the transmitter sweeps channels 1..11.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK) {
    oledMensaje("ERROR ESPNOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  // Initialize the PN532. A missing firmware response is surfaced on the OLED.
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();

  if (!versiondata) {
    oledMensaje("PN532 ERROR");
  } else {
    nfc.SAMConfig();
  }

  oledMensaje("RECEPTOR LISTO");
}

void loop() {
  // V1 runs the cloud handler continuously; local alert logic is still executed
  // on this receiver.
  ArduinoCloud.update();
  unsigned long ahora = millis();

  // End the temporary post-RFID RSSI lockout.
  // The historical comparison is retained unchanged; rollover behavior is
  // documented as a review item in docs/firmware-review.md.
  if (bloqueoRSSI && ahora > tiempoDesbloqueo) {
    bloqueoRSSI = false;
    oledMensaje("SISTEMA ACTIVO");
  }

  // Latch the door alarm after the filtered RSSI remains above the threshold
  // for the configured confirmation count.
  if (!alarmaActiva && !bloqueoRSSI) {
    if (rssiFiltrado >= PUNTO_ALARMA_PUERTA) {
      contadorCerca++;

      if (contadorCerca >= CONFIRMACION_RECEPTOR) {
        alarmaActiva = true;
        oledMensaje("PACIENTE EN PUERTA");
      }
    } else {
      contadorCerca = 0;
    }
  }

  uint8_t uid[7];
  uint8_t uidLength;

  // Poll briefly for an ISO14443A target.
  bool tarjeta = nfc.readPassiveTargetID(
    PN532_MIFARE_ISO14443A,
    uid,
    &uidLength,
    10
  );

  if (tarjeta) {
    if (ahora - ultimoRFID > BLOQUEO_RFID) {
      ultimoRFID = ahora;
      oledMensaje("TARJETA OK");

      // In V1, any detected card can reset an active alarm; no authorized UID
      // allowlist is implemented in the published source.
      if (alarmaActiva) {
        alarmaActiva = false;
        contadorCerca = 0;
        rssiFiltrado = -84.0;
        bloqueoRSSI = true;
        tiempoDesbloqueo = ahora + 6000;

        oledMensaje("ALARMA RESET");
      }
    }
  }

  // Toggle the visual/acoustic alarm without delay() while the alarm is latched.
  if (alarmaActiva) {
    if (ahora - previoMilisAlarma >= intervaloAlarma) {
      previoMilisAlarma = ahora;
      estadoAlarma = !estadoAlarma;
      digitalWrite(LED_ALARM, estadoAlarma);
      digitalWrite(BUZZER_PIN, estadoAlarma);
    }
  } else {
    digitalWrite(LED_ALARM, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Mirror local state to Arduino IoT Cloud.
  rssiPuerta = rssiFiltrado;
  alarmaPuerta = alarmaActiva;

  if (alarmaActiva) {
    estadoPuerta = "ALERTA";
  } else {
    estadoPuerta = "NORMAL";
  }

  Serial.print("RSSI: ");
  Serial.println(rssiFiltrado, 1);
}
