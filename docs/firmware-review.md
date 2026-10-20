# Firmware review — V1

This section connects the published V1 firmware snapshots with an engineering review of the implementation.

The review is **static**: it is based on the source currently published in this repository. The code was not recompiled, flashed or physically revalidated as part of this documentation pass.

## Detailed review

- [V1 firmware technical review](firmware-review/v1-review.md) — system-level strengths, findings, future architecture and test ideas.
- [Wearable transmitter flow](firmware-review/transmitter-flow.md) — channel sweep, peer updates, transmission bursts and timing implications.
- [Area receiver state machine](firmware-review/area-state-machine.md) — EMA filtering, hysteresis, CERCA/LEJOS behavior, critical alarm and RFID walk mode.
- [Exit receiver state machine](firmware-review/exit-state-machine.md) — approach confirmation, latched alarm, PN532 reset and timed re-arm.

## Reviewed public source

- [Wearable transmitter](../firmware/public/v1/transmitter/transmitter.ino)
- [Area receiver](../firmware/public/v1/area_receiver/area_receiver.ino)
- [Exit receiver](../firmware/public/v1/exit_receiver/exit_receiver.ino)

## What this review is for

The goal is to preserve the V1 implementation honestly while showing the ability to evaluate it critically.

The delivered prototype is not retroactively rewritten as if it had been developed with a production firmware architecture. Instead, the review distinguishes:

**what V1 actually implemented → what worked as a prototype → what should be improved in a future revision.**

REV 2.0 hardware development is tracked separately. Firmware porting and physical validation for that hardware remain pending.
