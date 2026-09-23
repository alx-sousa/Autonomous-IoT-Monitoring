# Hospital proximity monitoring and local alarms | V1

**ESP32-C6 · Embedded C++ · ESP-NOW · RSSI filtering · RFID · Hardware/software integration**

[Español](README.md) · [Architecture](docs/architecture.md) · [Results](docs/testing.md) · [Technical review](docs/firmware-review.md)

An embedded systems and IoT prototype developed by **Luis Alejandro Pérez Sousa** during a professional residency at Hospital General Dr. Desiderio G. Rosado Carbajal in Comalcalco, Tabasco, Mexico.

The system combines a wearable transmitter and two receivers to generate local alerts when the transmitter moves away from a bed area or approaches an exit. Processing runs on the receivers; Arduino IoT Cloud provides secondary telemetry. This is an experimental residency prototype, without medical certification or clinical validation.

## Built prototype

<p align="center">
  <img src="docs/images/20260716_211125.jpg" width="31%" alt="Integrated prototype, view 1">
  <img src="docs/images/20260716_211140.jpg" width="31%" alt="Integrated prototype, view 2">
  <img src="docs/images/20260716_211158.jpg" width="31%" alt="Integrated prototype, view 3">
</p>

<p align="center">
  <img src="docs/images/20260717_100755~2.jpg" width="50%" alt="Wearable transmitter">
</p>

## Engineering contribution

- C++ firmware for three ESP32-C6 nodes, direct wireless communication and local control.
- RSSI processing with an exponential moving average, area-node hysteresis and separate proximity logic for each receiver.
- UART/I²C integration of RDM6300 and PN532 readers, OLED displays and GPIO-driven indicators.
- Electronic design in EasyEDA, physical module integration and SolidWorks enclosure design.
- Arduino IoT Cloud telemetry and functional prototype evaluation.

Limited budget and accessible components guided the design. The repository explains the trade-offs without claiming a measured cost reduction or commercial product readiness.

## Architecture

| Node | Responsibility |
|---|---|
| Wearable | Two ESP-NOW destinations; channel sweep from 1 to 11 |
| Area receiver | Departure detection, EMA/hysteresis, RDM6300 interaction and local alarms |
| Exit receiver | Approach detection, PN532 reset and a six-second exclusion after an active alarm is reset |

The system monitors transmitter proximity, not mattress occupancy or falls. RSSI is not an exact distance measurement.

## Reported evaluation

| Metric | Residency report result |
|---|---:|
| Mean detection time | 2 s |
| Mean alarm activation time | 2.2 s |
| Reported maximum stable-RSSI distance range | 11–17 m |
| False alarms | 1 in 20 trials |
| Battery runtime | 4.9 h |

Source: final residency report, table 24, printed page 72. These are historical aggregate results, not guarantees or a fresh validation of the published source. Raw trial records are not included.

## Reproducibility and scope

Start with [setup instructions](docs/getting-started.md), [hardware notes](hardware/README.md) and the [evidence gallery](docs/evidence.md). Detailed documentation is in Spanish.

The technical review distinguishes report claims from source behavior: counters advance per loop iteration rather than per new packet; RFID reads are not checked against an authorized UID list; receivers have no explicit packet-loss timeout. PCB figures also require reconciliation with the actual C6 hardware and are not manufacturing files.

The current revision consolidates firmware and restores a missing Cloud connection object declaration. Compilation and hardware tests have not been repeated. See [SECURITY.md](SECURITY.md) for historical credential exposure and rotation requirements.

**Luis Alejandro Pérez Sousa** · Mechatronics Engineering, ITSC  
[GitHub profile](https://github.com/alx-sousa)
