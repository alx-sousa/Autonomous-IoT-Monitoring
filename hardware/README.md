# Hardware, BOM y conexiones

Este documento resume los componentes e interfaces utilizados en el prototipo. La información se basa en el diseño electrónico y el firmware implementado durante la residencia profesional.

## Lista de materiales (BOM)

| Categoría | Componente | Función |
|---|---|---|
| Procesamiento | ESP32-C6 Mini | Lógica embebida, RSSI, ESP-NOW y conectividad |
| RFID HF | PN532, 13.56 MHz | Identificación en el nodo de salida |
| RFID LF | RDM6300, 125 kHz | Identificación en el nodo de área |
| Interfaz | OLED 0.96" I²C | Visualización local |
| Alerta acústica | Buzzer activo + transistor BJT | Generación y conmutación de alerta |
| Indicadores | LED RGB / LED estándar | Representación visual de estados |
| Alimentación | Batería LiPo 3.7 V | Alimentación portátil |
| Gestión de carga | TP4056 | Carga y protección de la celda LiPo |
| Regulación | MT3608 Step-Up | Elevación y ajuste de alimentación a 5 V |
| Pasivos | Resistencias y capacitores | Filtrado, polarización y acondicionamiento eléctrico |
| Mecánica | Carcasa impresa en PLA | Integración y protección física del prototipo |
| Interconexión | PCB diseñada para el prototipo | Integración eléctrica de módulos y componentes |

> Las cantidades dependen del nodo. No se presenta una cantidad global única porque los módulos RFID y elementos de interfaz no son idénticos en las tres unidades.

## Distribución por nodo

### Transmisor móvil

Su función principal es transmitir tramas ESP-NOW hacia los receptores registrados.

Componentes principales:

- ESP32-C6.
- Alimentación portátil.
- Etapa de carga/regulación correspondiente al prototipo.

### Nodo de área / camilla

Componentes e interfaces implementados:

| Elemento | Interfaz / GPIO |
|---|---|
| RDM6300 | UART RX — GPIO17 |
| OLED | I²C — SDA GPIO7 / SCL GPIO6 |
| Buzzer | GPIO19 |
| LED RGB | GPIO14 / GPIO15 / GPIO18 |
| ESP-NOW | Radio 2.4 GHz del ESP32-C6 |
| Wi-Fi / IoT | Radio integrada del ESP32-C6 |

El RDM6300 utiliza comunicación serie para entregar las tramas RFID al microcontrolador. La pantalla OLED comparte el bus I²C definido para la interfaz local.

### Nodo de salida

| Elemento | Interfaz / GPIO |
|---|---|
| PN532 | I²C — SDA GPIO7 / SCL GPIO6 |
| OLED | I²C — SDA GPIO7 / SCL GPIO6 |
| LED de alarma | GPIO20 |
| Buzzer | GPIO19 |
| ESP-NOW | Radio 2.4 GHz del ESP32-C6 |
| Wi-Fi / IoT | Radio integrada del ESP32-C6 |

El PN532 opera mediante I²C y permite validar credenciales RFID/NFC en la lógica del nodo de salida.

## Arquitectura de alimentación

La etapa de energía del prototipo utiliza una batería **LiPo de 3.7 V**, un módulo **TP4056** para gestión de carga/protección y un convertidor **MT3608** para obtener una alimentación regulada de 5 V requerida por los módulos correspondientes.

```text
Batería LiPo 3.7 V
        │
        ▼
      TP4056
  carga / protección
        │
        ▼
      MT3608
    Step-Up 5 V
        │
        ├── ESP32-C6 / regulación de la placa
        └── periféricos del nodo
```

El diseño contempla líneas de alimentación para periféricos de **5 V y 3.3 V**, de acuerdo con los requerimientos de los módulos integrados.

## Interfaces utilizadas

### I²C

Utilizado para dispositivos como la pantalla OLED y el PN532.

- SDA: GPIO7
- SCL: GPIO6

### UART

Utilizado en el nodo de área para recibir las tramas del RDM6300.

- RX: GPIO17

### Salidas digitales

Se utilizan GPIO para controlar LED e indicadores acústicos. El buzzer se integra mediante una etapa de conmutación con transistor BJT, evitando manejar directamente toda la carga desde el GPIO.

## PCB

Las unidades receptoras fueron integradas mediante PCB diseñadas para el prototipo. El diseño contempló:

- distribución de potencia;
- buses de comunicación;
- GPIO;
- componentes pasivos de filtrado;
- integración de módulos RFID;
- indicadores visuales y acústicos.

El diseño electrónico y las PCB fueron desarrollados en **EasyEDA** antes de la etapa de ensamblaje.

## Consideraciones de reproducción

Este repositorio documenta el hardware utilizado en el prototipo original. Antes de reproducir una placa o conectar módulos equivalentes se deben verificar las tensiones, pinout y características eléctricas de la versión específica de cada componente.

Los GPIO documentados corresponden al firmware actual del proyecto.
