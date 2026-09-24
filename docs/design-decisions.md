# Engineering decisions

## Project delivery context

V1 was developed as a team-funded engineering prototype under a constrained budget. **Luis Alejandro Pérez Sousa led the project team**, coordinating technical integration, task execution, testing and documentation across the residency effort. The team completed the V1 prototype, experimental evaluation and final residency deliverables.

The available documentation does not provide a complete audited cost ledger, so the repository does not invent savings percentages, ROI or procurement claims. Team funding is documented here as project context, not as proof of a quantified economic advantage.

## V1 design decisions

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

The project combines project leadership, firmware, communication buses, signal processing, electronics, enclosure development and experimental evaluation in one embedded-system prototype. The reported results describe observed prototype behavior; they do not demonstrate a reduction in clinical incidents or superiority over a commercial medical product.

## REV 2.0 improvement request

After V1, a follow-up **request for improvement** initiated REV 2.0. The redesign targets cleaner electrical integration and easier maintenance rather than simply repeating the original prototype.

Current design goals are:

- reduce point-to-point wiring inside the receiver;
- move receiver integration to a dedicated two-layer carrier PCB;
- use a removable XIAO ESP32-S3 controller;
- preserve access to USB-C and serviceable modules;
- improve battery/interface integration;
- publish schematic, PCB, Gerber and component-selection artifacts for traceability.

REV 2.0 remains pre-fabrication / pre-bring-up. No new reliability, power-consumption or total-cost measurements are available yet for comparison with V1. Available files and unresolved checks are listed in [hardware REV 2.0](hardware-rev2.md).
