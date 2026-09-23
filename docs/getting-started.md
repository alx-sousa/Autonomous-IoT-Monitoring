# Puesta en marcha de la V1

El repositorio conserva el firmware del prototipo con una corrección de declaración de conexión Cloud. No hay un entorno de compilación fijado ni una validación de hardware repetida para esta revisión. Esta guía permite preparar una reproducción, no garantiza una carga inmediata en cualquier placa.

## 1. Preparar el entorno

Usar Arduino IDE y soporte de placas ESP32 compatible con la placa ESP32-C6 concreta. Las versiones originales del core y bibliotecas no están registradas; anotar las versiones elegidas al compilar. El callback ESP-NOW usa la interfaz `esp_now_recv_info`; un error de firma requiere revisar la compatibilidad del core.

Bibliotecas utilizadas:

- ArduinoIoTCloud y Arduino_ConnectionHandler.
- Adafruit GFX Library y Adafruit SSD1306.
- Adafruit PN532 para salida.
- WiFi, ESP-NOW, Wire y HardwareSerial del entorno ESP32.

## 2. Elegir el sketch

| Dispositivo | Archivo |
|---|---|
| Transmisor | `firmware/transmitter/transmitter.ino` |
| Área | `firmware/area_node/area_node.ino` |
| Salida | `firmware/exit_node/exit_node.ino` |

Abrir y compilar cada sketch por separado. Las carpetas tienen el mismo nombre que su archivo `.ino`.

## 3. Configurar credenciales y destinos

En cada receptor, copiar `secrets.example.h` como `secrets.h` en la misma carpeta. Completar SSID, contraseña y credenciales propias del dispositivo Arduino IoT Cloud. No reutilizar valores históricos del informe ni subir el archivo local: está excluido en `.gitignore`.

Crear la configuración Cloud correspondiente con las propiedades y tipos de `initProperties()`; consultar [communication.md](communication.md). La declaración del objeto de conexión está en el sketch y toma los valores del archivo local.

En el transmisor, reemplazar `receptor1` y `receptor2` por las MAC de estación de los receptores utilizados. Las MAC publicadas son referencias del montaje original, no contraseñas. El barrido de canales no evita por sí solo pérdidas por coexistencia Wi-Fi/ESP-NOW.

## 4. Verificar hardware y compilar

Revisar [hardware/README.md](../hardware/README.md): placa exacta, GPIO expuestos, tensiones, configuración PN532 y etapa de alimentación. Las figuras del informe no son esquemas de fabricación verificados.

Compilar los tres sketches y registrar core, bibliotecas, modelo de placa y resultados. No se incluye una afirmación de compilación exitosa en esta revisión porque no se ejecutó el toolchain ni se dispone de los dispositivos.

## 5. Comprobar en banco

1. Confirmar arranque, OLED, lectura RFID y salidas de cada receptor.
2. Verificar recepción y RSSI con el transmisor cerca antes de calibrar.
3. Repetir alejamiento/retorno y comprobar salidas físicas, especialmente en área.
4. Comprobar alarma de salida, restablecimiento por tarjeta y rearme tras 6 s.
5. Desconectar transmisor y Wi-Fi por separado; registrar diferencias entre estado lógico, salidas y telemetría.
6. Registrar resultados con el protocolo propuesto en [testing.md](testing.md).

No conectar esta reproducción a un flujo de atención clínica basándose únicamente en el repositorio; su alcance es experimental y sus límites técnicos están documentados.
