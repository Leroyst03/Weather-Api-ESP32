#ifndef CONFIG_H
#define CONFIG_H

// --- DHT ---
#define DHT_PIN 4
#define DHT_TYPE DHT11 

// --- OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

// --- WiFi ---
#define WIFI_SSID ""
#define WIFI_PASSWORD "" 

#define API_URL "" // URL de la API REST para enviar los datos del DHT11
#endif
