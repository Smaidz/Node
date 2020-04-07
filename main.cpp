#include <ESP8266WebServer.h>
#include "controls.h"
const char* ssid = "homewifi";
const char* password = "homewifipassword";
uint8_t LED1 = 12;
bool LED1Status = LOW;
uint8_t LED2 = 13;
bool LED2Status = LOW;
ESP8266WebServer server(255);

void rootPage() {
    server.send(200, "text/html", controlpage);
}

void bothLEDon() {
    digitalWrite(LED1, HIGH);
    LED1Status = HIGH;
    digitalWrite(LED2, HIGH);
    LED2Status = HIGH;
    server.send(200, "text/html", controlpage);
}
void bothLEDonRealtime() {
    digitalWrite(LED1, HIGH);
    LED1Status = HIGH;
    digitalWrite(LED2, HIGH);
    LED2Status = HIGH;
    server.send(200);
}

void bothLEDoff() {
    digitalWrite(LED1, LOW);
    LED1Status = LOW;
    digitalWrite(LED2, LOW);
    LED2Status = LOW;
    server.send(200, "text/html", controlpage);
}

void LED1Toggle() {
    if(LED1Status == HIGH) {
        digitalWrite(LED1, LOW);
        LED1Status = LOW;
    } else {
        digitalWrite(LED1, HIGH);
        LED1Status = HIGH;
    }
    server.send(200, "text/html", controlpage);
}

void LED2Toggle() {
    if(LED2Status == HIGH) {
        digitalWrite(LED2, LOW);
        LED2Status = LOW;
    } else {
        digitalWrite(LED2, HIGH);
        LED2Status = HIGH;
    }
    server.send(200, "text/html", controlpage);
}

void setup() {
    Serial.begin(9600);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    IPAddress ip(192,168,1,254);
    IPAddress gateway(192,168,1,1);
    IPAddress subnet(255,255,255,0);
    WiFi.config(ip, gateway, subnet);
    delay(5000);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Wifi connected");

    server.on("/", rootPage);
    server.on("/bothOn", bothLEDon);
    server.on("/bothOff", bothLEDoff);
    server.on("/l1Toggle", LED1Toggle);
    server.on("/l2Toggle", LED2Toggle);

    server.begin();
    Serial.println("Server started");

    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println(":255");
}

void loop() {
    server.handleClient();
}
