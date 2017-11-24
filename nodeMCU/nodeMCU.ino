#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

SoftwareSerial NodeSerial(D7, D8); // RX | TX
 
String msg,URL; 
const char* ssid = "ArduiNug";
const char* password = "#ravelinug";
 
void setup () { 
  NodeSerial.begin(4800);
  Serial.begin(9600); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  } 
}
 
void loop() {

  while (NodeSerial.available()) {
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      Serial.println("Conected");  
      HTTPClient http;  //Declare an object of class HTTPClient
      msg = NodeSerial.readStringUntil('\n');
      URL = "http://192.168.0.12/";
      URL += msg;
      http.begin(URL);  //Specify request destination
      int httpCode = http.GET();                                                                  //Send the request

      if (httpCode > 0) { //Check the returning code

        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);                     //Print the response payload

      }

    http.end();   //Close connection

    }
  }
  delay(500);    //get a request every 30 seconds
 
}


