# Visual evidence and provenance

This repository separates **portfolio-facing visuals** from **historical development evidence**.

The main README intentionally uses the REV 2.0 PCB render rather than the internal V1 prototyping-board photograph. This keeps the landing page aligned with the current engineering revision while preserving older evidence here for traceability.

The four original photographs under `docs/images/` are preserved with their original names and bytes. The six images under `docs/images/report/` were extracted from the author's final residency report without redrawing them. Page references use the printed page numbering.

## Mechanical design

| Exit-node base | Area-node middle section |
|---|---|
| ![Exit-node CAD base](images/report/cad-exit-base.jpeg) | ![Area-node CAD middle section](images/report/cad-area-middle.jpeg) |

Figures 17 and 18, p. 44. These images document mechanical layout and SolidWorks work. They do not replace editable CAD, dimensioned drawings or tolerance validation.

## Historical internal integration

The following image is retained as **development evidence only**. It is not used as the portfolio landing image because it shows the internal V1 prototyping stage rather than the current REV 2.0 design direction.

<details>
<summary>Show V1 internal assembly photograph</summary>

![Modules assembled inside the V1 enclosures](images/report/prototype-integration.jpeg)

Figure 28, p. 51. This image shows prototyping boards, modules and wiring. It demonstrates that physical integration work took place; it does not prove fabrication of the PCB shown in historical design views.

</details>

## PCB design

![Historical area-node PCB design](images/report/pcb-area-design.png)

Figure 12, p. 40. The visible footprint is labeled ESP32-C3 Super Mini, while the system documentation identifies ESP32-C6. This discrepancy is intentionally retained. The image is historical design evidence, **not a fabrication-ready source**.

## Telemetry

| Area receiver | Exit receiver |
|---|---|
| ![Area RSSI and state dashboard](images/report/cloud-area.png) | ![Exit RSSI and alarm dashboard](images/report/cloud-exit.png) |

Figures 41 and 42, pp. 75–76. These screenshots illustrate RSSI and alarm-state visualization in Arduino IoT Cloud. They do not provide enough information to reconstruct response time, trial count or accuracy.

## Original V1 photographs

The original camera files are preserved under `docs/images/` for provenance. They are intentionally not promoted as REV 2.0 evidence and are not used to imply that the new PCB has already been fabricated.

- `20260716_211125.jpg`
- `20260716_211140.jpg`
- `20260716_211158.jpg`
- `20260717_100755~2.jpg`

## Source and selection

*Sistema de monitoreo de presencia y alarma local en camilla hospitalaria*, professional residency report, Luis Alejandro Pérez Sousa, ITSC, cover dated June 2026. Technical figures related to development and results were selected for this portfolio. Full appendices, credentials, personal documents and internal-infrastructure screenshots are not published.

## REV 2.0 renders

[Perspective](images/rev2/pcb-perspective.png) · [Top](images/rev2/pcb-top.png) · [Bottom](images/rev2/pcb-bottom.png).

EasyEDA exports supplied by the author and preserved without altering their content. They show CAD design only; they do not establish fabrication or assembly. The XIAO and PN532 are not shown mounted. See [artifact provenance and SHA-256 hashes](../hardware/rev2/artifacts.json).
