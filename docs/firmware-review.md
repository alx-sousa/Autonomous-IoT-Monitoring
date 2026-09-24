# Published firmware review

Static review of the V1 source code compared against the final residency report. This review does not include compilation, execution on hardware or certification. Differences are documented to preserve traceability between design intent, implementation and reported results.

## Confirmed implementation

- Transmitter: two ESP-NOW destinations, two sends per destination/channel and channel sweep 1–11.
- Area node: EMA 0.20, NEAR/FAR states, hysteresis, counter, critical condition, RDM6300 parser and checksum.
- Exit node: EMA 0.20, counter, latched alarm, `millis()`-based output toggling and a 6 s exclusion after alarm reset.
- Receivers: OLED output and Arduino IoT Cloud telemetry properties.

## Relevant differences

| Report description | Evidence in published code |
|---|---|
| Five/ten consecutive samples | Counters advance in `loop()`; the same RSSI sample may be counted repeatedly |
| RFID identity authorization | Area validates frame/checksum; exit detects a card; neither has an authorized UID list |
| Bidirectional MAC filtering | Transmitter configures destinations; receiver callbacks do not filter source |
| Exit critical state at −50 dBm | No such threshold or second stage exists in `exit_node.ino` |
| Blue/intermittent preventive area alert | Not implemented as described in the published loop |
| Wi-Fi enabled only for notification events | Cloud handling runs every cycle; no event-only radio-suspension strategy is explicit |
| Physical alarm suspension after authorization/return | Area code does not explicitly reset outputs in every relevant path |
| Fully asynchronous operation | Transmitter and area node use `delay()`; exit alarm timing uses `millis()` |

## Technical items to verify on the bench

1. **RSSI age:** no frame timeout is recorded and the filter is not initialized from the first real sample.
2. **Area outputs:** verify LED/buzzer behavior when leaving the critical condition, enabling walking mode and returning to NEAR.
3. **PN532:** verify the library constructor, auxiliary pins and wiring; `Wire.begin()` alone does not establish complete reader initialization.
4. **Concurrency:** the callback updates RSSI shared with `loop()` without explicit synchronization.
5. **Timers:** `ahora > tiempoDesbloqueo` should be reviewed for `millis()` overflow behavior.
6. **Failure handling:** some initialization paths continue after errors or do not check return values.
7. **Link security:** ESP-NOW is configured without encryption, source verification or payload validation on reception.

These items are code-review findings, not measured failures from the residency. Historical tests and their limitations are documented in [testing.md](testing.md).

## Maintenance changes in the portfolio revision

- The public entry point was consolidated under `firmware/`, removing redundant root-level copies; two earlier copies had embedded credentials.
- Both receivers retain `WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID_WIFI, PASS_WIFI);`; credential values are loaded from the local `secrets.h`.
- Historical algorithms, thresholds, GPIO assignments and timing were preserved. Documentation cleanup does not imply a successful rebuild or physical revalidation.

Previously exposed credentials should be rotated even if history is later rewritten. See [SECURITY.md](../SECURITY.md).
