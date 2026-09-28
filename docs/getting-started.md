# Reviewing the firmware architecture

The public portfolio no longer distributes buildable V1 source code. This section is therefore a review guide for the firmware architecture rather than a compilation tutorial.

## Recommended review path

1. Start with the [system architecture](architecture.md).
2. Review the [communication architecture](communication.md).
3. Open the node-level block logic:
   - [Wearable transmitter](../firmware/transmitter/README.md)
   - [Area receiver](../firmware/area_node/README.md)
   - [Exit receiver](../firmware/exit_node/README.md)
4. Review the [experimental results](testing.md) and [validation status](validation.md).
5. Review [REV 2.0 hardware](hardware-rev2.md) for the current PCB/mechanical redesign.

## Public/private boundary

The repository exposes enough information to review responsibility split, communication flow, state-machine intent and hardware/software integration. Exact firmware implementation details are maintained privately and are not required to understand the project at portfolio level.
