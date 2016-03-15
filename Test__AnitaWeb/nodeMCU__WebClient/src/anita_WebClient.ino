/**
 * Basic Web_Client for NodeMCU
 *
 *  - Anita de Prado -
 *
 *     Lee el servidor local de la otra plaquita servidor: http://172.16.34.155
 *     En concreto saca información de la dirección: http://172.16.34.155/paracliente
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

// Wifi
const char* ssid = "BQ_CORP";
const char* password = "%&Th3_M4Tr1X1234!=";

const char* webDir = "http://172.16.34.155/paracliente"; //Dirección creada sólo para cliente y no tener que utilizar métodos GET

ESP8266WiFiMulti WiFiMulti;

void setup() {

    USE_SERIAL.begin(9600);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP(ssid, password);

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS

        http.begin(webDir); //Dirección creada sólo para cliente y no tener que utilizar métodos GET

        USE_SERIAL.print("[HTTP] GET...\n");

        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();  //Leo el código HTML directamente.
                USE_SERIAL.print("Leo esto en la web: ");
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(10000);
}
