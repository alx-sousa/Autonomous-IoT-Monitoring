#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
 
// MAC de tus dos receptores actualizadas
uint8_t receptor1[] = {0x58, 0xE6, 0xC5, 0x12, 0x0A, 0x3C}; 
uint8_t receptor2[] = {0x58, 0xE6, 0xC5, 0x12, 0x0C, 0x38};
 
uint8_t dato = 1;
int canalActual = 1;
 
// Función auxiliar para modificar dinámicamente el canal asignado al peer
void esp_now_mod_peer_channel(const uint8_t *peer_addr, int channel) {
  esp_now_peer_info_t peerStack;
  if (esp_now_get_peer(peer_addr, &peerStack) == ESP_OK) {
    peerStack.channel = channel;
    esp_now_modify_peer(&peerStack);
  }
}
 
void setup() {
  Serial.begin(115200);
  delay(1000);
 
  // WiFi en modo Estación
  WiFi.mode(WIFI_STA);
 
  // ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error iniciando ESP-NOW");
    return;
  }
 
  // Registrar Peers inicialmente en el canal 1
  esp_now_peer_info_t peer = {};
  peer.channel = 1;
  peer.encrypt = false;
 
  memcpy(peer.peer_addr, receptor1, 6);
  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Error al agregar Receptor 1");
  }
 
  memcpy(peer.peer_addr, receptor2, 6);
  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Error al agregar Receptor 2");
  }
 
  Serial.println("Transmisor ESP-NOW Dinámico Listo");
}
 
void loop() {
  // Cambiar el canal físico de emisión de la antena
  esp_wifi_set_channel(canalActual, WIFI_SECOND_CHAN_NONE);
  
  // Estructuras internas de ESP-NOW para ambos receptores
  esp_now_mod_peer_channel(receptor1, canalActual);
  esp_now_mod_peer_channel(receptor2, canalActual);
 
  // Primera ráfaga de envío
  esp_now_send(receptor1, &dato, sizeof(dato));
  esp_now_send(receptor2, &dato, sizeof(dato));
  delay(15); 
 
  // Ráfaga de envío para asegurar que el receptor capte el RSSI
  esp_now_send(receptor1, &dato, sizeof(dato));
  esp_now_send(receptor2, &dato, sizeof(dato));
  delay(65); 
 
  // Canal de radio para el próximo ciclo
  canalActual++;
  if(canalActual > 11) {
    canalActual = 1; // Reinicia el ciclo de canales (Estándar WiFi en México)
  }
}
