# Sistema de Monitoreo de Presencia y Alerta Local en Camilla Hospitalaria (Edge IoT)

Este repositorio contiene el ecosistema de firmware y la arquitectura de hardware desarrollados durante una estancia de residencia profesional de 6 meses en el **Hospital General "Dr. Desiderio G. Rosado Carbajal"**. El sistema mitiga los riesgos asociados con la movilidad no supervisada y el egreso no autorizado de pacientes mediante el paradigma de computación en el borde (**Edge IoT**), utilizando el SoC **ESP32-C6**.

## Arquitectura del Sistema (Descentralizada)
El sistema opera de forma asimétrica mediante una topología punto a punto (**Peer-to-Peer**) independiente de la infraestructura de red local del hospital, garantizando una operación crítica ininterrumpida ante caídas de telecomunicaciones externas:

*   **Transmisor Móvil (Brazalete):** Ejecuta un algoritmo de salto cíclico de canales (1 al 11) vía **ESP-NOW** para asegurar la entrega de tramas optimizando el consumo energético de la batería LiPo.
*   **Nodo de Área (Camilla):** Supervisa el perímetro inmediato calculando la atenuación de la señal (**RSSI**). Integra un módulo RFID de baja frecuencia (**125 kHz - RDM6300**) para traslados autorizados.
*   **Nodo de Salida (Zona Crítica):** Funciona como una barrera restrictiva ante intentos de evasión inminente utilizando un lector RFID de alta frecuencia (**13.56 MHz - PN532** bajo bus I²C).

## 🛠️ Especificaciones de Hardware y Pines

### Distribución del Nodo de Área / Camilla

| Componente periférico | Interfaz física / Pin ESP32-C6 | Función en el sistema |
| :--- | :--- | :--- |
| **Lector RDM6300** | UART (RX Pin 17) | Validación de presencia pasiva (Etiquetas EM4100) |
| **Pantalla OLED 0.96"** | I²C (SDA Pin 7, SCL Pin 6) | Interfaz gráfica local de estados en tiempo real |
| **Buzzer Activo** | GPIO Pin 19 (vía Transistor BJT) | Alerta acústica progresiva por alejamiento |
| **LED RGB** | GPIO Pins 14, 15, 18 | Indicadores ópticos de estado (Cerca/Lejos/Crítico) |

### Etapa de Potencia y Gestión de Energía
*   **Alimentación Principal:** Batería LiPo 3.7V / Fuente externa dual 5V.
*   **Gestión de Carga:** Módulo **TP4056** con protección integrada contra sobredescarga profunda.
*   **Regulación:** Convertidor conmutado elevador **MT3608** ajustado de manera estática a 5V estables.

## Algoritmos Implementados en el Borde

### 1. Filtro Digital de Suavizado Exponencial (EMA)
Para disipar el ruido electromagnético de alta frecuencia y las fluctuaciones dinámicas por multitrayectoria en interiores (variaciones de hasta ±15 dBm), el firmware procesa las lecturas de potencia recursivamente mediante la ecuación de tiempo discreto:

`RSSI_filtrado = (RSSI_actual * alpha) + (RSSI_anterior * (1.0 - alpha))`

Calibrado experimentalmente con un factor α = 0.20, el filtro deforma y estabiliza la señal, atenuando las fluctuaciones abruptas provocadas por reflexiones del entorno o movimientos del usuario, manteniendo el tiempo promedio de respuesta de las alarmas en **2.2 segundos**.

### 2. Lógica de Histéresis y Máquina de Estados Finitos (FSM)
Se implementaron umbrales de decisión diferenciados acoplados a buffers de confirmación secuencial (5 a 10 lecturas fuera de rango) para suprimir falsas alarmas provocadas por atenuaciones temporales en el entorno clínico.

### 3. Ventana Táctica de Exclusión
El nodo de salida gestiona temporizaciones asíncronas no bloqueantes (`millis()`). Al autenticar una tarjeta médica autorizada (ISO14443A), se habilita una ventana de exclusión temporal de **6 segundos** para el cruce seguro del paciente, incorporando un mecanismo de rearme automático.

## ☁️ Telemetría Secundaria (Monitoreo Pasivo)
Las alertas consolidadas en el borde se transmiten de forma asíncrona mediante el transceptor Wi-Fi hacia la plataforma **Arduino IoT Cloud** y servidores locales de TI, alimentando tableros gráficos de tendencia temporal para la supervisión remota en estaciones de enfermería.
