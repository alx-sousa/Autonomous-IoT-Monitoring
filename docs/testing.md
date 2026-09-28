# Experimental evaluation and results

Source: final V1 technical report by Luis Alejandro Pérez Sousa, chapter 4. The figures below correspond to the original V1 evaluation; this repository update is not a new experimental campaign.

## Published metrics

| Metric | Result | Source |
|---|---:|---|
| Mean detection time | 2 s | Table 24, p. 72 |
| Mean alarm activation time | 2.2 s | Table 24, p. 72 |
| Maximum distance with stable RSSI | 11–17 m | Table 24, p. 72 |
| False alarms | 1 in 20 trials | Table 24, p. 72 |
| Battery runtime | 4.9 h | Table 24, p. 72 |

The table does not separate timing/runtime by node or define the temporal relationship between detection and alarm activation. The two averages should not simply be added. One false alarm in twenty trials is also not equivalent to a global 95% accuracy claim because the event definition and classification matrix are not available.

## Described method

- Controlled transmitter movement was evaluated across multiple distances and with departure/approach paths and obstacles.
- Signal filtering was tuned experimentally to balance stability and response.
- Battery/external-supply operation and transition behavior were evaluated.
- Local alarm operation was tested during simulated Wi-Fi loss.
- RSSI and alarm-state visualization were observed through Arduino IoT Cloud.

The report describes evaluation in a simulated operational environment and tests related to the hospital setting. It does not provide a clinical protocol or enough detail to attribute every measurement to one fixed location/configuration.

## Critical reading of results

The discussion refers to eliminating false positives, while table 24 records one false alarm. The repository therefore keeps the quantitative result and describes a reduction in false activations rather than claiming complete elimination. Raw RSSI samples, individual timing records, repeated runtime trials and confidence intervals are not available here.

## Protocol for a future repeatable campaign

The following is a proposed protocol, not evidence of tests already executed:

1. Record hardware revision, software revision and power source.
2. Record geometry, distance, obstacles, orientation and radio conditions.
3. Log timestamp, signal state, logical state and physical outputs.
4. Repeat departure, return, exit-approach and RFID scenarios.
5. Test transmitter loss and Wi-Fi loss independently.
6. Verify physical alarm behavior on every transition and measure runtime per node.
7. Publish trial count, individual timing values and false-alarm classification criteria.

All metrics above belong to V1. REV 2.0 status and pending tests are tracked in [validation.md](validation.md).
