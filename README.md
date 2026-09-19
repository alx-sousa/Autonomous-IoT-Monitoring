# Sistema de monitoreo de presencia y alerta local en camilla hospitalaria

Sistema desarrollado durante una residencia profesional de seis meses en el **Hospital General Dr. Desiderio G. Rosado Carbajal**, Comalcalco, Tabasco.

El proyecto utiliza **ESP32-C6**, comunicación **ESP-NOW**, identificación RFID, procesamiento de RSSI y telemetría mediante **Arduino IoT Cloud** para implementar un sistema distribuido de monitoreo de presencia y generación de alertas locales.

La detección y las alertas principales se ejecutan directamente en los nodos. La conexión a la plataforma IoT funciona como canal secundario de monitoreo.

> **Nota de seguridad:** las credenciales de Wi-Fi y Arduino IoT Cloud se mantienen fuera del repositorio mediante archivos locales `secrets.h`.

## Objetivo

Desarrollar e integrar un sistema electrónico inalámbrico capaz de monitorear la proximidad de un transmisor móvil respecto a diferentes zonas, identificar accesos autorizados mediante RFID y generar indicaciones y alertas locales.

## Funciones principales

- Comunicación inalámbrica entre nodos mediante **ESP-NOW**.
- Estimación de proximidad mediante **RSSI**.
- Filtrado EMA para suavizar las lecturas.
- Confirmación mediante lecturas consecutivas e histéresis para reducir cambios de estado por fluctuaciones.
- Identificación RFID para gestionar un traslado autorizado.
- Monitoreo de una zona de salida mediante **PN532**.
- Indicadores locales mediante OLED, LED y buzzer.
- Telemetría secundaria mediante **Arduino IoT Cloud**.
- Firmware separado por función: transmisor, nodo de área y nodo de salida.

## Arquitectura

El sistema está compuesto por tres nodos principales:

1. **Transmisor móvil:** envía tramas ESP-NOW a los receptores y cambia de canal para realizar la comunicación con los nodos.
2. **Nodo de área / camilla:** procesa RSSI y RFID de 125 kHz, determina el estado de proximidad y genera alertas locales.
3. **Nodo de salida:** procesa RSSI y RFID de 13.56 MHz para gestionar una condición de alarma en la zona de salida.

La arquitectura prioriza el procesamiento local para las funciones de detección y alerta. La plataforma IoT se utiliza para visualización y telemetría, no como dependencia principal de la lógica de alarma.

## Participación en el proyecto

Durante la residencia profesional participé en el desarrollo e integración del sistema, incluyendo:

- Programación de microcontroladores ESP32-C6.
- Implementación de comunicación inalámbrica mediante ESP-NOW.
- Procesamiento de RSSI y lógica de detección.
- Integración de lectores RFID.
- Integración de indicadores y dispositivos electrónicos.
- Diseño e integración de PCB.
- Implementación de telemetría mediante Arduino IoT Cloud.
- Pruebas y validación funcional del prototipo.

## Tecnologías

| Área | Tecnologías |
|---|---|
| Microcontroladores | ESP32-C6 |
| Comunicación | ESP-NOW, Wi-Fi |
| IoT | Arduino IoT Cloud |
| Identificación | RDM6300, PN532 |
| Interfaz | OLED 128x64, LED RGB, buzzer |
| Procesamiento | RSSI, filtro EMA, máquina de estados, histéresis |
| Programación | C/C++ para Arduino |
| Alimentación | LiPo 3.7 V, TP4056, MT3608 |

## Hardware

### Nodo de área / camilla

| Componente | Interfaz / pin | Función |
|---|---|---|
| RDM6300 | UART RX GPIO17 | Lectura RFID de baja frecuencia |
| OLED | I²C SDA GPIO7 / SCL GPIO6 | Estado local |
| Buzzer | GPIO19 | Alerta acústica |
| LED RGB | GPIO14, GPIO15, GPIO18 | Indicadores de estado |

### Nodo de salida

| Componente | Interfaz / pin | Función |
|---|---|---|
| PN532 | I²C SDA GPIO7 / SCL GPIO6 | Identificación RFID |
| OLED | I²C SDA GPIO7 / SCL GPIO6 | Estado local |
| LED de alarma | GPIO20 | Indicador de alarma |
| Buzzer | GPIO19 | Alerta acústica |

## Procesamiento de RSSI

Las lecturas RSSI se suavizan mediante un filtro de media móvil exponencial (EMA):

`RSSI_filtrado = alpha × RSSI_actual + (1 - alpha) × RSSI_anterior`

En el firmware actual se utiliza **alpha = 0.20**.

La decisión de estado no depende de una sola lectura. Se utilizan lecturas consecutivas para confirmar determinadas condiciones y evitar cambios de estado provocados por fluctuaciones momentáneas de la señal.

## Identificación RFID

Se utilizan dos tecnologías RFID según el nodo:

- **RDM6300:** 125 kHz en el nodo de área.
- **PN532:** 13.56 MHz mediante I²C en el nodo de salida.

El nodo de salida incorpora una ventana temporal de exclusión de **6 segundos** después de una lectura RFID válida para evitar que la misma autorización provoque una nueva alarma inmediatamente.

## Estructura del repositorio

```text
Monitoreo-Camilla-IoT/
├── README.md
├── .gitignore
├── firmware/
│   ├── transmitter/
│   │   └── transmitter.ino
│   ├── area_node/
│   │   ├── area_node.ino
│   │   └── secrets.example.h
│   └── exit_node/
│       ├── exit_node.ino
│       └── secrets.example.h
└── docs/
    ├── architecture.md
    ├── testing.md
    └── images/
```

## Instalación

### 1. Preparar las credenciales

En los directorios `firmware/area_node/` y `firmware/exit_node/`:

1. Copia `secrets.example.h`.
2. Renombra la copia a `secrets.h`.
3. Introduce las credenciales correspondientes a cada dispositivo.
4. No subas `secrets.h` al repositorio.

### 2. Librerías

Instala las librerías requeridas desde el entorno de Arduino:

- ArduinoIoTCloud
- Arduino_ConnectionHandler
- Adafruit GFX Library
- Adafruit SSD1306
- Adafruit PN532

Las librerías de ESP-NOW, Wi-Fi y Wire forman parte del entorno ESP32.

### 3. Cargar el firmware

Abre cada sketch de forma independiente y selecciona la placa ESP32-C6 correspondiente.

## Documentación

La documentación se ampliará progresivamente con material real del proyecto:

- Diagrama de arquitectura.
- Diagrama de comunicación.
- Fotografías del prototipo y de los nodos.
- Fotografías de PCB y montaje.
- Evidencia de pruebas.
- Diagrama de conexiones.
- Video de demostración, si se dispone de uno.

## Limitaciones

- La estimación mediante RSSI depende del entorno físico, orientación y obstáculos.
- Los umbrales deben calibrarse para la instalación concreta.
- La telemetría depende de la disponibilidad de la red Wi-Fi y del servicio IoT.
- Este repositorio documenta un prototipo académico/profesional y no representa un dispositivo médico certificado.

## Autor

**Luis Alejandro Pérez Sousa**

Ingeniería en Mecatrónica · Electrónica · Sistemas embebidos · IoT · Automatización
