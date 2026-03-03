#include <Arduino.h>

#include "dht_service.h"
#include "wifi_service.h"
#include "http_client.h"
#include "oled_service.h"

unsigned long lastSend = 0;
const unsigned long interval = 10000;

void setup() {
    Serial.begin(115200);

    dht_init();
    oled_init();

    bool wifi_ok = wifi_connect();
    oled_show_status(wifi_ok ? "OK" : "ERROR", 0);
}

void loop() {
    DhtData data = dht_read();
    bool wifi_ok = wifi_is_connected();

    int httpCode = -1;

    if (millis() - lastSend > interval) {
        httpCode = http_send(data);
        lastSend = millis();
    }

    oled_show_data(data);
    delay(1500);

    oled_show_status(wifi_ok ? "OK" : "ERROR", httpCode);
    delay(1500);
}
