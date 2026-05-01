#include <Arduino.h>
#include <CC3000.h>
#include <CC3000_Server.h>
#include "secrets.h"

#define CC3000_IRQ   3
#define CC3000_VBAT  5
#define CC3000_CS    10

CC3000 cc3000 = CC3000(
    CC3000_CS, CC3000_IRQ, CC3000_VBAT,
    SPI_CLOCK_DIVIDER);

CC3000_Server server(7);

static void printIPdotted(uint32_t ip) {
    Serial.print((uint8_t)(ip >> 24)); Serial.print('.');
    Serial.print((uint8_t)(ip >> 16)); Serial.print('.');
    Serial.print((uint8_t)(ip >>  8)); Serial.print('.');
    Serial.print((uint8_t)(ip      ));
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println(F("\n--- cc3000-wifi-driver tcp_echo ---"));

    if (!cc3000.begin()) {
        Serial.println(F("FAIL: begin"));
        while (1) {}
    }
    Serial.println(F("OK: begin"));

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
    }

    server.begin();
    Serial.print(F("listening on ")); printIPdotted(ip); Serial.println(F(":7"));
}

void loop() {
    CC3000_ClientRef client = server.available();
    if (client) {
        Serial.println(F("client connected"));
        while (client.connected()) {
            if (client.available()) {
                int c = client.read();
                if (c >= 0) {
                    Serial.print(F("rx: "));
                    Serial.write((uint8_t)c);
                    Serial.println();
                    client.write((uint8_t)c);
                }
            }
            delay(10);
        }
        Serial.println(F("client disconnected"));
    }
    delay(10);
}
