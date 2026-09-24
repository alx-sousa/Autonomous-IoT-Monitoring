# MONITOR IoT — Hardware REV 2.0

Receiver design package supplied by the author. Status: fabrication preparation; assembly and bring-up remain pending evidence.

| Deliverable | File | Scope |
|---|---|---|
| Schematic | [PDF](schematic/schematic-2026-09-23.pdf) | Individual export; title block still says V1.0 and must be harmonized with REV 2.0 |
| Project PDF export | [Original ZIP](schematic/project-pdf-export-2026-09-23.zip) | Preserved for provenance; not an editable project |
| PCB and component list | [PDF](pcb/pcb-documentation-2026-09-23.pdf) | Board documentation export |
| Gerbers and NC Drill | [ZIP](fabrication/gerber-2026-09-23.zip) | Fabrication output; not an approved production release |
| JLCPCB matching | [XLSX](bom/jlcpcb-matching-2026-09-24.xlsx) | BOM Matching report with unresolved items |
| Traceability | [SHA-256 manifest](artifacts.json) | Original names and hash of each supplied artifact |

The received file originally used an `.xls` extension but contains an OOXML workbook; it is published as `.xlsx` without changing its bytes. It is not a consolidated purchasing BOM or proof of payment. Both schematic containers are preserved as supplied exports without assuming they represent different revisions.

Still missing: editable EasyEDA project, CPL/Pick and Place, final manual-assembly/DNP list and physical test results. The XIAO and PN532 are intended as modules purchased and installed by the author. DNP means do not populate; a manually assembled part should not be confused with a component omitted from the system.

[Hardware design details](../../docs/hardware-rev2.md) · [Validation](../../docs/validation.md).
