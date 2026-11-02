#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

const char* SSID = "ESP32_AP";
const char* PSK = "Whatevercode123";
const char* server_listen_ip = "192.168.4.2"; // my server 
const uint16_t serverPort = 8090;
// ESP32 anvender per standard 192.168.4.XXX subnet
WiFiClient client;


//socket 
void setup() {
Serial.begin(9600);

// laver et WiFI netvaerk samt DHCP server for os at koere vores datasamling paa.

WiFi.setHostname("ESP32-stol");


if (!WiFi.softAP(SSID, PSK)) {

// koeres kun hvis noget gaar galt.
log_e("Kunne ikke anvendes som AP");

} 

delay(10000);
}





void loop() {
  if (client.connect(server_listen_ip, serverPort)) {
Serial.println("connected to socket\n");
client.println("my msg is how long?");

client.stop();

} else {
  Serial.println("not working\n");
}

}