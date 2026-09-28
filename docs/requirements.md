# V1 objectives, implementation and evidence

Objective source: final V1 technical report, §1.3, printed pages 12–13. Public implementation evidence is represented through block-level firmware documentation rather than complete source code.

| Objective | Available evidence | Confirmed scope |
|---|---|---|
| Design area and exit stations | Report §§3.3–3.5, photographs and hardware documentation | Two independent receiver functions with electronic/mechanical integration |
| Develop a wearable transmitter | Wearable photograph, system architecture and transmitter block logic | Patient-side interface plus independent wireless links to both receivers |
| Integrate RFID | Hardware documentation and receiver block logic | RFID interaction is part of each receiver workflow |
| Implement local alarms | V1 evaluation, receiver logic and photographs | Visual/acoustic alerting executes locally on the receivers |
| Enable remote supervision | Arduino IoT Cloud evidence and architecture | Cloud used for telemetry visibility; primary decisions remain local |
| Evaluate overall performance | Report §3.7, table 24 and §4.4 discussion | Aggregate V1 response, range, false-alarm and runtime metrics reported |

## General-objective outcome

A three-node embedded system was developed to connect wireless proximity monitoring, patient-side information display, RFID interaction and local alarms. The system was functionally evaluated and delivered to the hospital.

## Public implementation boundary

The repository documents architecture, design decisions, hardware, validation and firmware logic at block level. Complete firmware source and implementation-specific constants are maintained privately.

New REV 2.0 deliverables are documented separately in [hardware-rev2.md](hardware-rev2.md).
