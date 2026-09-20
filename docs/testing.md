# Pruebas y validación

Las pruebas documentadas en esta sección corresponden a la evaluación experimental reportada durante la residencia profesional. Se realizaron pruebas de proximidad, comunicación, alertas, RFID, alimentación y telemetría sobre el prototipo integrado.

## Metodología de prueba

Para evaluar el comportamiento de los nodos se realizaron desplazamientos controlados del transmisor en un rango aproximado de **3 m a 20 m**.

En el nodo de área se observaron las transiciones entre los estados de proximidad configurados. En el nodo de salida se evaluó la detección del transmisor al aproximarse a la zona definida, considerando también obstáculos e infraestructura del entorno.

Durante la calibración del RSSI se evaluó inicialmente un factor EMA de 0.10. Debido al retardo observado, el firmware final utilizó **alpha = 0.20** como compromiso entre suavizado y velocidad de respuesta.

## Resultados generales

| Prueba | Resultado reportado |
|---|---:|
| Tiempo promedio de detección | 2 s |
| Tiempo promedio de activación de alarmas | 2.2 s |
| Distancia máxima con RSSI estable | 11–17 m |
| Falsas alarmas | 1 de 20 pruebas |
| Autonomía con batería | 4.9 h |

Estos valores corresponden a las condiciones experimentales del prototipo y **no deben interpretarse como especificaciones universales**. El RSSI y el alcance dependen del entorno, obstáculos, orientación y condiciones radioeléctricas.

## Nodo de área / camilla

El nodo de área utilizó RSSI filtrado mediante EMA y lógica de histéresis.

Parámetros documentados durante las pruebas:

| Parámetro | Valor |
|---|---:|
| Umbral de advertencia por alejamiento | -66 dBm |
| Umbral de retorno a zona segura | -59 dBm |
| Umbral crítico | -84 dBm |
| Confirmación para transición a LEJOS | 5 lecturas |
| Factor EMA | 0.20 |

La separación entre los umbrales de activación y recuperación permite introducir histéresis y reducir cambios repetitivos de estado alrededor de un único límite.

## Nodo de salida

El nodo de salida combina la evaluación de RSSI con identificación mediante **PN532**. Una lectura RFID válida permite desactivar la alerta y habilita una ventana temporal de exclusión de **6 segundos** para el cruce autorizado.

## Comunicación ESP-NOW

La evaluación se realizó con una arquitectura formada por **tres ESP32-C6**:

- un transmisor móvil;
- un nodo receptor de área;
- un nodo receptor de salida.

La comunicación se implementó mediante ESP-NOW y direcciones MAC registradas. Los nodos receptores utilizan el RSSI asociado a las tramas recibidas como entrada para la lógica de proximidad.

> Las direcciones MAC concretas del prototipo no se reproducen en esta documentación pública.

## RFID

Durante la validación se realizaron pruebas independientes con:

- **RDM6300 (125 kHz)** en el nodo de área;
- **PN532 (13.56 MHz / ISO14443A)** en el nodo de salida.

Las pruebas verificaron la lectura de las credenciales utilizadas por el prototipo y su interacción con la lógica local de los nodos.

## Alimentación

El prototipo fue evaluado utilizando batería LiPo y alimentación externa.

La etapa de energía documentada incluye:

- batería LiPo;
- módulo TP4056 para carga/protección;
- regulador elevador MT3608 ajustado a 5 V;
- alimentación externa de 5 V.

Durante las pruebas se reportó operación estable con ambas fuentes y transición de alimentación sin reinicio del sistema.

## Telemetría

Los nodos receptores fueron vinculados a la capa de supervisión para visualizar variables y eventos. También se realizaron pruebas con **Arduino IoT Cloud**, incluyendo la representación del comportamiento RSSI y los estados de alerta de los nodos.

La telemetría es complementaria: la evaluación de RSSI, la máquina de estados y la activación de alertas se ejecutan localmente.

## Alcance de los resultados

Los resultados documentan el comportamiento de un **prototipo desarrollado y evaluado durante la residencia profesional**. No constituyen certificación de dispositivo médico ni validación clínica.

Para reproducir las pruebas en otra instalación es necesario recalibrar los umbrales de RSSI y considerar las características físicas y radioeléctricas del entorno.
