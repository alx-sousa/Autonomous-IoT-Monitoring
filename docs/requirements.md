# Objetivos, implementación y evidencia — V1

Fuente de objetivos: informe final de residencia, §1.3, páginas 12–13. Las referencias de página usan la numeración impresa, no el contador del visor PDF. La evidencia visual procede del mismo informe; la evidencia de implementación se encuentra en `firmware/`.

| Objetivo | Evidencia disponible | Alcance confirmado |
|---|---|---|
| Diseñar estaciones de área y salida | Informe §§3.3–3.5; fotografías; sketches de receptores | Integración de dos receptores y diseño electrónico/mecánico documentados; no hay fuentes CAD/PCB ni Gerbers publicados |
| Desarrollar transmisor con barrido de canales | `transmitter.ino`, `canalActual`, dos peers | Recorre canales 1–11 y realiza dos envíos por destino en cada canal; no garantiza entrega de todos los paquetes |
| Integrar RFID 125 kHz y 13.56 MHz | `leerRFID()` y `readPassiveTargetID()` | Lectura e interacción implementadas; checksum en área. Autorización por identidad no implementada |
| Temporizar actuadores sin bloquear | `millis()` en alarma del nodo de salida | Alterna salidas cada 150 ms. El transmisor y el nodo de área conservan `delay()`; no es un sistema completamente no bloqueante |
| Habilitar supervisión remota | `initProperties()`, variables Cloud y figuras 41–42 | Telemetría Arduino IoT Cloud implementada; credenciales propias necesarias |
| Evaluar rendimiento integral | Informe §3.7, tabla 24 y discusión §4.4 | Métricas agregadas reportadas; sin dataset crudo ni repetición de pruebas en esta revisión |

## Resultado del objetivo general

Se desarrolló un prototipo de tres nodos que relaciona proximidad inalámbrica e interacción RFID con alertamiento local. El informe aporta evaluación funcional y métricas de respuesta. El objetivo preventivo hospitalario es la motivación del proyecto: no equivale a demostrar eficacia clínica, detectar caídas o disponer de control de acceso autenticado.

## Documentación de referencia

Luis Alejandro Pérez Sousa, *Sistema de monitoreo de presencia y alarma local en camilla hospitalaria*, informe de residencia profesional, Ingeniería Mecatrónica, Instituto Tecnológico Superior de Comalcalco, portada junio de 2026.

El informe se utilizó para esta síntesis y la selección de figuras. No se distribuye íntegro: sus anexos incluyen configuración sensible. Las discrepancias con el código se detallan en [revisión del firmware](firmware-review.md).

Los nuevos entregables REV 2.0 se documentan por separado en [hardware-rev2.md](hardware-rev2.md). No sustituyen archivos o pruebas faltantes de V1.
