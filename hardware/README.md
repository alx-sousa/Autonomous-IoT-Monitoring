# Hardware e integración de la V1

El informe documenta selección de componentes, diseño en EasyEDA, carcasas en SolidWorks y ensamble físico. Esta sección distingue componentes reportados, pines del firmware y archivos efectivamente disponibles.

## Componentes principales

| Componente | Función / nodo | Evidencia |
|---|---|---|
| ESP32-C6 Mini | Un controlador por nodo; tres en la arquitectura | Informe y firmware |
| RDM6300, 125 kHz | Interacción RFID en área | Informe, UART en firmware |
| PN532, 13.56 MHz | Interacción RFID en salida | Informe, llamadas a biblioteca Adafruit |
| OLED I²C 128×64 | Interfaz local de receptores | Informe y firmware; dirección 0x3C |
| LED RGB / LED | Indicadores de área / salida | Informe y GPIO |
| Buzzer y etapa BJT | Alerta acústica | Informe, tabla 8 y diseño |
| LiPo 3.7 V | Alimentación portátil | Informe; p. 78 menciona 1200 mAh |
| Módulo TP4056 | Carga de batería | Informe; verificar revisión y protección incorporada |
| MT3608 | Elevación de tensión hacia 5 V | Informe |
| Resistencias, capacitores e interconexión | Conmutación, desacoplo y ensamble | Informe, figs. 10–15 y 26–28 |
| Carcasas PLA | Integración mecánica | Informe, figs. 16–25 |

Esta es una lista funcional de componentes, **no una BOM de fabricación completa**. Faltan cantidades y referencias exactas por nodo, valores consolidados, proveedores y costos comprobables.

## Pines definidos en el firmware

| Señal | Nodo de área | Nodo de salida |
|---|---|---|
| I²C SDA / SCL | GPIO7 / GPIO6 | GPIO7 / GPIO6 |
| UART RX RDM6300 | GPIO17, 9600 baud | No aplica |
| Buzzer | GPIO19 | GPIO19 |
| LED azul / verde / rojo | GPIO14 / GPIO15 / GPIO18 | No aplica |
| LED de alarma | No aplica | GPIO20 |

Estos valores son declaraciones de software, no comprobación del cableado real. Confirmar disponibilidad de GPIO, niveles eléctricos y polaridad con la placa exacta antes de conectar periféricos.

**PN532:** `Wire.begin(7, 6)` configura el bus, pero la instancia `Adafruit_PN532 nfc(SDA_PIN, SCL_PIN)` requiere revisar el significado de esos argumentos en la versión instalada de la biblioteca. Los nombres de las macros no prueban que el constructor reciba SDA/SCL. No se presenta esta asignación como conexión completa y validada del PN532.

## Alimentación

El informe describe una LiPo, un módulo de carga TP4056 y un elevador MT3608 ajustado a 5 V, además de alimentación externa. No se publica un esquema de potencia listo para replicar: hacen falta la revisión del módulo, conexiones reales y configuración de carga.

La protección de batería no se da por verificada por el nombre TP4056. Deben identificarse los elementos de protección del módulo concreto y la topología de alimentación bajo carga. La tabla 26 reporta transición sin reinicio en las pruebas históricas; no constituye validación de un circuito de gestión de alimentación reproducible.

## Diseño PCB frente a ensamble documentado

![Diseño histórico del nodo de área](../docs/images/report/pcb-area-design.png)

Figura 12, página 40 del informe. **La huella visible está rotulada ESP32-C3 Super Mini**, mientras que la arquitectura y el firmware publicados se describen para ESP32-C6. La figura se conserva como evidencia del trabajo de diseño, sin afirmar compatibilidad de huella o pinout.

La foto de integración (fig. 28) muestra placas perforadas y módulos cableados. Por tanto, las imágenes disponibles no demuestran que la PCB diseñada fuera la placa fabricada e instalada en el prototipo final. No se incluyen archivos nativos EasyEDA, Gerbers, CAD nativo, STEP ni STL. La documentación visual no debe utilizarse directamente para fabricar una placa.

## Mecánica

Se documenta una carcasa por secciones, fabricada en PLA, con ubicación para periféricos. El informe §4.4 describe ajustes geométricos en la zona RFID y recuperación de lectura de aproximadamente 3–5 cm. Es una observación reportada, sin ensayos de resistencia, limpieza hospitalaria o tolerancias publicados.

[Galería y procedencia de figuras](../docs/evidence.md) · [Puesta en marcha](../docs/getting-started.md)
