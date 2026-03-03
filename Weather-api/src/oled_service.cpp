#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "oled_service.h"

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void oled_init() {
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("OLED lista...");
    display.display();
    delay(800);
}

void oled_show_status(const char* wifiStatus, int httpCode) {
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println("Estado del sistema");
    display.println("------------------");

    display.print("WiFi: ");
    display.println(wifiStatus);

    display.print("HTTP: ");
    if (httpCode > 0) display.println(httpCode);
    else display.println("ERR");

    display.display();
}

void oled_show_data(const DhtData& data) {
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println("Estacion Meteo");
    display.println("----------------");

    if (data.valid) {
        display.printf("Temp: %.1f C\n", data.temperature);
        display.printf("Hum:  %.1f %%\n", data.humidity);
    } else {
        display.println("Sensor ERROR");
    }

    display.display();
}
