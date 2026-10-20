# Security and configuration

## Public source scope

The repository includes **sanitized historical V1 firmware snapshots** for portfolio review. They preserve representative application logic while excluding deployment-specific configuration and unique device identifiers.

Do not publish private network configuration, cloud secrets, patient data, internal infrastructure information or other deployment data that does not need to be public.

## Historical exposure

Earlier revisions of this repository contained firmware source and, in older history, embedded Wi-Fi / Arduino IoT Cloud credentials. Removing files from the current branch does **not** erase them from Git history or cached references.

Any previously exposed credentials should be rotated or revoked independently of repository cleanup. A complete purge can require Git history rewriting, cleanup of branches/tags/PR references and, in some cases, GitHub support for cached or unreachable objects.

Historical secret values are intentionally not reproduced in this documentation.

## Current portfolio boundary

The public source under `firmware/public/v1/` uses neutral placeholder configuration instead of the original deployment values.

The source is provided as engineering evidence, not as a deployment package.

## Reporting an issue

For non-sensitive defects, open a public issue and include the affected revision and observed behavior. Do not include secrets or sensitive infrastructure data.
