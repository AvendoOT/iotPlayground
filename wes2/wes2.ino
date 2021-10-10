#include <BlynkSimpleEsp8266.h>

#include <TimeLib.h>
#include <Time.h>

#include "ESP8266WiFi.h"
#include <dht.h>
#include "HttpClient.h"
#include "time.h"

#define port 3000
#define dataPin 2

int lamp = 16;
int pwmlamp = 14;
int s;
int led = 5;
int dim;

const char* ssid = "AndroidHotspot1857";
const char* password = "volimtekralju";
const char* host = "10.129.6.18";
const char* auth = "4aJrCZeI5XUzm0lc6cywrjovpsXrS2AJ";

dht DHT;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(led, OUTPUT);
  pinMode(lamp, OUTPUT);

  WiFi.begin(ssid, password);
  Blynk.begin(auth, ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.print("Successfully connected to WiFi! Local IP adress is: ");
  Serial.println(WiFi.localIP());

  Serial.println("Sending data every 5 seconds");
  
}

void loop() {

  Blynk.run();

  time_t t = now();
  s = second(t);
  digitalWrite(lamp, HIGH);
  analogWrite(pwmlamp, dim);
  analogWrite(0, 255);

  int readData = DHT.read11(dataPin); // Reads the data from the sensor
  float temp = DHT.temperature; // Gets the values of the temperature
  float hum = DHT.humidity; // Gets the values of the humidity

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);

  if(isnan(temp) || isnan(hum)) {
    Serial.print(hum);
    Serial.print(temp);
    Serial.println("Failed to read temperature or humidity from DHT sensor");
  } else {
    if (hum> 50){
      digitalWrite(led, HIGH);
    }
    else {
      digitalWrite(led, LOW);
    }
    if (s > 0 && s < 10) {
      dim = 255;
    }
    else if ( s > 10 && s < 20) {
      dim = 2;
    }
    else {
      dim = 0;
    }
    if (!client.connect(host, port)) {  
      Serial.println("Cannot connect to that webpage"); // if connection fails
      return;
    }
    String url = "/measurement/\?temperature=";
    client.print(String("GET ") + url + temp + "&humidity=" + hum + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  }

  delay(1000);
}
