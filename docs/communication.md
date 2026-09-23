# Comunicación y lógica implementada

Esta descripción corresponde a los sketches de `firmware/`. Las cifras de evaluación histórica están en [pruebas](testing.md).

## ESP-NOW y filtrado

El transmisor registra dos peers con MAC fija y `encrypt = false`. En cada canal envía dos veces a cada destino, con retardos de 15 y 65 ms, y avanza del canal 1 al 11. Este recorrido no implica confirmación de entrega ni sincronización garantizada.

Los receptores extraen el RSSI en el callback y aplican:

`filtrado = 0.20 * muestra + 0.80 * filtrado_anterior`

Los callbacks no comparan la MAC de origen con una lista ni validan el contenido del paquete. Tampoco registran un timeout de recepción. Si dejan de llegar tramas, permanece el último RSSI filtrado; una pérdida de enlace no produce por sí sola una alarma específica.

## Nodo de área

| Elemento | Comportamiento del código |
|---|---|
| Inicio | Estado CERCA; RSSI filtrado −40 dBm |
| Entrada a LEJOS | RSSI ≤ −66 dBm durante cinco evaluaciones de `loop()` |
| Regreso a CERCA | RSSI ≥ −59 dBm; desactiva modo paseo |
| Condición crítica | LEJOS, sin modo paseo y RSSI ≤ −84 dBm |
| RDM6300 | UART 9600 baud, trama de 12 caracteres y checksum XOR entre delimitadores |
| Interacción RFID | Conmuta modo paseo tras intervalo mínimo de 1500 ms |

Solo CERCA y LEJOS pertenecen al `enum`. CRÍTICO es una condición lógica; modo paseo es un booleano. No existe comparación del identificador leído contra una lista autorizada. Las cinco evaluaciones pueden reutilizar una misma muestra RSSI.

La condición crítica acciona LED rojo y buzzer, pero el bloque actual no restablece explícitamente ambas salidas en todos los caminos al volver a CERCA o activar modo paseo. Este comportamiento requiere comprobación en banco antes de atribuir silencio físico garantizado a esas transiciones.

## Nodo de salida

| Elemento | Comportamiento del código |
|---|---|
| Inicio | RSSI filtrado −84 dBm; alarma desactivada |
| Activación | RSSI ≥ −65 dBm durante diez evaluaciones, sin bloqueo ni alarma previa |
| Alarma | Permanece activa hasta restablecimiento RFID; salidas alternan cada 150 ms |
| Lectura PN532 | Detecta tarjeta ISO14443A; no compara UID autorizado |
| Restablecimiento | Con alarma activa y cumplido el intervalo RFID, apaga alarma, reinicia contador y RSSI |
| Exclusión | Inhibe disparo RSSI durante 6000 ms después del restablecimiento; rearme automático |

La exclusión no se activa por toda lectura: depende de que exista una alarma activa. Los diez conteos corresponden a ciclos, no necesariamente a diez tramas independientes. No existe en este sketch una segunda etapa de alarma a −50 dBm.

## Telemetría

Área publica `rssiArea`, `estadoPaciente`, `alarmaCritica`, `modoPaseoCloud` y `pacienteLejos`. Salida publica `rssiPuerta`, `alarmaPuerta` y `estadoPuerta`. Se registran como propiedades de lectura con intervalo de un segundo. El código no demuestra Wi-Fi activado exclusivamente por eventos ni una estrategia explícita de suspensión de la radio.

Los umbrales son parámetros de la V1. El RSSI cambia con orientación, obstáculos y entorno; no se convierte en distancia ni se usa Bluetooth para la detección en estos sketches.
