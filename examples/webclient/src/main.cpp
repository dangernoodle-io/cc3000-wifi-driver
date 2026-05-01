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
    Serial.println(F("\n--- cc3000-wifi-driver webclient ---"));

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

    // Resolve httpbin.org hostname to IP
    uint32_t hostIP = 0;
    uint16_t dnsStatus = cc3000.getHostByName("httpbin.org", &hostIP);
    if (dnsStatus != 0) {
        Serial.println(F("FAIL: getHostByName"));
        while (1) {}
    }
    Serial.print(F("httpbin.org: ")); printIPdotted(hostIP); Serial.println();

    // Create client and connect to httpbin.org:80
    CC3000_Client client;
    if (!client.connect(IPAddress(hostIP), 80)) {
        Serial.println(F("FAIL: client.connect"));
        while (1) {}
    }
    Serial.println(F("OK: connected"));

    // Send HTTP GET request
    client.fastrprintln(F("GET /ip HTTP/1.1"));
    client.fastrprintln(F("Host: httpbin.org"));
    client.fastrprintln(F("Connection: close"));
    client.fastrprintln(F(""));

    // Read and print response
    Serial.println(F("--- response ---"));
    unsigned long timeout = millis() + 10000; // 10 second timeout
    while (client.connected() && millis() < timeout) {
        if (client.available()) {
            int c = client.read();
            if (c >= 0) Serial.write((uint8_t)c);
        }
        delay(10);
    }
    client.close();
    Serial.println(F("--- done ---"));
}

void loop() {}
