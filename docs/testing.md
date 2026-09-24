# Experimental evaluation and results

Source: final residency report by Luis Alejandro Pérez Sousa, chapter 4. The figures below were reported during the residency; this repository update is not a new experimental campaign.

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

- §3.7, pp. 61–62: controlled transmitter movement between approximately 3 and 20 m, including departure/approach paths and obstacles.
- §3.7.2, p. 62: EMA tuning from α = 0.10 to 0.20 due to observed delay.
- §4.4, p. 77: approximate association of −84 dBm with 6 m in the test environment. This is not a universal RSSI-to-distance conversion.
- Tables 25–26, pp. 72–73: battery/external-supply operation; transition without reset was reported, but oscillograms and a detailed switchover procedure are not published.
- §4.4, p. 77: local alarm operation during simulated Wi-Fi loss.
- §4.3, pp. 74–76: RSSI and alarm-state visualization in Arduino IoT Cloud.

The report describes evaluation in a simulated operational environment and tests related to the hospital setting. It does not provide a clinical protocol or enough detail to attribute every measurement to one fixed location/configuration. Page 78 mentions a 1200 mAh LiPo, which is insufficient to reconstruct power consumption per node and load profile.

## Critical reading of results

The discussion refers to eliminating false positives, while table 24 records one false alarm. The repository keeps the quantitative result and describes a reduction in false activations rather than claiming complete elimination. Raw RSSI samples, individual timing records, repeated runtime trials and confidence intervals are not available here.

RFID authentication, receiver-side MAC filtering and additional states described in the report are not fully implemented in the published sketches. See the [technical firmware review](firmware-review.md). Historical results therefore do not automatically validate every claim about the current source code.

## Protocol for a repeatable campaign

The following is a proposed protocol, not evidence of tests already executed:

1. Record board, hardware revision, library versions, power source and exact firmware commit.
2. Record geometry, distance, obstacles, orientation and access-point/channel conditions.
3. Log timestamp, raw/filtered RSSI, new-frame indication, logical state and physical outputs.
4. Repeat departure, return, exit approach and RFID reset scenarios.
5. Test transmitter loss, Wi-Fi loss, different cards and startup without incoming frames.
6. Verify physical alarm shutdown on every transition and measure runtime per node.
7. Publish trial count, individual timing values and the criterion used to classify false alarms.

The [telemetry figures](evidence.md) illustrate the interface but do not replace an experimental dataset.

## Revision scope

All metrics above belong to V1. REV 2.0 status and pending tests are tracked in [validation.md](validation.md).
