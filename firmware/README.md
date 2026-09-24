# Firmware

Los tres sketches publicados corresponden a V1. No se incluye firmware validado para REV 2.0.

| Carpeta / sketch | Función | Hardware documentado |
|---|---|---|
| [transmitter](transmitter/transmitter.ino) | Emisión ESP-NOW a dos receptores | ESP32-C6 |
| [area_node](area_node/area_node.ino) | RSSI, histéresis, modo paseo y alarma | ESP32-C6, RDM6300 UART, OLED y RGB |
| [exit_node](exit_node/exit_node.ino) | Aproximación, alarma y restablecimiento RFID | ESP32-C6, PN532 I²C y OLED |

Se mantienen las rutas existentes y la coincidencia entre carpeta y nombre del `.ino`. Copiar `secrets.example.h` como `secrets.h` en cada receptor y configurar valores propios. No publicar ese archivo.

## Reproducción

[Entorno y puesta en marcha](../docs/getting-started.md) · [Lógica implementada](../docs/communication.md) · [Revisión estática](../docs/firmware-review.md).

No hay versiones históricas fijadas del core y bibliotecas ni compilación repetida en esta actualización. El port a XIAO debe definir GPIO, dimensiones de OLED, polaridad de salidas, lector PN532 y estrategia de conectividad antes de probarse. Los resultados de V1 no se trasladan automáticamente al nuevo hardware.
