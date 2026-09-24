# V1 hardware and integration

The final report documents component selection, EasyEDA design work, SolidWorks enclosures and physical assembly. This section distinguishes reported components, firmware pin definitions and files that are actually available.

## Main components

| Component | Function / node | Evidence |
|---|---|---|
| ESP32-C6 Mini | One controller per node; three in the architecture | Report and firmware |
| RDM6300, 125 kHz | RFID interaction on area node | Report; UART in firmware |
| PN532, 13.56 MHz | RFID interaction on exit node | Report; Adafruit library calls |
| 128×64 I²C OLED | Local receiver interface | Report and firmware; address 0x3C |
| RGB LED / LED | Area / exit indicators | Report and GPIO definitions |
| Buzzer and BJT stage | Acoustic alert | Report, table 8 and design |
| 3.7 V LiPo | Portable power | Report; p. 78 mentions 1200 mAh |
| TP4056 module | Battery charging | Report; exact revision/protection must be verified |
| MT3608 | Boost conversion toward 5 V | Report |
| Resistors, capacitors and interconnects | Switching, decoupling and assembly | Report, figs. 10–15 and 26–28 |
| PLA enclosures | Mechanical integration | Report, figs. 16–25 |

This is a functional component list, **not a complete manufacturing BOM**. Exact per-node quantities, consolidated values, suppliers and verified costs are not available.

## Pins defined in firmware

| Signal | Area node | Exit node |
|---|---|---|
| I²C SDA / SCL | GPIO7 / GPIO6 | GPIO7 / GPIO6 |
| RDM6300 UART RX | GPIO17, 9600 baud | N/A |
| Buzzer | GPIO19 | GPIO19 |
| Blue / green / red LED | GPIO14 / GPIO15 / GPIO18 | N/A |
| Alarm LED | N/A | GPIO20 |

These values are software definitions, not proof of the physical wiring. Confirm GPIO availability, electrical levels and polarity on the exact board before connecting peripherals.

**PN532:** `Wire.begin(7, 6)` configures the I²C bus, but the instance `Adafruit_PN532 nfc(SDA_PIN, SCL_PIN)` requires checking what those constructor arguments mean in the installed library version. Macro names alone do not prove that the constructor expects SDA/SCL. This mapping is therefore not presented as a complete validated PN532 connection.

## Power

The report describes a LiPo, TP4056 charge module and MT3608 boost converter adjusted to 5 V, plus external power. No fabrication-ready power schematic is published. The exact module revision, wiring and charging configuration would need to be identified before reproduction.

Battery protection is not assumed from the TP4056 name alone. The protection components on the actual module and the under-load power topology should be identified. Table 26 reports transition without reset during historical testing, but this does not validate a reproducible power-management circuit.

## PCB design versus documented assembly

![Historical area-node PCB design](../../docs/images/report/pcb-area-design.png)

Figure 12, report page 40. **The visible footprint is labeled ESP32-C3 Super Mini**, while the published architecture and firmware are described for ESP32-C6. The image is preserved as design-work evidence without claiming footprint or pinout compatibility.

The integration photograph (fig. 28) shows prototyping boards and wired modules. The available images therefore do not demonstrate that the historical designed PCB was the board fabricated and installed in the final prototype. V1 native EasyEDA files, Gerbers, native CAD, STEP and STL files are not published.

## Mechanical integration

A sectioned PLA enclosure with locations for peripherals is documented. Report §4.4 describes geometric adjustments around the RFID zone and a recovered read range of approximately 3–5 cm. This is a reported observation; standardized strength, hospital-cleaning and tolerance tests are not available.

[Evidence gallery](../../docs/evidence.md) · [Setup guide](../../docs/getting-started.md)
