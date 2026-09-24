# Communication and implemented logic

This document describes the sketches published under `firmware/`. Historical evaluation figures are documented in [testing](testing.md).

## ESP-NOW and filtering

The transmitter registers two peers with fixed MAC addresses and `encrypt = false`. On each channel it sends twice to each destination, with 15 ms and 65 ms delays, then advances from channel 1 through 11. This sweep does not imply delivery acknowledgement or guaranteed synchronization.

The receivers extract RSSI in the receive callback and apply:

`filtered = 0.20 * sample + 0.80 * previous_filtered`

The callbacks do not compare the source MAC against an allow-list and do not validate payload content. They also do not implement a receive timeout. If frames stop arriving, the last filtered RSSI value remains in memory; link loss alone does not trigger a dedicated alarm.

## Area node

| Element | Code behavior |
|---|---|
| Startup | NEAR state; filtered RSSI −40 dBm |
| Enter FAR | RSSI ≤ −66 dBm for five `loop()` evaluations |
| Return to NEAR | RSSI ≥ −59 dBm; walking mode is disabled |
| Critical condition | FAR, walking mode disabled and RSSI ≤ −84 dBm |
| RDM6300 | UART 9600 baud, 12-character frame and XOR checksum between delimiters |
| RFID interaction | Toggles walking mode after a minimum 1500 ms interval |

Only NEAR and FAR belong to the `enum`. CRITICAL is a logical condition, while walking mode is a boolean. The reader output is not compared against an authorized identifier list. The five evaluations may reuse the same RSSI sample.

The critical condition drives the red LED and buzzer, but the current control block does not explicitly reset both outputs in every path when returning to NEAR or enabling walking mode. This requires bench verification before claiming guaranteed physical silence on those transitions.

## Exit node

| Element | Code behavior |
|---|---|
| Startup | Filtered RSSI −84 dBm; alarm disabled |
| Trigger | RSSI ≥ −65 dBm for ten evaluations, with no lockout and no previous alarm |
| Alarm | Remains active until RFID reset; outputs toggle every 150 ms |
| PN532 read | Detects an ISO14443A card; no authorized UID comparison |
| Reset | With an active alarm and valid RFID interval, disables alarm and resets counter/RSSI |
| Exclusion | Suppresses RSSI triggering for 6000 ms after reset; automatic re-arm |

The exclusion period is not activated by every card read; an active alarm is required. The ten counts represent loop cycles, not necessarily ten independent received frames. No second alarm stage at −50 dBm exists in this sketch.

## Telemetry

The area node publishes `rssiArea`, `estadoPaciente`, `alarmaCritica`, `modoPaseoCloud` and `pacienteLejos`. The exit node publishes `rssiPuerta`, `alarmaPuerta` and `estadoPuerta`. They are registered as read-only properties with a one-second interval.

The code does not demonstrate event-only Wi-Fi activation or an explicit radio-suspension strategy.

These thresholds belong to V1. RSSI changes with orientation, obstacles and environment; it is not converted into exact distance, and Bluetooth is not used for detection in these sketches.
