#include <Arduino.h>
#include <CC3000.h>
#include "secrets.h"

#define CC3000_IRQ   3
#define CC3000_VBAT  5
#define CC3000_CS    10

CC3000 cc3000(CC3000_CS, CC3000_IRQ, CC3000_VBAT, SPI_CLOCK_DIVIDER);

static uint32_t hostIP = 0;
static unsigned long lastFetch = 0;
static unsigned long lastTick = 0;

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println(F("\n--- cc3000-wifi-driver poll_demo ---"));

    if (!cc3000.begin()) {
        Serial.println(F("FAIL: begin"));
        while (1) {}
    }
    if (!cc3000.connectToAP(WIFI_SSID, WIFI_PASSWORD, WIFI_SECURITY)) {
        Serial.println(F("FAIL: connectToAP"));
        while (1) {}
    }
    while (!cc3000.checkDHCP()) {
        delay(250);
    }

    cc3000.getHostByName("httpbin.org", &hostIP);
    if (hostIP == 0) {
        Serial.println(F("FAIL: getHostByName"));
        while (1) {}
    }
    Serial.println(F("ready"));
}

static void doGet() {
    CC3000_Client client;
    if (!client.connect(IPAddress(hostIP), 80)) {
        Serial.println(F("connect fail"));
        return;
    }
    client.fastrprintln(F("GET /ip HTTP/1.1"));
    client.fastrprintln(F("Host: httpbin.org"));
    client.fastrprintln(F("Connection: close"));
    client.fastrprintln(F(""));
    unsigned long timeout = millis() + 5000;
    while (client.connected() && millis() < timeout) {
        if (client.available()) {
            int c = client.read();
            if (c >= 0) Serial.write((uint8_t)c);
        }
    }
    client.close();
    Serial.println();
}

void loop() {
    unsigned long now = millis();
    // Non-network heartbeat to prove the loop stays responsive between fetches.
    if (now - lastTick >= 1000) {
        lastTick = now;
        Serial.print(F("tick "));
        Serial.println(now / 1000);
    }
    // Periodic fetch every 30s.
    if (now - lastFetch >= 30000) {
        lastFetch = now;
        Serial.println(F("--- GET ---"));
        doGet();
    }
}
