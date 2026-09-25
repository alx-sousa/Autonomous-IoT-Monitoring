# Validation status

This matrix separates historical evidence, document inspection and tests that are still pending. CAD exports are not treated as experimental results.

| Revision / activity | Status | Evidence or pending work |
|---|---|---|
| V1 physical integration | Documented | [Evidence gallery](evidence.md) and V1 technical report |
| V1 functional evaluation | Historical results reported | [Results and method](testing.md); no raw dataset published |
| V1 source review | Static review documented | [Findings](firmware-review.md) |
| V1 build of the published source | Not repeated in this portfolio revision | Pin ESP32 core, libraries and board target; record build |
| REV 2.0 schematic, layout and renders | Files available | [Inventory](../hardware/rev2/README.md) |
| REV 2.0 Gerber/Drill export | Available | Does not equal approved DFM |
| REV 2.0 PCBA component selection | Incomplete | U3 unresolved, pogo quantity zero and several matches unconfirmed |
| REV 2.0 fabrication / received board | No evidence published | Add order/receipt evidence and board photographs |
| REV 2.0 bring-up and firmware | Pending | [Bench plan](hardware-rev2.md) |
| REV 2.0 battery runtime and RF performance | Pending | Measure on new hardware; do not reuse V1 metrics |

## How to record a test

Each validation record should include an ID, date, objective, hardware revision, firmware commit, dependency versions, configuration, procedure, acceptance criterion, result and evidence link. Failures and resulting design changes should be recorded as well. Acceptance criteria should be defined before execution.

Publishable test reports can be added under `docs/reports/` after reviewing them for credentials and personal data.
