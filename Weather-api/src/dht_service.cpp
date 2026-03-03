#include <Arduino.h>
#include <DHT.h>
#include "config.h"
#include "dht_service.h"

static DHT dht(DHT_PIN, DHT_TYPE);

void dht_init() {
    dht.begin();
}

DhtData dht_read() {
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
        return {0, 0, false};
    }

    return {t, h, true};
}
