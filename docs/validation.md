# Estado de validación

Esta matriz separa evidencia histórica, inspección documental y pruebas pendientes. No convierte exportaciones CAD en resultados experimentales.

| Revisión / actividad | Estado | Evidencia o pendiente |
|---|---|---|
| V1: integración física | Documentada | [Galería](evidence.md) e informe de residencia |
| V1: evaluación funcional | Resultados históricos reportados | [Tabla y método](testing.md); no hay dataset crudo publicado |
| V1: revisión del código | Revisión estática documentada | [Hallazgos](firmware-review.md) |
| V1: compilación del código publicado | No repetida en esta actualización | Fijar core, bibliotecas, placa y registrar build |
| REV 2.0: esquema, layout y renders | Archivos disponibles | [Inventario](../hardware/rev2/README.md) |
| REV 2.0: exportación Gerber/Drill | Disponible | No equivale a DFM aprobado |
| REV 2.0: selección PCBA | Incompleta | U3 sin selección, pogos con cantidad cero y matching pendiente |
| REV 2.0: fabricación / recepción | Sin evidencia aportada | Confirmación y fotografías de placa recibida |
| REV 2.0: bring-up y firmware | Pendiente | [Plan de banco](hardware-rev2.md) |
| REV 2.0: autonomía y desempeño RF | Pendiente | Medir con configuración nueva; no reutilizar métricas V1 |

## Cómo registrar una prueba

Cada registro debe incluir ID, fecha, objetivo, revisión de hardware, commit de firmware, versiones de dependencias, configuración, procedimiento, criterio de aceptación, resultado y enlace a evidencia. Registrar también fallos y cambios derivados. Los criterios se definen antes del ensayo.

Los informes publicables podrán añadirse a `docs/reports/` cuando existan y estén revisados para excluir credenciales y datos personales.
