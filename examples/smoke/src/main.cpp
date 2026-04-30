#include <Arduino.h>
#include <CC3000.h>
#include "secrets.h"

#define CC3000_IRQ   3
#define CC3000_VBAT  5
#define CC3000_CS    10

CC3000 cc3000 = CC3000(
    CC3000_CS, CC3000_IRQ, CC3000_VBAT,
    SPI_CLOCK_DIVIDER);

static void printIPdotted(uint32_t ip) {
    Serial.print((uint8_t)(ip >> 24)); Serial.print('.');
    Serial.print((uint8_t)(ip >> 16)); Serial.print('.');
    Serial.print((uint8_t)(ip >>  8)); Serial.print('.');
    Serial.print((uint8_t)(ip      ));
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println(F("\n--- cc3000-driver smoke ---"));

    if (!cc3000.begin()) {
        Serial.println(F("FAIL: begin"));
        while (1) {}
    }
    Serial.println(F("OK: begin"));

    uint8_t major, minor;
    if (cc3000.getFirmwareVersion(&major, &minor)) {
        Serial.print(F("firmware: "));
        Serial.print(major); Serial.print('.'); Serial.println(minor);
    }

    uint8_t mac[6];
    if (cc3000.getMacAddress(mac)) {
        Serial.print(F("mac: "));
        for (uint8_t i = 0; i < 6; i++) {
            if (mac[i] < 0x10) Serial.print('0');
            Serial.print(mac[i], HEX);
            if (i < 5) Serial.print(':');
        }
        Serial.println();
    }

    Serial.print(F("connecting to ")); Serial.println(F(WIFI_SSID));
    if (!cc3000.connectToAP(WIFI_SSID, WIFI_PASSWORD, WIFI_SECURITY)) {
        Serial.println(F("FAIL: connectToAP"));
        while (1) {}
    }
    Serial.println(F("OK: associated"));

    Serial.print(F("DHCP"));
    while (!cc3000.checkDHCP()) { Serial.print('.'); delay(250); }
    Serial.println();

    uint32_t ip, nm, gw, dhcp, dns;
    if (cc3000.getIPAddress(&ip, &nm, &gw, &dhcp, &dns)) {
        Serial.print(F("ip: ")); printIPdotted(ip); Serial.println();
        Serial.print(F("gw: ")); printIPdotted(gw); Serial.println();
        Serial.print(F("dns: ")); printIPdotted(dns); Serial.println();
    }
    Serial.println(F("--- done ---"));
}

void loop() {}
