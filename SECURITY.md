# Security and configuration

## Local credentials

The V1 receivers load credentials from `secrets.h`, created from `secrets.example.h` and excluded from Git. Do not publish Wi-Fi passwords, cloud keys, patient data or internal infrastructure information in source code, screenshots, PDFs or public issues.

## Historical exposure

Earlier revisions contained embedded Wi-Fi and Arduino IoT Cloud credentials. They were removed from the current files, but references may remain reachable in historical commits or GitHub-side cached references. Repository cleanup does **not** revoke those credentials.

Any affected Wi-Fi passwords and Arduino IoT Cloud keys should be rotated or revoked independently of Git history cleanup. Rotation has not been verified by this repository.

A complete purge of already published secrets can require history rewriting, cleanup of branches/tags/PR references and, in some cases, GitHub support for cached views or unreachable objects. Historical secret values are intentionally not reproduced in this documentation.

## Prototype security scope

V1 is experimental. The published firmware does not implement an authorized RFID UID list, receiver-side source-MAC filtering, ESP-NOW encryption or an explicit packet-loss timeout. See the [firmware review](docs/firmware-review.md).

REV 2.0 remains under development; see the [validation status](docs/validation.md).

This document covers credential handling and cybersecurity limitations only. It does not establish functional safety, medical certification or clinical validation.

## Reporting an issue

For non-sensitive defects, open a public issue and include the affected revision, reproduction steps and observed behavior. Do not include secrets or sensitive infrastructure data. No private security-reporting channel is currently documented in this repository.
