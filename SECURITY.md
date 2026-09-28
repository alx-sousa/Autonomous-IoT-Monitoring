# Security and configuration

## Public source scope

The public repository documents firmware architecture and block logic, but does not distribute the complete V1 firmware implementation. Do not publish Wi-Fi passwords, cloud keys, patient data, device credentials or internal infrastructure information in source files, screenshots, PDFs or public issues.

## Historical exposure

Earlier revisions of this repository contained firmware source and, in older history, embedded Wi-Fi / Arduino IoT Cloud credentials. Removing files from the current branch does **not** erase them from Git history or cached references.

Any previously exposed credentials should be rotated or revoked independently of repository cleanup. A complete purge can require Git history rewriting, cleanup of branches/tags/PR references and, in some cases, GitHub support for cached or unreachable objects.

Historical secret values are intentionally not reproduced in this documentation.

## Current portfolio boundary

The public version omits buildable firmware, exact device identifiers, GPIO maps, control thresholds and timing constants. Architectural behavior and validation results remain documented for technical review.

## Reporting an issue

For non-sensitive defects, open a public issue and include the affected revision and observed behavior. Do not include secrets or sensitive infrastructure data.
