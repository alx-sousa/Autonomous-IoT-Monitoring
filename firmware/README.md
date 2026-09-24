# Firmware

The three published sketches correspond to V1. No validated REV 2.0 firmware is included yet.

| Folder / sketch | Responsibility | Documented hardware |
|---|---|---|
| [transmitter](transmitter/transmitter.ino) | ESP-NOW transmission to two receivers | ESP32-C6 |
| [area_node](area_node/area_node.ino) | RSSI, hysteresis, walking mode and local alarm | ESP32-C6, RDM6300 UART, OLED and RGB |
| [exit_node](exit_node/exit_node.ino) | Approach detection, alarm and RFID reset | ESP32-C6, PN532 I²C and OLED |

Existing paths and Arduino folder/file naming are preserved. Copy `secrets.example.h` to `secrets.h` in each receiver directory and configure your own values. Never commit the local secret file.

## Reproduction

[Environment and setup](../docs/getting-started.md) · [Implemented logic](../docs/communication.md) · [Static review](../docs/firmware-review.md).

Original ESP32 core/library versions were not pinned and compilation was not repeated during the portfolio documentation update. A future XIAO port must explicitly define GPIO mapping, OLED dimensions, output polarity, PN532 interface and connectivity strategy before validation. V1 results do not automatically transfer to the new hardware.
