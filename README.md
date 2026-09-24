# MONITOR IoT

**Embedded Systems · IoT · PCB Design · Hardware/Firmware Integration**

[Español](README.es.md) · [Hardware REV 2.0](docs/hardware-rev2.md) · [Firmware](firmware/README.md) · [Validation](docs/validation.md)

Wireless proximity monitoring and local alarm system developed by **Luis Alejandro Pérez Sousa** during an engineering residency at Hospital General Dr. Desiderio G. Rosado Carbajal in Comalcalco, Mexico. A wearable transmitter and two receivers combine ESP-NOW, RSSI processing, RFID interaction and local embedded control.

**V1:** prototype built and evaluated during the residency. **REV 2.0:** receiver redesign using a removable XIAO ESP32-S3 and a custom two-layer PCB; fabrication outputs are available, while assembly and physical validation remain pending.

<p align="center"><img src="docs/images/rev2/pcb-perspective.png" width="560" alt="MONITOR IoT REV 2.0 PCB render with OLED, buzzer, RGB LED and removable sockets"></p>

*REV 2.0 EasyEDA render. The XIAO and external PN532 module are not shown installed. This is not a photograph of manufactured hardware.*

## Engineering contribution

- C++ firmware for three ESP32-C6 nodes, ESP-NOW communication and RSSI processing with EMA filtering and hysteresis.
- RFID integration over UART/I²C, OLED interfaces, indicators and local alarms; Arduino IoT Cloud telemetry in V1.
- Electronic design in EasyEDA and V1 enclosure development in SolidWorks.
- Evolution toward a compact two-layer receiver PCB with removable controller, battery interface and fabrication documentation.
- Technical review separating measured V1 results, source-code behavior and pending REV 2.0 verification.

**Technologies:** C++/Arduino, ESP32-C6, XIAO ESP32-S3, ESP-NOW, I²C, UART, GPIO, EasyEDA Pro, SolidWorks and Arduino IoT Cloud. [Requirements and evidence](docs/requirements.md).

## System architecture — V1

```mermaid
flowchart TD
    T["Wearable transmitter · ESP32-C6"] -->|ESP-NOW| A["Area receiver"]
    T -->|ESP-NOW| S["Exit receiver"]
    A --> L["Local alarms and RFID interaction"]
    S --> L
    A -. Wi-Fi telemetry .-> C["Arduino IoT Cloud"]
    S -. Wi-Fi telemetry .-> C
```

The area receiver detects departure and uses an RDM6300 reader. The exit receiver detects approach and uses a PN532. Decisions are executed locally on the receivers. The system monitors transmitter proximity; it does **not** measure mattress occupancy, detect falls or estimate exact distance. [Architecture](docs/architecture.md) · [Communications](docs/communication.md).

## Hardware REV 2.0

Carrier PCB for a **removable XIAO ESP32-S3**, I²C OLED, RGB LED, BC547-driven buzzer, pushbutton and battery interface. A four-contact header connects the external PN532. Available fabrication outputs include copper, solder mask and drill files.

The JLCPCB component-matching export still contains unresolved selections. The design is therefore documented as **pre-fabrication / pre-bring-up**, not as electrically validated hardware or a confirmed production order. [Design and pending checks](docs/hardware-rev2.md) · [Hardware files](hardware/rev2/README.md).

## Firmware

| V1 node | Published implementation |
|---|---|
| [Transmitter](firmware/transmitter/transmitter.ino) | Two ESP-NOW destinations and channel sweep 1–11 |
| [Area receiver](firmware/area_node/area_node.ino) | EMA α = 0.20, −66/−59 dBm hysteresis, UART RFID and critical alarm logic |
| [Exit receiver](firmware/exit_node/exit_node.ino) | Approach detection from −65 dBm, latched alarm and PN532 reset |

These sketches target **V1**. A tested XIAO ESP32-S3 port is not included yet. [Environment setup](docs/getting-started.md) · [Static firmware review](docs/firmware-review.md).

## Engineering decisions

| Constraint | Decision and trade-off |
|---|---|
| Limited budget | Commercial modules and integrated radio; no unmeasured cost-saving claim |
| RSSI variation | EMA and hysteresis; improved stability at the cost of response delay |
| Local alerting | Receiver-side decisions; cloud telemetry remains secondary |
| REV 2.0 integration | Custom PCB and removable sockets; assembly, pin mapping and firmware port still require verification |

[Engineering decisions and evidence](docs/design-decisions.md).

## Historical results — V1

| Metric | Residency report result |
|---|---:|
| Mean detection time | 2 s |
| Mean alarm activation time | 2.2 s |
| Reported maximum stable-RSSI distance range | 11–17 m |
| False alarms | 1 in 20 trials |
| Battery runtime | 4.9 h |

Source: final residency report, table 24, printed page 72. These are historical aggregate results from V1; they do not validate REV 2.0 and do not constitute medical certification. [Methods and limitations](docs/testing.md).

![V1 physical prototype integration](docs/images/report/prototype-integration.jpeg)

*Assembly documented during the residency. [Original photographs and evidence gallery](docs/evidence.md).*

## Repository map

```text
firmware/          V1 sketches by node and example secret configuration
hardware/rev1/     Historical V1 integration and documented interfaces
hardware/rev2/     REV 2.0 schematic, PCB, Gerbers and component matching
docs/              Architecture, decisions, testing, validation and evidence
```

- [Validation by revision](docs/validation.md): evidence available and tests still pending.
- [Hardware overview](hardware/README.md): V1 history and REV 2.0 deliverables.
- [Firmware overview](firmware/README.md): node responsibilities and reproduction notes.
- [Security](SECURITY.md): local secret handling and historical credential exposure.

## Author

**Luis Alejandro Pérez Sousa** — Mechatronics Engineering, ITSC, Mexico. Embedded firmware, electronics, PCB design and hardware–software integration. [GitHub profile](https://github.com/alx-sousa).
