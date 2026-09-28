# Firmware architecture review

This public document summarizes the engineering structure of the delivered V1 firmware without reproducing the source implementation.

## Confirmed architectural elements

- One wearable transmitter and two independent receiver nodes.
- ESP-NOW communication from the wearable to each receiver.
- RSSI-based proximity evaluation with signal conditioning and state stabilization.
- Receiver-side local decision making and alarms.
- RFID interaction on the receiver workflows.
- OLED/visual/acoustic local feedback.
- Arduino IoT Cloud as a telemetry layer rather than the primary decision path.

## Public scope

The portfolio intentionally does not publish:

- complete C++/Arduino source;
- receiver MAC addresses or device identifiers;
- exact GPIO maps;
- RSSI thresholds, filter coefficients or timing constants;
- implementation-specific recovery, retry or channel-management sequences;
- cloud credentials or internal infrastructure configuration.

## Engineering traceability

The original V1 system was functionally evaluated and delivered. Public documentation preserves the architecture, responsibilities, validation results and design decisions while the complete firmware implementation remains private.

REV 2.0 changes the receiver hardware platform toward a removable XIAO ESP32-S3 and custom PCB. Firmware porting for that hardware is tracked separately from the delivered V1 implementation.
