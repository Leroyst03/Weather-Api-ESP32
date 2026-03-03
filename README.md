# ESP32 Weather Station — Firmware

Firmware para ESP32 que lee temperatura y humedad con un sensor DHT11, los muestra en una pantalla OLED y los envia periodicamente a una API REST via WiFi.

---

## Hardware necesario

| Componente        | Descripcion                         |
|-------------------|-------------------------------------|
| ESP32             | Microcontrolador con WiFi integrado |
| DHT11             | Sensor de temperatura y humedad     |
| OLED 128x64       | Display I2C (direccion 0x3C)        |
| Cables/protoboard | Conexiones                          |

### Esquema de pines

| ESP32    | Periferico   |
|----------|--------------|
| GPIO 4   | DHT11 DATA   |
| GPIO 21  | OLED SDA     |
| GPIO 22  | OLED SCL     |
| 3.3V/GND | Alimentacion |

---

## Estructura del firmware

```
.
├── include/
│   ├── config.h               # Pines, credenciales WiFi y URL de la API
│   ├── dht_service.h          # Interfaz lectura DHT11
│   ├── http_client.h          # Interfaz envio HTTP POST
│   ├── oled_service.h         # Interfaz pantalla OLED
│   └── wifi_service.h         # Interfaz conexion WiFi
├── src/
│   ├── main.cpp               # setup() y loop() principal
│   ├── dht_service.cpp        # Inicializacion y lectura del DHT11
│   ├── http_client.cpp        # Envio de datos via HTTP POST
│   ├── oled_service.cpp       # Visualizacion en pantalla OLED
│   └── wifi_service.cpp       # Conexion y comprobacion de estado WiFi
├── lib/                       # Librerias locales (PlatformIO)
└── platformio.ini             # Configuracion de placa y dependencias
```

---

## Configuracion

Antes de compilar, rellena `config.h`:

```cpp
#define WIFI_SSID     "tu_red_wifi"
#define WIFI_PASSWORD "tu_contrasena"
#define API_URL       "http://192.168.x.x:8080/api/sensor"

// Cambiar solo si modificas el cableado
#define DHT_PIN  4
#define DHT_TYPE DHT11
```

---

## Dependencias

Instala desde el **Library Manager** de Arduino IDE:

| Libreria                | Proposito           |
|-------------------------|---------------------|
| DHT sensor library      | Lectura del DHT11   |
| Adafruit Unified Sensor | Dependencia del DHT |
| Adafruit SSD1306        | Driver OLED         |
| Adafruit GFX Library    | Graficos OLED       |

---

## Funcionamiento

### Arranque (setup)

1. Inicializa el puerto serie a 115200 baud.
2. Inicia el sensor DHT11.
3. Inicia la pantalla OLED.
4. Conecta al WiFi y muestra el resultado en la OLED (OK / ERROR).

### Bucle principal (loop)

Cada ciclo de ~3 segundos el ESP32:

1. Lee temperatura y humedad del DHT11.
2. Comprueba si el WiFi sigue conectado.
3. Cada **10 segundos**, si la lectura es valida, envia un POST JSON a la API:

```json
{ "temperature": 24.5, "humidity": 61.0 }
```

4. Alterna la pantalla OLED entre dos vistas (1.5 s cada una):
   - **Datos**: temperatura y humedad actuales.
   - **Estado**: WiFi OK/ERROR y codigo HTTP de la ultima peticion.

### Protecciones

- Si el DHT11 devuelve `NaN`, el envio HTTP se cancela para evitar datos corruptos.
- `http.setReuse(false)` y un `delay(800 ms)` tras cada POST evitan colisiones TCP en el ESP32.
- El cliente HTTP cierra la conexion explicitamente con `http.end()` tras cada envio.

---

## Compilar y flashear

1. Abre el proyecto en **PlatformIO** (VS Code).
2. Rellena `config.h` con tus credenciales y la URL de la API.
3. Conecta el ESP32 por USB y ejecuta `Upload` (o `pio run -t upload`).
4. Abre el **Monitor Serie** a 115200 baud para ver el log de arranque.

---

