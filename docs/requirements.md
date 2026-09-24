# V1 objectives, implementation and evidence

Objective source: final residency report, §1.3, printed pages 12–13. Page references use the report's printed numbering rather than PDF viewer index. Visual evidence comes from the same report; implementation evidence is in `firmware/`.

| Objective | Available evidence | Confirmed scope |
|---|---|---|
| Design area and exit stations | Report §§3.3–3.5; photographs; receiver sketches | Two-receiver integration and electronic/mechanical design documented; V1 native CAD/PCB fabrication sources are not published |
| Develop a transmitter with channel sweep | `transmitter.ino`, `canalActual`, two peers | Sweeps channels 1–11 and sends twice per destination/channel; does not guarantee delivery of every packet |
| Integrate 125 kHz and 13.56 MHz RFID | `leerRFID()` and `readPassiveTargetID()` | Read/interaction implemented; checksum on area node. Identity authorization is not implemented |
| Time actuators without blocking | `millis()` in exit-node alarm | Toggles outputs every 150 ms. Transmitter and area node still use `delay()`; the full system is not completely non-blocking |
| Enable remote supervision | `initProperties()`, Cloud variables and figures 41–42 | Arduino IoT Cloud telemetry implemented; user-owned credentials are required |
| Evaluate overall performance | Report §3.7, table 24 and §4.4 discussion | Aggregate metrics reported; no raw dataset or repeated campaign in this portfolio revision |

## General-objective outcome

A three-node prototype was developed to connect wireless proximity and RFID interaction with local alerts. The report contains functional evaluation and response metrics. The hospital-safety objective is the project motivation; it does not equal demonstrated clinical efficacy, fall detection or authenticated access control.

## Reference documentation

Luis Alejandro Pérez Sousa, *Sistema de monitoreo de presencia y alarma local en camilla hospitalaria*, professional residency report, Mechatronics Engineering, Instituto Tecnológico Superior de Comalcalco, cover dated June 2026.

The report was used for this technical summary and figure selection. It is not distributed in full because appendices include sensitive configuration. Differences between report claims and published source are documented in the [firmware review](firmware-review.md).

New REV 2.0 deliverables are documented separately in [hardware-rev2.md](hardware-rev2.md). They do not replace missing V1 source files or validation evidence.
