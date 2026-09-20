# Revisión del firmware

Este documento resume la revisión técnica del firmware publicado en el repositorio. La revisión se realizó conservando el comportamiento funcional documentado del prototipo.

## Estructura

El firmware está dividido por responsabilidad:

- `transmitter/transmitter.ino`: transmisión ESP-NOW hacia los receptores.
- `area_node/area_node.ino`: RSSI, máquina de estados, RDM6300, OLED, alertas y telemetría.
- `exit_node/exit_node.ino`: RSSI, PN532, alarma de salida y telemetría.

## Aspectos implementados

### Transmisor

El transmisor recorre los canales Wi-Fi 1–11 y actualiza el canal configurado para ambos peers antes de transmitir. En cada canal envía dos ráfagas a los dos receptores.

### Nodo de área

El nodo de área implementa:

- filtro EMA con `alpha = 0.20`;
- estados `CERCA` y `LEJOS`;
- histéresis mediante umbrales separados;
- confirmación de 5 lecturas para transición a `LEJOS`;
- condición crítica por RSSI;
- lectura del RDM6300 mediante UART;
- validación de checksum de la trama RFID;
- modo paseo;
- OLED, LED RGB y buzzer;
- publicación de variables en Arduino IoT Cloud.

### Nodo de salida

El nodo de salida implementa:

- filtro EMA con `alpha = 0.20`;
- confirmación de 10 lecturas antes de activar la alarma;
- lectura PN532 mediante I²C;
- restablecimiento mediante RFID;
- exclusión temporal de RSSI durante 6 segundos después del restablecimiento;
- alarma temporizada mediante `millis()`;
- publicación de variables en Arduino IoT Cloud.

## Seguridad de credenciales

Las credenciales Wi-Fi y de Arduino IoT Cloud no se almacenan en los sketches públicos. Cada receptor utiliza un archivo local `secrets.h`, excluido mediante `.gitignore`, y el repositorio proporciona `secrets.example.h` como plantilla.

## Observaciones de código

La revisión identificó oportunidades de mejora que se mantienen documentadas en lugar de modificar automáticamente el firmware validado:

1. **Direcciones MAC del transmisor.** Actualmente están escritas directamente en `transmitter.ino`. No son contraseñas, pero pueden trasladarse a un archivo de configuración si se desea publicar una versión más genérica.

2. **Uso de `delay()`.** El transmisor utiliza retardos breves como parte de su secuencia de envío. El nodo de área también utiliza un retardo corto para la confirmación acústica RFID y un `delay(20)` al final del ciclo. Una evolución futura podría convertir estas tareas a temporización no bloqueante.

3. **Inicialización del RSSI.** Los receptores arrancan con valores RSSI predefinidos antes de recibir la primera trama. Una versión futura podría incorporar una bandera de `primeraLectura` para inicializar el EMA con la primera muestra real.

4. **Validación de errores.** Algunas llamadas de inicialización, como la pantalla OLED o determinadas operaciones ESP-NOW, podrían tener manejo de error más completo.

5. **Constantes.** Los umbrales y tiempos pueden agruparse en una sección de configuración o archivo dedicado para facilitar calibración y mantenimiento.

6. **Nombres y tipos.** Los valores que no cambian durante la ejecución pueden declararse con tipos y constantes más explícitos (`constexpr`, `uint32_t`, etc.) en una futura refactorización.

## Decisión para la versión de portafolio

No se realizó una refactorización agresiva del firmware porque el código publicado representa el prototipo probado durante la residencia. Cambiar su estructura sin repetir las pruebas podría hacer que el repositorio dejara de representar exactamente la versión validada.

Por ello, la versión actual prioriza:

- fidelidad al prototipo;
- separación clara por nodo;
- eliminación de credenciales públicas;
- documentación técnica;
- trazabilidad entre firmware, arquitectura y resultados.

## Mejoras futuras

Una siguiente versión del sistema podría incorporar:

- configuración externa de MAC y parámetros de calibración;
- temporización completamente no bloqueante;
- detección explícita de pérdida de paquetes o timeout del transmisor;
- encapsulación de la lógica RSSI en funciones o clases reutilizables;
- registro estructurado de eventos;
- pruebas unitarias de funciones independientes como checksum y transiciones de estado.

Estas mejoras se consideran evolución del proyecto y no resultados ya implementados o validados.
