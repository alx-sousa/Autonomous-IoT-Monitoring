# Hardware REV 2.0

Receiver redesign around a removable XIAO ESP32-S3. The published files document the design state; they do not establish that a board has been manufactured, assembled or electrically validated.

## Blocks and interfaces

| Element | Documented design |
|---|---|
| XIAO ESP32-S3 | Intended controller; U5/U6 seven-contact sockets, USB accessible at board edge |
| OLED1 | HS91L02W2C01, SDA/SCL and 3V3; JLCPCB matching report identifies 128×32 |
| PN532 | External module through U7 four-contact header: GND, 3V3, SDA, SCL |
| BUZZER1 / Q1 / D1 | Buzzer with BC547 NPN driver and 1N4148W diode |
| U4 / R3–R5 | RGB LED with 330 Ω resistors |
| SW1 | Local interaction pushbutton |
| CN2 / U3 | Two-contact PH connector and SS12D00G4 switch in the battery interface |
| CN1 / CN3 | BAT− / BAT+ pogo contacts; dimensions and compression reviewed by the author |
| C1 / C2 | 100 nF and 10 µF decoupling |

The absence of a 3D model does not determine whether a manufacturer can supply a component. That depends on BOM selection, footprint compatibility, availability and assembly service.

## PCB and routing

The Gerber package contains top/bottom copper, solder masks, silkscreen and PTH/via drill outputs. Renders show copper pours and additional stitching vias. The design intent is to use GND planes on both layers and connect them with stitching vias; final connectivity should still be checked against the editable project and DRC for the exact released revision.

The agreed routing guideline is 0.254 mm for signals and 0.5 mm for power/battery nets. This is a design rule, not a documented maximum-current calculation. It must be compared with the real traces and manufacturer rules. Copper weight and finish should be recorded in the final order.

![REV 2.0 top side](images/rev2/pcb-top.png)

[Bottom view](images/rev2/pcb-bottom.png) · [Hardware package](../hardware/rev2/README.md).

## PCBA preparation

The supplied JLCPCB file is a component-matching result for five boards, not proof of manufacturing:

- U3: no component selected.
- CN1/CN3: quantity zero in the report; confirm whether they are manually supplied/assembled.
- R2, R3–R5 and R6: matches are marked as unconfirmed.
- BUZZER1: the selected part reference and footprint name do not literally match; verify dimensions and pads against the datasheet before accepting a substitution.
- No independent CPL/Pick and Place file is included. Review must verify side, position and rotation by designator.
- XIAO and PN532: intended for installation by the author. Confirm the final assembly scope for all remaining parts before publishing a closed BOM.

Purchase quantities in the matching report may include MOQ or overage and should not be interpreted as quantity per PCB.

## Reconciliation before release

1. Harmonize REV 2.0 identification: the individual schematic title block still says V1.0.
2. Verify U1–U5 mapping: U1 labels D4/SDA, D5/SCL and D6/Bb, while U5 maps contacts 5/6/7 to Bb/SDA/SCL. Resolve using physical socket numbering and firmware configuration before claiming equivalence.
3. Reconcile OLED size: V1 firmware configures 128×64, while the REV 2.0 matching file identifies 128×32.
4. Complete component selection, manual-assembly/DNP definition, CPL review and Gerber/NC Drill review.
5. Record DRC and tests for this exact hardware revision.

## Proposed bring-up — not yet executed

Start with unpowered inspection of assembly, orientation and continuity. Check for shorts between rails and GND. Power the board with current limiting and record voltages/current. Test XIAO, OLED, pushbutton, RGB LED, buzzer and PN532 individually before integrating communications. Evaluate battery/charging behavior, resets and link loss. Record PCB revision, firmware commit, instruments, conditions and outcome for every test.

See the [validation log](validation.md). Enclosure and full mechanical validation should be added when dimensioned files and a physical assembly exist.
