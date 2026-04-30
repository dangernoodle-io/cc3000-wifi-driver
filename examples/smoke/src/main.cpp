#include <Arduino.h>
#include <Adafruit_CC3000.h>

// Adafruit CC3000 breakout default pins.
#define CC3000_IRQ   3
#define CC3000_VBAT  5
#define CC3000_CS    10

Adafruit_CC3000 cc3000 = Adafruit_CC3000(
    CC3000_CS, CC3000_IRQ, CC3000_VBAT,
    SPI_CLOCK_DIVIDER);

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println(F("cc3000-driver smoke"));
    if (!cc3000.begin()) {
        Serial.println(F("begin failed"));
        while (1) {}
    }
    Serial.println(F("begin ok"));
}

void loop() {}
