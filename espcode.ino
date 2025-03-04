#include <WiFi.h>
#include <HTTPClient.h>

#define LED_PIN 23  // Change if using a different GPIO

// Replace with your WiFi credentials
const char* WIFI_SSID = "Noisebridge";
const char* WIFI_PASSWORD = "noisebridge";

// Replace with your API endpoint
const char* SERVER_URL = "http://replace_url.com/";

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(SERVER_URL);

        int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
            String response = http.getString();
            response.trim(); // Remove unwanted spaces/newlines

            Serial.print("Server Response: ");
            Serial.println(response);

            if (response == "ON") {
                digitalWrite(LED_PIN, HIGH);
            } else if (response == "OFF") {
                digitalWrite(LED_PIN, LOW);
            }
        } else {
            Serial.print("Error on HTTP request: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected! Reconnecting...");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }

    delay(5000);  // Check every 5 seconds
}