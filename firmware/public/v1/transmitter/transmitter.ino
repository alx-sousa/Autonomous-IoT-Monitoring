/*
  Autonomous IoT Monitoring — V1 wearable transmitter
  Portfolio-safe historical snapshot.

  Deployment peer MAC addresses have been replaced with placeholders.
  Replace them locally before use.
*/

#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

// Sanitized peer addresses for the public portfolio snapshot.
uint8_t receptor1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
uint8_t receptor2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x02};

uint8_t dato = 1;
int canalActual = 1;

// Update the ESP-NOW peer channel dynamically.
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

  // Register both peers initially on channel 1.
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

  Serial.println("Transmisor ESP-NOW Dinamico Listo");
}

void loop() {
  // Change the physical radio channel.
  esp_wifi_set_channel(canalActual, WIFI_SECOND_CHAN_NONE);

  // Keep the ESP-NOW peer configuration aligned with the active channel.
  esp_now_mod_peer_channel(receptor1, canalActual);
  esp_now_mod_peer_channel(receptor2, canalActual);

  // First transmission burst.
  esp_now_send(receptor1, &dato, sizeof(dato));
  esp_now_send(receptor2, &dato, sizeof(dato));
  delay(15);

  // Second burst used by the V1 prototype to improve receiver opportunity.
  esp_now_send(receptor1, &dato, sizeof(dato));
  esp_now_send(receptor2, &dato, sizeof(dato));
  delay(65);

  canalActual++;
  if (canalActual > 11) {
    canalActual = 1;
  }
}
