# Revisión del firmware publicado

Revisión estática de la V1 contrastada con el informe final. No incluye compilación, ejecución en hardware ni certificación. Las diferencias se documentan para mantener trazabilidad entre intención de diseño, implementación y resultados reportados.

## Implementación confirmada

- Transmisor: dos destinos ESP-NOW, dos envíos por destino y canal, barrido 1–11.
- Área: EMA 0.20, estados CERCA/LEJOS, histéresis, contador, condición crítica, parser RDM6300 y checksum.
- Salida: EMA 0.20, contador, alarma enclavada, alternancia por `millis()` y exclusión de 6 s tras restablecimiento de alarma.
- Receptores: OLED y propiedades de telemetría Arduino IoT Cloud.

## Diferencias relevantes

| Descripción del informe | Evidencia en el código publicado |
|---|---|
| Cinco/diez muestras consecutivas | Contadores en `loop()`; pueden contar repetidamente el mismo RSSI |
| Autorización por identidad RFID | Área valida formato/checksum; salida detecta tarjeta; no hay lista de UID autorizados |
| Filtrado MAC bidireccional | El transmisor configura destinos; callbacks receptores no filtran origen |
| Estado crítico de salida a −50 dBm | No existe ese umbral ni segunda etapa en `exit_node.ino` |
| Alerta preventiva azul e intermitente en área | No está implementada como tal en el lazo publicado |
| Wi-Fi activado solo para notificar eventos | Cloud se atiende en cada ciclo; no hay estrategia explícita de suspensión por eventos |
| Suspensión física de alarmas al autorizar o regresar | Área no restablece explícitamente las salidas en todos esos caminos |
| Operación completamente asíncrona | Hay `delay()` en transmisor y área; la alarma de salida sí se temporiza con `millis()` |

## Límites técnicos a comprobar en banco

1. **Antigüedad del RSSI:** no se registra timeout de tramas ni se inicializa el filtro con la primera muestra real.
2. **Salidas del nodo de área:** revisar LED/buzzer al abandonar la condición crítica, activar modo paseo y retornar a CERCA.
3. **PN532:** comprobar constructor de la biblioteca, pines auxiliares y cableado; `Wire.begin()` no valida por sí solo la inicialización completa del lector.
4. **Concurrencia:** el callback actualiza RSSI compartido con `loop()` sin mecanismo explícito de sincronización.
5. **Temporizadores:** `ahora > tiempoDesbloqueo` requiere revisar el comportamiento al desbordarse `millis()`.
6. **Manejo de fallos:** algunas inicializaciones continúan después de un error o no comprueban retornos.
7. **Enlace:** ESP-NOW se configura sin cifrado; no se verifica origen o carga útil en recepción.

Estas observaciones no se presentan como fallos medidos durante la residencia: proceden de la lectura del código. Las pruebas históricas y sus límites están en [testing.md](testing.md).

## Cambios de mantenimiento de esta revisión

- Se consolidó el punto de entrada en `firmware/`, retirando tres copias redundantes de la raíz; dos contenían credenciales incrustadas.
- Se restauró en ambos receptores la declaración `WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID_WIFI, PASS_WIFI);`, presente en los originales pero ausente en los sketches organizados. Los valores permanecen en `secrets.h` local.
- Se conservaron algoritmos, umbrales, GPIO y temporizaciones históricos. La restauración de la declaración no equivale a una compilación ni una validación física.

El historial anterior sigue existiendo. Las credenciales previamente expuestas deben rotarse; véase [SECURITY.md](../SECURITY.md).
