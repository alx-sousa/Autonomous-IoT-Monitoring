# Credenciales y alcance de seguridad

## Configuración local

Los receptores leen credenciales desde `secrets.h`. Crear ese archivo a partir de la plantilla correspondiente y mantenerlo fuera de Git. No incluir contraseñas, claves de dispositivo ni datos identificables de pacientes en código, capturas, registros o incidencias públicas.

## Exposición histórica

Las copias antiguas de los receptores ubicadas en la raíz contenían credenciales Wi-Fi y de Arduino IoT Cloud. Se retiraron de la versión actual del repositorio al consolidar el firmware. **La retirada no elimina los valores de commits anteriores ni revoca su acceso.** El propietario debe cambiar las credenciales Wi-Fi afectadas y revocar o regenerar las claves de dispositivo Cloud expuestas.

El informe original también contiene configuración sensible en anexos y por ese motivo no se distribuye íntegro. Una limpieza del historial requeriría una operación separada; no se ha reescrito el historial en esta revisión.

## Límites del prototipo

El firmware no implementa una lista de tarjetas autorizadas, filtrado de MAC de origen en los callbacks ni cifrado ESP-NOW. La interacción RFID del prototipo no debe presentarse como autenticación robusta o control de acceso certificado. Tampoco existe un timeout explícito de pérdida del transmisor.

El repositorio documenta una V1 experimental. Su propósito preventivo no equivale a validación clínica o disponibilidad garantizada. Los límites observados en el código están en [docs/firmware-review.md](docs/firmware-review.md).
