#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

// Direcciones MAC de los nodos receptores.
uint8_t receptor1[] = {0x58, 0xE6, 0xC5, 0x12, 0x0A, 0x3C};
uint8_t receptor2[] = {0x58, 0xE6, 0xC5, 0x12, 0x0C, 0x38};

uint8_t dato = 1;
int canalActual = 1;

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

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error iniciando ESP-NOW");
    return;
  }

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

  Serial.println("Transmisor ESP-NOW dinámico listo");
}

void loop() {
  esp_wifi_set_channel(canalActual, WIFI_SECOND_CHAN_NONE);

  esp_now_mod_peer_channel(receptor1, canalActual);
  esp_now_mod_peer_channel(receptor2, canalActual);

  esp_now_send(receptor1, &dato, sizeof(dato));
  esp_now_send(receptor2, &dato, sizeof(dato));
  delay(15);

  esp_now_send(receptor1, &dato, sizeof(dato));
  esp_now_send(receptor2, &dato, sizeof(dato));
  delay(65);

  canalActual++;

  if (canalActual > 11) {
    canalActual = 1;
  }
}
