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

// VARIABLES CLOUD
float rssiPuerta;
bool alarmaPuerta;
String estadoPuerta;

// OLED
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

// PN532
#define SDA_PIN 7
#define SCL_PIN 6
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

// PINES
#define LED_ALARM 20
#define BUZZER_PIN 19

// RSSI
const int PUNTO_ALARMA_PUERTA = -65;
float rssiFiltrado = -84.0;
float alpha = 0.20;
bool alarmaActiva = false;
int contadorCerca = 0;
const int CONFIRMACION_RECEPTOR = 10;

// RFID
unsigned long ultimoRFID = 0;
const int BLOQUEO_RFID = 6000;

// BLOQUEO
bool bloqueoRSSI = false;
unsigned long tiempoDesbloqueo = 0;

// CONTROL ASÍNCRONO DE ALARMA
unsigned long previoMilisAlarma = 0;
const long intervaloAlarma = 150;
bool estadoAlarma = LOW;

// CLOUD
void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);

  ArduinoCloud.addProperty(rssiPuerta, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(alarmaPuerta, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(estadoPuerta, READ, 1 * SECONDS, NULL);
}

// ESP-NOW
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  if (info && info->rx_ctrl) {
    int rssiReal = info->rx_ctrl->rssi;
    rssiFiltrado = (rssiReal * alpha) + (rssiFiltrado * (1.0 - alpha));
  }
}

// SETUP
void setup() {
  delay(2000);

  Serial.begin(115200);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(LED_ALARM, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin(SDA_PIN, SCL_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  oledMensaje("INICIANDO");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK) {
    oledMensaje("ERROR ESPNOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();

  if (!versiondata) {
    oledMensaje("PN532 ERROR");
  } else {
    nfc.SAMConfig();
  }

  oledMensaje("RECEPTOR LISTO");
}

// LOOP
void loop() {
  ArduinoCloud.update();
  unsigned long ahora = millis();

  if (bloqueoRSSI && ahora > tiempoDesbloqueo) {
    bloqueoRSSI = false;
    oledMensaje("SISTEMA ACTIVO");
  }

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
