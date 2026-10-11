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

These are the source files for building the MMDVMHost, the program that
interfaces to the MMDVM or DVMega on the one side, and a suitable network on
the other. It supports D-Star, DMR, P25 Phase 1, NXDN, System Fusion, M17,
POCSAG, and FM on the MMDVM, and D-Star, DMR, and System Fusion on the DVMega.

On the D-Star side the MMDVMHost interfaces with the ircDDB Gateway, on DMR it
connects to the DMR Gateway to allow for connection to multiple DMR networks,
or a single network directly. on System Fusion it connects to the YSF Gateway to allow
access to the FCS and YSF networks. On P25 it connects to the P25 Gateway. On
NXDN it connects to the NXDN Gateway which provides access to the NXDN and
NXCore talk groups. On M17 it uses the M17 Gateway to access the M17 reflector system.
It uses the DAPNET Gateway to access DAPNET to receive
paging messages.

It builds on 32-bit and 64-bit Linux as well as on Windows using Visual Studio
2022 on x86 and x64. It can optionally control various Displays. Currently
these are:

- HD44780 (sizes 2x16, 2x40, 4x16, 4x20)
	- Support for HD44780 via 4 bit GPIO connection (user selectable pins)
	- Adafruit 16x2 LCD+Keypad Kits (I2C)
	- Connection via PCF8574 GPIO Extender (I2C)
- Nextion TFTs (all sizes, both Basic and Enhanced versions)
- OLED 128x64 (SSD1306)
- LCDproc

The Nextion displays can connect to the UART on the Raspberry Pi, or via a USB
to TTL serial converter like the FT-232RL. It may also be connected to the UART
output of the MMDVM modem (Arduino Due, STM32, Teensy).

The HD44780 displays are integrated with wiringPi for Raspberry Pi based
platforms.

The OLED display needs an extra library see OLED.md

The LCDproc support enables the use of a multitude of other LCD screens. See
the [supported devices](http://lcdproc.omnipotent.net/hardware.php3) page on
the LCDproc website for more info.

This software is licenced under the GPL v2 and is primarily intended for amateur and
educational use.
