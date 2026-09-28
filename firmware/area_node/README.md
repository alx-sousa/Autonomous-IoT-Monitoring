# Area receiver — firmware logic

**Platform:** ESP32-C6 (V1)

The area receiver evaluates whether the wearable remains inside the monitored zone and performs the corresponding local alert actions.

```mermaid
flowchart TD
    A[Receive wearable frame] --> B[Extract signal quality / RSSI]
    B --> C[Apply signal conditioning]
    C --> D[Evaluate proximity state]
    D -->|Normal condition| E[Maintain local monitoring]
    D -->|Departure condition confirmed| F[Activate local visual / audible alert]
    F --> G[RFID interaction / authorized workflow]
    E --> H[Update telemetry]
    G --> H
    H --> A
```

## Responsibility

- Receive the wearable signal independently from the exit receiver.
- Condition the RSSI input to reduce short-term fluctuations.
- Evaluate the local area state with hysteresis/state logic.
- Drive OLED/indicator/buzzer behavior locally.
- Process RFID interaction for the area workflow.
- Publish operational telemetry to Arduino IoT Cloud.

Exact thresholds, filter coefficients, GPIO assignments, timers and source code are intentionally not published.
