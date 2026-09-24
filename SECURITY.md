# Seguridad y configuración

## Credenciales locales

Los receptores V1 leen sus credenciales desde `secrets.h`, creado a partir de `secrets.example.h` y excluido de Git. No publicar contraseñas, claves Cloud, datos de pacientes ni información de infraestructura interna en código, imágenes, PDFs o incidencias.

## Exposición histórica

Versiones anteriores incluían credenciales Wi-Fi y Arduino IoT Cloud incrustadas. Fueron retiradas de los archivos actuales, pero continúan en commits antiguos. La renovación del portafolio no elimina ese historial ni revoca las credenciales. Su propietario debe cambiar las contraseñas afectadas y regenerar o revocar las claves Cloud. No se ha confirmado su rotación.

La reescritura del historial se prepara por separado de este Pull Request. Debe coordinarse con ramas, tags y copias existentes, y puede requerir asistencia de GitHub para referencias o vistas almacenadas. No se publican los valores históricos en esta documentación.

## Alcance del prototipo

V1 es experimental. El firmware publicado no incluye validación de UID autorizado, filtrado de MAC de origen en recepción, cifrado ESP-NOW ni timeout explícito de pérdida de tramas. [Revisión técnica](docs/firmware-review.md). REV 2.0 está en desarrollo: [estado de validación](docs/validation.md).

Este documento trata de credenciales y límites de seguridad informática. No acredita seguridad funcional, certificación médica ni validación clínica.

## Reportar un problema

Para errores sin datos sensibles, abrir una incidencia indicando revisión, pasos de reproducción y comportamiento observado. No incluir secretos en incidencias públicas. No hay un canal privado de reporte documentado en este repositorio.
