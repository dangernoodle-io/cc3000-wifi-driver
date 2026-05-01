# cc3000-wifi-driver

CC3000 WiFi driver for Arduino UNO R3 + UNO R4 Minima. Forked from Adafruit_CC3000_Library; both targets hardware-validated.

## Targets

| FQBN family | Board | Status |
|-------------|-------|--------|
| `arduino:avr:uno` | UNO R3 | tier 1, hardware-validated |
| `arduino:renesas_uno:minima` | UNO R4 Minima | tier 1, hardware-validated |

## Local development

PlatformIO required. On Apple Silicon, copy `examples/smoke/platformio_local.ini.example` to `platformio_local.ini` (gitignored) and adjust the symlink paths to your local arm64 toolchains. Without this, builds fail with `bad CPU type in executable`.

R4 Minima upload also needs a native arm64 dfu-util wrapper — see KB fact 335.

```sh
make smoke-uno          # AVR build
make smoke-r4-minima    # Cortex-M build
make test               # Unity host tests
make coverage           # gcovr -> Coveralls
make check              # cppcheck
```

CI on ubuntu-latest uses native x86_64 toolchains; no overrides needed.

## Repo conventions

See workspace `claude-code/rules/arduino.md` and `claude-code/rules/embedded.md`.
