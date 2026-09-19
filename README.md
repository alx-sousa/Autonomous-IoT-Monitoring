# Sistema de monitoreo de presencia y alerta local en camilla hospitalaria

Sistema de monitoreo desarrollado durante una residencia profesional de seis meses en el **Hospital General Dr. Desiderio G. Rosado Carbajal**, utilizando **ESP32-C6**, comunicación **ESP-NOW**, identificación RFID y telemetría mediante **Arduino IoT Cloud**.

El proyecto combina procesamiento local, comunicación inalámbrica y dispositivos electrónicos para detectar cambios de proximidad y generar alertas locales ante condiciones configuradas.

> **Nota de seguridad:** las credenciales de Wi-Fi y Arduino IoT Cloud se mantienen fuera del repositorio. Consulta la sección de instalación para configurar el firmware.

## Funciones principales

- Comunicación inalámbrica entre nodos mediante ESP-NOW.
- Estimación de proximidad mediante RSSI.
- Filtrado EMA para suavizar las lecturas.
- Lógica de confirmación e histéresis para reducir activaciones por fluctuaciones.
- Identificación RFID para gestionar un traslado autorizado.
- Nodo de salida con lector PN532.
- Indicadores locales mediante OLED, LED y buzzer.
- Telemetría secundaria mediante Arduino IoT Cloud.
- Firmware separado por función: transmisor, nodo de área y nodo de salida.

## Arquitectura

El sistema está compuesto por tres nodos principales:

1. **Transmisor móvil:** envía tramas ESP-NOW a los receptores.
2. **Nodo de área / camilla:** procesa RSSI y RFID de 125 kHz, y genera alertas locales.
3. **Nodo de salida:** procesa RSSI y RFID de 13.56 MHz para gestionar una condición de alarma en la zona de salida.

La detección y las alertas principales se ejecutan localmente en los nodos; la conexión a la plataforma IoT se utiliza como canal de monitoreo secundario.

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

## Hardware documentado

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

La decisión de estado no depende de una sola lectura: se utilizan lecturas consecutivas para confirmar determinadas condiciones y evitar cambios de estado por fluctuaciones momentáneas.

## RFID

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

Las carpetas de documentación e imágenes se irán completando con material real del proyecto.

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

## Documentación pendiente

- Diagrama de arquitectura del sistema.
- Fotografías del prototipo y de los nodos.
- Fotografías de PCB y montaje.
- Evidencia de pruebas.
- Video de demostración, si se dispone de uno.
- Diagrama de conexiones detallado.

## Limitaciones

- La estimación mediante RSSI depende del entorno físico, orientación y obstáculos.
- Los umbrales deben calibrarse para la instalación concreta.
- La telemetría depende de la disponibilidad de la red Wi-Fi y del servicio IoT.
- Este repositorio documenta un prototipo académico/profesional y no representa un dispositivo médico certificado.

## Autor

**Luis Alejandro Pérez Sousa**

Ingeniería en Mecatrónica · Electrónica · Sistemas embebidos · IoT · Automatización
