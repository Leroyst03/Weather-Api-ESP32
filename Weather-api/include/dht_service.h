#ifndef DHT_SERVICE_H
#define DHT_SERVICE_H

struct DhtData {
    float temperature;
    float humidity;
    bool valid;
};

void dht_init();
DhtData dht_read();

#endif
