# V1 public firmware snapshots

This directory contains **portfolio-safe snapshots of the V1 prototype firmware** for technical review.

The files preserve the main control flow used in the project—ESP-NOW transmission, RSSI filtering, local state logic, RFID interaction, OLED/alarm handling and Arduino IoT Cloud telemetry—while removing deployment credentials and device identifiers.

## Nodes

- [Wearable transmitter](transmitter/transmitter.ino)
- [Area receiver](area_receiver/area_receiver.ino)
- [Exit receiver](exit_receiver/exit_receiver.ino)

## Security boundary

The public snapshots do **not** contain:

- Wi-Fi passwords;
- Arduino IoT Cloud secret device keys;
- deployment device identifiers;
- real ESP-NOW peer MAC addresses;
- patient data.

Placeholder values must be replaced locally before attempting to build or deploy the code.

## Status

These files document the **historical V1 prototype implementation** and are published as engineering evidence. They are not presented as production firmware, medical-device software, or a reproducible deployment package.

The repository's architecture and validation documentation remain the authoritative description of system behavior and measured V1 results.

## Engineering review notes

The snapshot also preserves several areas that would be improved in a later firmware revision:

- configuration and pin mapping should be separated from application logic;
- sender identity and packet-length validation should be explicit in ESP-NOW receive callbacks;
- Wi-Fi / Arduino IoT Cloud and ESP-NOW channel coexistence should be documented and verified for the target network;
- remaining blocking delays should be replaced where practical;
- thresholds and timing constants should move into a centralized configuration layer;
- automated tests and a reproducible build environment should be added.

These are documented as development opportunities rather than retroactively rewriting the delivered V1 behavior.
