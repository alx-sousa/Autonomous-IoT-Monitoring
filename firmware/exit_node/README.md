# Exit receiver — firmware logic

**Platform:** ESP32-C6 (V1)

The exit receiver independently evaluates the wearable as it approaches the monitored exit and activates its own local alarm workflow.

```mermaid
flowchart TD
    A[Receive wearable frame] --> B[Extract signal quality / RSSI]
    B --> C[Apply signal conditioning]
    C --> D[Evaluate approach condition]
    D -->|No alert condition| E[Continue monitoring]
    D -->|Approach confirmed| F[Latch local visual / audible alert]
    F --> G[RFID interaction]
    G --> H[Reset / re-arm local monitoring]
    E --> I[Update telemetry]
    H --> I
    I --> A
```

## Responsibility

- Receive the wearable signal independently from the area receiver.
- Evaluate approach to the exit using local RSSI/state logic.
- Activate the exit node's own visual and audible alert.
- Handle RFID interaction and local re-arm behavior.
- Publish operational telemetry to Arduino IoT Cloud.

Exact thresholds, filter coefficients, GPIO assignments, timers and source code are intentionally not published.
