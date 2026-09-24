#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

// V1 receiver MAC addresses. The published firmware uses a static peer list.
uint8_t receptor1[] = {0x58, 0xE6, 0xC5, 0x12, 0x0A, 0x3C};
uint8_t receptor2[] = {0x58, 0xE6, 0xC5, 0x12, 0x0C, 0x38};

// One-byte heartbeat payload. Receiver decisions are based on packet RSSI.
uint8_t dato = 1;

// V1 sweeps Wi-Fi channels 1 through 11 to reach receivers that share the radio
// with Wi-Fi/cloud connectivity.
int canalActual = 1;

// Keep the ESP-NOW peer metadata aligned with the radio channel before sending.
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

  // Both V1 peers start on channel 1; loop() updates the channel dynamically.
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
  // Move the station radio and both peers to the same channel.
  esp_wifi_set_channel(canalActual, WIFI_SECOND_CHAN_NONE);

  esp_now_mod_peer_channel(receptor1, canalActual);
  esp_now_mod_peer_channel(receptor2, canalActual);

  // Historical V1 behavior: transmit twice to each receiver on every channel.
  esp_now_send(receptor1, &dato, sizeof(dato));
  esp_now_send(receptor2, &dato, sizeof(dato));
  delay(15);

  esp_now_send(receptor1, &dato, sizeof(dato));
  esp_now_send(receptor2, &dato, sizeof(dato));
  delay(65);

  // Continue the 1..11 channel sweep.
  canalActual++;

  if (canalActual > 11) {
    canalActual = 1;
  }
}
