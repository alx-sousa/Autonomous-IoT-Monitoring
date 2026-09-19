# Arquitectura del sistema

## Flujo funcional

```text
[Transmisor móvil]
        |
     ESP-NOW
        |
   +----+----+
   |         |
   v         v
[Nodo de   [Nodo de
 área]      salida]
   |         |
 RSSI/RFID RSSI/PN532
   |         |
   +----+----+
        |
      Wi-Fi
        |
[Arduino IoT Cloud]
```

La comunicación ESP-NOW se utiliza para el intercambio local entre el transmisor y los nodos receptores. El monitoreo mediante Arduino IoT Cloud funciona como una capa secundaria de telemetría.
