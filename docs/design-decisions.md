# Engineering decisions

## Project delivery context

V1 was developed as a team-funded engineering project in response to a technical request from the hospital's DTI department. **Luis Alejandro Pérez Sousa led the project team**, coordinating technical integration, task execution, testing and documentation. The team completed the V1 system, experimentally evaluated its operation and delivered it to the hospital.

## V1 design decisions

| Need | Implemented decision | Engineering trade-off |
|---|---|---|
| Local alerting | Execute proximity decisions on the receiver nodes and communicate through ESP-NOW | Keeps the primary alert path local rather than server-dependent |
| Reuse integrated radio | Use RSSI as the proximity indicator | Avoids a dedicated ranging sensor but requires environmental calibration and does not provide exact distance |
| Reduce fluctuations | Apply signal filtering | Improves stability with a response-time trade-off |
| Prevent state oscillation | Use hysteresis / confirmation logic | Reduces rapid state changes around the operating boundary |
| Address two situations | Area node detects departure; exit node detects approach | Keeps each receiver focused on its own local condition |
| Card interaction | Use RDM6300/UART and PN532/I²C | Provides local operator interaction through RFID |
| Local feedback | OLED, LEDs and buzzer | Gives immediate indication without requiring the cloud interface |
| Remote visibility | Arduino IoT Cloud | Adds telemetry while local decisions remain receiver-side |
| Mechanical integration | Modular enclosures and later custom PCB/carrier design | Supports serviceability and iterative development |

Exact control parameters are intentionally not published in the public portfolio.

## REV 2.0 improvement request

After V1, a follow-up **request for improvement** initiated REV 2.0. The redesign focuses on cleaner electrical integration, maintainability and a more compact receiver.

Current design goals include reducing point-to-point wiring, using a dedicated two-layer carrier PCB, keeping the XIAO ESP32-S3 removable, preserving USB-C/antenna access, improving battery integration and completing the enclosure CAD in Fusion 360.
