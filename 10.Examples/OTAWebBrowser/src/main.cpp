#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

const char* update_path = "/firmware";
const char* update_username = "admin";
const char* update_password = "admin";
const char* ssid = "my_ssid";
const char* password = "my_password";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("Booting Sketch 1...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while(WiFi.waitForConnectResult() != WL_CONNECTED){
        WiFi.begin(ssid, password);
        Serial.println("WiFi failed, retrying.");
    }

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    httpUpdater.setup(&httpServer, update_path, update_username, update_password);
    httpServer.begin();

    Serial.printf("HTTPUpdateServer ready! Open http://%s%s in your browser and login with username '%s' and password '%s'\n", WiFi.localIP().toString().c_str(), update_path, update_username, update_password);
}

void loop() {
    httpServer.handleClient();
}
