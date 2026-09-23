# Decisiones de ingeniería de la V1

El objetivo fue construir y evaluar un prototipo con recursos limitados. El bajo costo se presenta como restricción de diseño, sin atribuir una reducción económica medida. El informe introduce este enfoque en la página 3 y describe la selección de componentes en las páginas 35–38; el presupuesto limitado fue confirmado por el autor.

| Necesidad | Decisión implementada | Compromiso y evidencia |
|---|---|---|
| Alertamiento local | Ejecutar lógica en ESP32-C6 y transmitir mediante ESP-NOW | Evita delegar la decisión al servidor. La coexistencia con Wi-Fi y la pérdida de paquetes requieren evaluación; informe §3.6 y firmware |
| Aprovechar hardware disponible | Usar RSSI de la radio integrada | Reduce sensores adicionales; exige calibración y no produce distancia exacta |
| Atenuar fluctuaciones | EMA con α = 0.20 | Mayor suavizado implica respuesta más lenta; el informe §3.7.2 describe el ajuste desde 0.10 |
| Evitar oscilaciones de estado | Umbrales separados −66/−59 dBm en área | Histéresis verificada en el código; los contadores adicionales avanzan por ciclos |
| Atender dos situaciones | Área detecta alejamiento; salida detecta aproximación | Firmware y periféricos diferentes por función |
| Interacción con tarjetas | RDM6300/UART y PN532/I²C | Lectura y control local implementados; no existe lista de UID autorizados |
| Facilitar integración física | Carcasas modulares diseñadas en SolidWorks y fabricadas en PLA | El informe documenta ajustes en la zona de lectura RFID; no aporta ensayos mecánicos normalizados |
| Operación portátil | LiPo, módulo de carga y elevador | Autonomía reportada de 4.9 h; requiere identificar el circuito de protección y la revisión real del módulo |
| Observar estados a distancia | Arduino IoT Cloud | Añade dependencia de conectividad solo a la telemetría; no hay implementación de servidor local en este repositorio |

## Lo que demuestra el proyecto

Integración de firmware, buses de comunicación, procesamiento de señal, electrónica, manufactura de carcasas y evaluación experimental en un mismo prototipo. Los resultados describen su comportamiento observado; no prueban reducción de incidentes clínicos ni superioridad frente a un producto comercial.

## Alcance económico

La documentación disponible no permite reconstruir una BOM cotizada por nodo con proveedores, cantidades y fechas. Por ello, el repositorio documenta el criterio de accesibilidad y la selección de componentes, sin inventar precios, retorno de inversión ni porcentajes de ahorro.
