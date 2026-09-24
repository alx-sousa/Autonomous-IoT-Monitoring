# V1 engineering decisions

The objective was to build and evaluate a prototype under limited resources. Low cost is presented as a design constraint, not as a measured economic reduction. The final report introduces this approach on page 3 and describes component selection on pages 35–38.

| Need | Implemented decision | Trade-off and evidence |
|---|---|---|
| Local alerting | Run logic on ESP32-C6 receivers and communicate through ESP-NOW | Avoids delegating the alert decision to a server; Wi-Fi coexistence and packet loss still require evaluation |
| Reuse available hardware | Use RSSI from the integrated radio | Avoids an additional distance sensor; requires calibration and does not provide exact distance |
| Reduce fluctuations | EMA with α = 0.20 | More smoothing improves stability but increases response delay; report §3.7.2 describes tuning from 0.10 |
| Prevent state oscillation | Separate −66/−59 dBm area thresholds | Hysteresis is present in code; additional counters advance per loop cycle |
| Address two situations | Area detects departure; exit detects approach | Different firmware and peripherals are used for each function |
| Card interaction | RDM6300/UART and PN532/I²C | Local read/control is implemented; no authorized UID list is present |
| Simplify physical integration | Modular SolidWorks enclosures printed in PLA | Report documents RFID-zone geometry adjustments; no standardized mechanical testing is available |
| Portable operation | LiPo, charger module and boost converter | 4.9 h runtime was reported; protection circuit and exact module revision still require identification |
| Remote state visibility | Arduino IoT Cloud | Adds connectivity dependency to telemetry only; no reproducible local-server implementation is included |

## What the project demonstrates

The project combines firmware, communication buses, signal processing, electronics, enclosure manufacturing and experimental evaluation in one embedded-system prototype. The reported results describe observed prototype behavior; they do not demonstrate a reduction in clinical incidents or superiority over a commercial medical product.

## Economic scope

The available documentation is not sufficient to reconstruct a fully quoted BOM by node with suppliers, quantities and purchase dates. The repository therefore documents accessibility as a design criterion and records component choices without inventing prices, ROI or savings percentages.

## REV 2.0 evolution

The receiver moves to a carrier PCB with removable sockets and a battery interface. This revision is intended to reduce wiring and improve maintainability. Available files and unresolved checks are listed in [hardware REV 2.0](hardware-rev2.md). No new reliability, power-consumption or total-cost measurements are available yet for comparison with V1.
