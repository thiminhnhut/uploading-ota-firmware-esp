#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

const char* ssid = "my_ssid";
const char* password = "my_password";

unsigned int i = 0;

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

    t_httpUpdate_return ret = ESPhttpUpdate.update("http://abc.xyz/firmware.bin");
    // NOT Working
    switch(ret) {
        case HTTP_UPDATE_FAILED:
            Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            break;
        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("HTTP_UPDATE_NO_UPDATES");
            break;
        case HTTP_UPDATE_OK:
            Serial.println("HTTP_UPDATE_OK");
            break;
    }
}

void loop() {
    Serial.println(i++);
    delay(200);
}
