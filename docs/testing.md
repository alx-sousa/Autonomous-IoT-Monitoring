# Evaluación experimental y resultados

Fuente: informe final de residencia de Luis Alejandro Pérez Sousa, capítulo 4. Los resultados siguientes fueron reportados por el autor durante la residencia; esta actualización del repositorio no constituye una nueva campaña experimental.

## Métricas publicadas

| Métrica | Resultado | Fuente |
|---|---:|---|
| Tiempo promedio de detección | 2 s | Tabla 24, p. 72 |
| Tiempo promedio de activación de alarmas | 2.2 s | Tabla 24, p. 72 |
| Distancia máxima con RSSI estable | 11–17 m | Tabla 24, p. 72 |
| Falsas alarmas | 1 en 20 pruebas | Tabla 24, p. 72 |
| Autonomía con batería | 4.9 h | Tabla 24, p. 72 |

La tabla no desglosa tiempos y autonomía por nodo ni especifica la relación temporal entre detección y activación. No se suman ambos promedios. Una falsa alarma en veinte ensayos no equivale a una exactitud global del 95 %: faltan la definición completa de eventos y una matriz de clasificación.

## Método descrito

- §3.7, pp. 61–62: desplazamientos controlados del transmisor entre aproximadamente 3 y 20 m, con trayectorias de alejamiento y aproximación y consideración de obstáculos.
- §3.7.2, p. 62: ajuste del EMA desde α = 0.10 a 0.20 por el retardo observado.
- §4.4, p. 77: asociación aproximada de −84 dBm con 6 m en el entorno de prueba. No es una conversión universal de RSSI a distancia.
- Tablas 25–26, pp. 72–73: funcionamiento con batería y fuente externa; transición sin reinicio reportada, sin oscilogramas ni procedimiento detallado de conmutación publicados.
- §4.4, p. 77: alarmas locales durante simulaciones de caída de Wi-Fi.
- §4.3, pp. 74–76: visualización de RSSI y estado de alarma en Arduino IoT Cloud.

El informe menciona evaluación en entorno operativo simulado y pruebas relacionadas con el entorno hospitalario. No aporta un protocolo clínico ni permite atribuir todas las mediciones a una ubicación y configuración únicas. La página 78 menciona una LiPo de 1200 mAh; no basta para reconstruir consumo por nodo y perfil de carga.

## Lectura crítica de resultados

La discusión habla de eliminación de falsos positivos, pero la tabla 24 registra uno. Se conserva el dato cuantitativo y se describe reducción de falsas activaciones, sin afirmar eliminación total. No se dispone aquí de muestras RSSI crudas, tiempos individuales, repeticiones de autonomía ni intervalos de confianza.

Los objetivos de autenticación RFID, filtrado MAC y estados adicionales descritos en el informe no están íntegramente implementados en los sketches publicados. Véase [revisión técnica](firmware-review.md). Los resultados históricos no validan automáticamente cada afirmación sobre el código actual.

## Guía para una repetición verificable

Esta lista es un protocolo propuesto, no pruebas ya ejecutadas:

1. Registrar placa, revisión de hardware, bibliotecas, alimentación y firmware exactos.
2. Anotar geometría, distancias, obstáculos, orientación y canal del punto de acceso.
3. Registrar timestamp, RSSI crudo/filtrado, trama nueva, estado lógico y salidas físicas.
4. Repetir alejamiento, retorno, aproximación a salida y restablecimiento RFID.
5. Probar ausencia del transmisor, pérdida Wi-Fi, tarjetas distintas y arranque sin tramas.
6. Verificar apagado físico de alarmas en todas las transiciones y medir autonomía por nodo.
7. Publicar número de ensayos, tiempos individuales y criterio para clasificar falsas alarmas.

Las [figuras de telemetría](evidence.md) ilustran la interfaz; no sustituyen un dataset experimental.

## Alcance por revisión

Todas las métricas anteriores pertenecen a V1. El estado de REV 2.0 y sus pruebas pendientes se mantienen en [validation.md](validation.md).
