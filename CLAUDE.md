# cc3000-driver

CC3000 WiFi driver for modern Arduino boards. Vendored from Adafruit_CC3000_Library; clean rewrite in progress.

## Targets

| FQBN family | Board | Status |
|-------------|-------|--------|
| `arduino:avr:uno` | UNO R3 | tier 1 |
| `arduino:renesas_uno:minima` | UNO R4 Minima | tier 1 |

## Local development

### Apple Silicon

PlatformIO's `atmelavr` and `renesas-ra` toolchains are x86_64 only. Install Rosetta 2 once:

    softwareupdate --install-rosetta --agree-to-license

Without it, `make smoke-*` fails with `bad CPU type in executable`.

### Build

    make smoke-uno              # AVR build
    make smoke-uno_r4_minima    # Cortex-M build (currently fails — phase 1 work)
    make smoke                  # both
    make check                  # cppcheck

CI runs on `ubuntu-latest` with native x86_64 toolchains; no Rosetta involved.

## Repo conventions

See workspace `claude-code/rules/arduino.md` and `claude-code/rules/embedded.md`.
