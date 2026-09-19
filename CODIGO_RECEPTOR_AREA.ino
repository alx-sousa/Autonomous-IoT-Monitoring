#include <WiFi.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
 
#include <esp_now.h>
#include <esp_wifi.h>
#include <HardwareSerial.h>
 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
// CREDENCIALES ARDUINO CLOUD - NODO CAMILLA
 
const char SSID_WIFI[]         = "CABLETECH3AF6";  // Red matriz directa
const char PASS_WIFI[]         = "kEueE3uJxY";       
const char DEVICE_LOGIN_NAME[] = "60b187f0-c404-439f-8d7c-020c75fee601"; 
const char DEVICE_KEY[]        = "rrtlrLLrfQymyA!0jkr25LSQz"; 
 
WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID_WIFI, PASS_WIFI);
 
// VARIABLES CLOUD
 
float rssiArea;
String estadoPaciente;
bool alarmaCritica;
bool modoPaseoCloud;
bool pacienteLejos;
 
// OLED
 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
unsigned long oledTiempo = 0;
unsigned long oledDuracion = 0;
bool oledActivo = false;
 
void oledMensaje(const char* txt, unsigned long duracion = 5000){
 
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,25);
  display.println(txt);
  display.display();
 
  oledTiempo = millis();
  oledDuracion = duracion;
  oledActivo = (duracion > 0);
}
 
// RFID
 
HardwareSerial RFID(1);
 
#define RFID_RX 17
 
String frame = "";
 
unsigned long lastRFID = 0;
 
const int BLOQUEO_RFID = 1500;
 
// PINES
 
#define BUZZER_PIN 19
#define LED_BLUE   14
#define LED_GREEN  15
#define LED_RED    18
 
// RSSI
 
const int PUNTO_ALERTA = -66;
const int PUNTO_SALIDA = -59;
 
float rssiFiltrado = -40.0;
float alpha = 0.2;
 
enum Estado { CERCA, LEJOS };
 
Estado estadoActual = CERCA;
 
bool alarmaSilenciada = false;
bool modoPaseo = false;
 
int contadorLejos = 0;
 
const int CONFIRMACION_LEJOS = 5;
 
// CRITICO
 
const int UMBRAL_CRITICO = -84;
const int UMBRAL_CRITICO_SALIDA = -80;
 
// TIMERS
 
unsigned long tiempoAzul = 0;
 
bool azulEncendido = false;
bool rojoActivo = false;
 
// CLOUD
 
void initProperties(){
 ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
 ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);

 ArduinoCloud.addProperty(rssiArea, READ, 1 * SECONDS, NULL);
 ArduinoCloud.addProperty(estadoPaciente, READ, 1 * SECONDS, NULL);
 ArduinoCloud.addProperty(alarmaCritica, READ, 1 * SECONDS, NULL);
 ArduinoCloud.addProperty(modoPaseoCloud, READ, 1 * SECONDS, NULL);
 ArduinoCloud.addProperty(pacienteLejos, READ, 1 * SECONDS, NULL);
}
 
// CHECKSUM RFID
 
bool validarChecksum(String data){
 
  byte checksum = 0;
 
  for(int i=0;i<10;i+=2){
     byte value = strtol(data.substring(i,i+2).c_str(),NULL,16);
     checksum ^= value;
  }
 
  byte recibido = strtol(data.substring(10,12).c_str(),NULL,16);
 
  return checksum == recibido;
}
 
// RFID
void leerRFID(){
 
  while(RFID.available()){
 
    char c = RFID.read();
 
    if(c == 0x02){
       frame = "";
       return;
    }
 
    if(c == 0x03){
 
      if(frame.length() == 12 && validarChecksum(frame)){
 
        if(millis() - lastRFID > BLOQUEO_RFID){
 
          oledMensaje("TARJETA DETECTADA",1000);
 
          digitalWrite(BUZZER_PIN,HIGH);
          delay(160);
          digitalWrite(BUZZER_PIN,LOW);
          modoPaseo = !modoPaseo;
 
          if(modoPaseo){
            oledMensaje("PASEO ACTIVADO",5000);
          }else{
            oledMensaje("PASEO DESACTIVADO",5000);
          }
 
          lastRFID = millis();
        }
 
      }else{
        oledMensaje("ERROR RFID",5000);
      }
 
      frame = "";
      return;
    }
 
    frame += c;
  }
}
 
// ESPNOW
 
void OnDataRecv(const esp_now_recv_info *info,const uint8_t *data,int len){
 
  if(info && info->rx_ctrl){
 
    int rssiReal = info->rx_ctrl->rssi;
 
    rssiFiltrado = (rssiReal * alpha) + (rssiFiltrado * (1.0 - alpha));
  }
}
 
// SETUP
 
void setup(){
 
  Serial.begin(115200);
 
  initProperties();
 
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
 
  setDebugMessageLevel(2);
 
  ArduinoCloud.printDebugInfo();
 
  Wire.begin(7,6);
 
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 
  oledMensaje("INICIANDO");
 
  RFID.begin(9600,SERIAL_8N1,RFID_RX,-1);
 
  pinMode(LED_BLUE,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);
 
  digitalWrite(LED_BLUE,HIGH);
  digitalWrite(LED_GREEN,HIGH);
  digitalWrite(LED_RED,HIGH);
 
  WiFi.mode(WIFI_STA);
 
  esp_wifi_set_channel(1,WIFI_SECOND_CHAN_NONE);
 
  WiFi.disconnect();
 
  if(esp_now_init()!=ESP_OK){
    Serial.println("ERROR ESPNOW");
  }
 
  esp_now_register_recv_cb(OnDataRecv);
 
  oledMensaje("SISTEMA ACTIVADO");
}
 
// LOOP
 
void loop(){
 
  ArduinoCloud.update();
 
  unsigned long ahora = millis();
 
  if(oledActivo && (ahora - oledTiempo >= oledDuracion)){
    display.clearDisplay();
    display.display();
    oledActivo = false;
  }
 
  leerRFID();
 
  if(estadoActual == CERCA){
 
    if(rssiFiltrado <= PUNTO_ALERTA){
      contadorLejos++;
    }else{
      contadorLejos = 0;
    }
 
    if(contadorLejos >= CONFIRMACION_LEJOS){
      estadoActual = LEJOS;
      contadorLejos = 0;
      oledMensaje("PACIENTE LEJOS",0);
    }
 
  }else{
 
    if(rssiFiltrado >= PUNTO_SALIDA){
      estadoActual = CERCA;
      modoPaseo = false;
      oledMensaje("PACIENTE CERCA",5000);
    }
  }
 
  if(estadoActual == LEJOS && !modoPaseo){
 
    if(rssiFiltrado <= UMBRAL_CRITICO){
      digitalWrite(LED_RED,LOW);
      digitalWrite(BUZZER_PIN,HIGH);
      oledMensaje("DISTANCIA CRITICA",0);
 
    }else{
      digitalWrite(LED_RED,HIGH);
      digitalWrite(BUZZER_PIN,LOW);
    }
  }
 
  // CLOUD UPDATE
 
  rssiArea = rssiFiltrado;
 
  pacienteLejos = (estadoActual == LEJOS);
 
  modoPaseoCloud = modoPaseo;
 
  alarmaCritica = (rssiFiltrado <= UMBRAL_CRITICO && estadoActual == LEJOS && !modoPaseo);
 
  if(estadoActual == LEJOS)
    estadoPaciente = "LEJOS";
  else
    estadoPaciente = "CERCA";
 
  Serial.print("RSSI: ");
  Serial.println(rssiFiltrado);
 
  delay(20);
}
