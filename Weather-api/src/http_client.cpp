#include <HTTPClient.h>
#include <WiFi.h>
#include "http_client.h"
#include "config.h"

int http_send(const DhtData& data) {
    if (!data.valid || WiFi.status() != WL_CONNECTED) return -1;

    HTTPClient http;
    http.setReuse(false);  // evitar problemas de conexión en el ESP32
    http.begin(API_URL);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"temperature\":";
    json += data.temperature;
    json += ",\"humidity\":";
    json += data.humidity;
    json += "}";

    int code = http.POST(json);

    http.end();  // cerrar conexión correctamente
    delay(800);  // evitar colisiones TCP

    return code;
}
