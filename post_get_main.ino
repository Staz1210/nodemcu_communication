/**
 * AizD
 * (IoT-2) - Kirim dan Terima data terhadap Internet
 * Komunikasi NodeMCU-Internet
 *
 * Satrio Adi, Teknik Komputer
 * Jum'at, 14 Desember 2018
 * Politeknik Elektronika Negeri Surabaya 
 * 
 **/
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(D3, D2);
char char_received; //char hasil pembacaan bluetooth
String string_received; //String hasil pembacaan bluetooth
 
const char* ssid = "AMiN"; //SSID HOTSPOT
const char* password = "robotics"; //PASSWORD HOTSPOT

char JsonMessageToSend[300];
 
void setup () {
 
  Serial.begin(38400);
  BTSerial.begin(38400);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(10000);
    Serial.print("Connecting.."); //Menghubungkan ke wifi dengan ssid dan password di atas
 
  }
}


