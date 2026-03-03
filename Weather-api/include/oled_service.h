#ifndef OLED_SERVICE_H
#define OLED_SERVICE_H

#include "dht_service.h"

void oled_init();
void oled_show_status(const char* wifiStatus, int httpCode);
void oled_show_data(const DhtData& data);

#endif
