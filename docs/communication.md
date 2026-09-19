# Comunicación y lógica del sistema

## Comunicación inalámbrica

La comunicación entre el transmisor móvil y los nodos receptores se realiza mediante **ESP-NOW**, un protocolo de comunicación inalámbrica entre dispositivos ESP32 que permite el intercambio directo de datos sin utilizar un servidor como intermediario.

El transmisor envía tramas a los nodos configurados y realiza un recorrido por los canales Wi-Fi utilizados por el sistema. Los receptores utilizan la información recibida, incluyendo el **RSSI**, como referencia para estimar la proximidad del transmisor.

## Estimación mediante RSSI

El **Received Signal Strength Indicator (RSSI)** representa la intensidad de la señal recibida. En este proyecto se utiliza como una referencia de proximidad, no como una medición directa de distancia.

La señal puede variar debido a obstáculos, orientación de las antenas, interferencias y características del entorno. Por esta razón, el firmware no toma decisiones basándose en una lectura aislada.

## Filtrado EMA

Para suavizar las variaciones de RSSI se utiliza un filtro de media móvil exponencial (EMA):

`RSSI_filtrado = alpha × RSSI_actual + (1 - alpha) × RSSI_anterior`

El firmware utiliza:

`alpha = 0.20`

Un valor menor de alpha da mayor peso al historial de lecturas, ayudando a reducir cambios bruscos en la señal.

## Confirmación de estados e histéresis

La lógica de detección utiliza estados y lecturas consecutivas para evitar que una fluctuación momentánea del RSSI provoque un cambio inmediato de estado.

En el nodo de área se manejan estados de proximidad como **CERCA** y **LEJOS**, utilizando umbrales diferentes para la activación y recuperación. Esta separación constituye una forma de histéresis.

La confirmación mediante varias lecturas consecutivas proporciona una segunda capa de estabilidad antes de modificar el estado del sistema.

## Identificación RFID

El sistema utiliza RFID en dos puntos con diferentes tecnologías:

- **RDM6300:** lector de 125 kHz utilizado en el nodo de área.
- **PN532:** lector de 13.56 MHz utilizado en el nodo de salida mediante I²C.

La identificación RFID permite distinguir una interacción autorizada dentro de la lógica definida por el firmware.

En el nodo de salida, una lectura RFID válida activa una ventana temporal de exclusión para evitar que la misma autorización provoque inmediatamente una nueva condición de alarma.

## Gestión de alarmas

Las alertas se generan localmente mediante indicadores visuales y acústicos:

- OLED para información de estado.
- LED para indicación visual.
- Buzzer para alerta acústica.

La gestión temporal de las alarmas utiliza `millis()` en lugar de depender exclusivamente de esperas bloqueantes, permitiendo que el firmware continúe atendiendo otras tareas durante la operación.

## Telemetría

Los nodos receptores pueden conectarse a **Arduino IoT Cloud** mediante Wi-Fi para publicar variables de monitoreo.

Esta comunicación se considera secundaria respecto a la lógica local. La pérdida de conexión con la plataforma IoT no sustituye ni representa por sí misma la lógica de detección implementada en los nodos.

## Separación de responsabilidades

| Nodo | Responsabilidad principal |
|---|---|
| Transmisor móvil | Emitir tramas ESP-NOW |
| Nodo de área | Proximidad mediante RSSI + identificación RFID + alertas locales |
| Nodo de salida | Proximidad mediante RSSI + identificación RFID + alertas locales |
| Arduino IoT Cloud | Telemetría y visualización secundaria |

## Consideraciones

El RSSI depende de las condiciones físicas y radioeléctricas del entorno. Por ello, los umbrales utilizados en el firmware corresponden a una configuración concreta del prototipo y deben validarse y calibrarse cuando cambien las condiciones de instalación.

Este documento describe el funcionamiento implementado en el firmware actual; los resultados cuantitativos del sistema se documentarán por separado utilizando evidencia de pruebas reales.
