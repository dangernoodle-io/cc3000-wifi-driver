# cc3000-wifi-driver

Arduino library for the TI CC3000 WiFi chip. Vendored from Adafruit_CC3000_Library; trimmed and ported to Arduino UNO R4 Minima.

## When to use this

Use this library if:
- You have CC3000 hardware (Adafruit breakout, etc.) and want to use it on UNO R4 Minima.
- You want the smartconfig / patch-programming code paths excluded from your build by default.

Use the original [Adafruit_CC3000_Library](https://github.com/adafruit/Adafruit_CC3000_Library) if:
- You have a working sketch on it. There is no functional reason to switch.

## Supported boards

| FQBN family               | Board          | Validated     |
|---------------------------|----------------|---------------|
| `arduino:avr:uno`         | UNO R3         | yes — hardware test passed |
| `arduino:renesas_uno:minima` | UNO R4 Minima | compile-only — no hardware yet |

3.3V signaling required. The Adafruit breakout has level shifters for 5V boards; bare CC3000 modules need external level shifters with the UNO R3.

## Quick start

```cpp
#include <CC3000.h>

#define CC3000_IRQ   3
#define CC3000_VBAT  5
#define CC3000_CS    10

CC3000 cc3000(CC3000_CS, CC3000_IRQ, CC3000_VBAT, SPI_CLOCK_DIVIDER);

void setup() {
    Serial.begin(115200);
    cc3000.begin();
    cc3000.connectToAP("ssid", "password", WLAN_SEC_WPA2);
    while (!cc3000.checkDHCP()) delay(250);
}
```

See `examples/smoke/` for a working build with WiFi associate + DHCP.

## Non-blocking patterns

The CC3000's host driver enforces synchronous behavior on chip-level operations — there is no `EINPROGRESS` / `EWOULDBLOCK` path in the firmware. Use this table to plan sketch structure:

| Operation | Blocking? | Notes |
|-----------|-----------|-------|
| `cc3000.begin()` | yes | one-time, ~1s |
| `cc3000.connectToAP()` | yes | one-time, ~5–10s |
| `cc3000.checkDHCP()` | non-blocking poll | call in a `while` until true |
| `cc3000.getHostByName()` | yes | seconds; resolve once and cache |
| `client.connect(ip, port)` | yes | TCP handshake, ~1s |
| `client.available()` / `client.read()` | non-blocking | safe to call every loop |
| `client.write()` | mostly non-blocking | chip buffers outgoing data |
| `server.available()` | non-blocking | poll every loop |

**Recommended structure:** do all blocking setup (associate, DHCP, DNS, initial connect) in `setup()`. Drive any other work and read I/O in `loop()` via the polling APIs.

See `examples/poll_demo/` for a sketch that does periodic HTTP GETs while keeping the loop responsive.

## Configuration

Compile-time knobs in `src/cc3000_config.h`. Override via `build_flags` in `platformio.ini` or `-D` flags.

| Macro                      | Default | Effect                              |
|----------------------------|--------:|-------------------------------------|
| `CC3K_DEBUG`               | 0       | Verbose driver logging to Serial    |
| `CC3K_SMARTCONFIG`         | 0       | Compile in smartconfig provisioning (~440 B flash) |
| `CC3K_PATCH_PROGRAMMING`   | 0       | Compile in CC3000 firmware patching |
| `CC3K_SCAN`                | 1       | Compile in WiFi scan API            |

## Memory footprint

Validated on UNO R3 + Adafruit CC3000 breakout, smoke example:

|        | RAM   | Flash    |
|--------|------:|---------:|
| AVR    | 664 B | 10,648 B |
| R4     | 3,560 B | 46,440 B |

## Local development

PlatformIO required. On Apple Silicon, the `atmelavr` and `renesas-ra` toolchains are x86_64; symlink native arm64 versions via `examples/smoke/platformio_local.ini` (see `.example`).

```sh
make smoke-uno          # AVR build
make smoke-r4-minima    # Cortex-M build
make check              # cppcheck
```

## License

BSD 2-Clause. Vendored portions copyright Adafruit Industries (Limor Fried, Kevin Townsend) and Tony DiCola; per-file headers preserved.
