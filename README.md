This repository adds M17 support back to [G4KLX's MMDVM-Host](https://github.com/g4klx/MMDVM-Host), which removed it in July 2025:

## Branches

- **`master`** follows G4KLX's current `master` (the MQTT/JSON version), with M17 restored on top.
- **`v1.0`** is G4KLX's `v1.0` release, the last version before MQTT and the one WPSD and Pi-Star use, with M17 restored on top.
- **`archived-master`** is this repository's previous `master`: G4KLX's code from July 2025 with M17 restored. It is kept for reference and no longer updated.

**If you cloned this repository before October 2026:** `master` was replaced with a new history, not updated, so `git pull` on an old clone will fail or try to merge unrelated work. To switch to the new `master` and keep your old one as `archived-master`, run:

    git fetch origin
    git branch -m master archived-master
    git checkout -b master origin/master

If you have no local changes to keep, `git checkout master && git reset --hard origin/master` does the same in one step and discards your local `master`.

## Original README from upstream

These are the source files for building the MMDVM Host, the program that
interfaces to the MMDVM or DVMega on the one side, and a suitable network (via a
gateway) on the other. It supports D-Star, DMR, P25 Phase 1, NXDN, System Fusion,
M17, POCSAG, and FM on the MMDVM, and D-Star, DMR, and System Fusion on the DVMega.

On the D-Star side the MMDVM Host interfaces with the D-Star Gateway, on DMR it
connects to the DMR Gateway to allow for connection to multiple DMR networks.
On System Fusion it connects to the DG-Id or YSF Gateway to allow
access to the FCS and YSF networks. On P25 it connects to the P25 Gateway. On
NXDN it connects to the NXDN Gateway which provides access to the NXDN and
NXCore talk groups. On M17 it uses the M17 Gateway to access the M17 reflector
system. It uses the DAPNET Gateway to access DAPNET to receive
paging messages for transmission using POCSAG.

It builds on 32-bit and 64-bit Linux as well as on Windows using Visual Studio
2022 on x86 and x64.

This software is licenced under the GPL v2 and is primarily intended for amateur and
educational use.
