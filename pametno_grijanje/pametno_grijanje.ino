//ESP8266WiFi library for ESP8266 module
#include <ESP8266WiFi.h>
#include <dht11.h>
#define DHT11PIN 12

dht11 DHT11;
 
// AP credentials
const char AP_Password[] = "12345678";
const char AP_Name[] = "Croduino_AP";
 
// AP port
WiFiServer server(80);

// html strings for creating web view
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width,"
" initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;}"
" #main {display: table; margin: auto; padding: 0 10px 0 10px; } h2,{text-align:center; }"
" .button { padding:10px 10px 10px 10px; width:100%; background-color: #4CAF50; font-size: 120%;}</style>"
"<title>AP LED</title></head><body><div id='main'><h2>Kontrola temperature</h2>";
String html_set_temperature = "";
String html_end = "</div></body></html>";

// input field and submit for seting temperature
String html_submit_temperature = "<form id='F1' action='SET_TEMPERATURE'><input type='text' id='lname' name='temperature'><br><br><input type='submit' value='Postavi temperaturu' ></form><br>";

// LED_red pin 16(heating) -> LED_blue pin 14 (cooling)
int LED_red = 16;
int LED_blue=14; 

int stringSpliceIndex = 33;

bool cooling = false;
bool heating = false;

int lowBoundary = 2;
int highBoundary = 2;
  
void setup() 
{
 Serial.begin(9600);
 pinMode(LED_red, OUTPUT); 
 pinMode(LED_blue, OUTPUT);
 boolean conn = WiFi.softAP(AP_Name, AP_Password);
 server.begin();

 digitalWrite(LED_red,LOW);
 digitalWrite(LED_blue,LOW); 
}

// function that slices string from the end of GET request through first empty space.
// Sliced string that represents the user given temperature is converted to integer and returned
int spliceStringAndReturnInt(String initialString){
  String spliced = initialString.substring(stringSpliceIndex);
  int sliced_length = sliced.length()+1;
  char charArray[sliced_length];
  sliced.toCharArray(charArray, sliced_length);
  char* text = strtok(charArray, " ");
  String newText(text);
  return newText.toInt();
}
  
void loop() 
{
 String html_print_temperature = "Trenutna temperatura prostorije : ";
 WiFiClient client = server.available();
 if (!client) { return; }
 html_set_temperature = client.readStringUntil('\r');

int setTemperature = spliceStringAndReturnInt(html_set_temperature);

int chk = DHT11.read(DHT11PIN);
int currentTemperature = (float)DHT11.temperature;
html_print_temperature = html_print_temperature + currentTemperature;
 
if (setTemperature != 0) { // if temperature is given
 if(currentTemperature < setTemperature - lowBoundary) { //heating -> system is heating up to the given temperature (offset by low boundary) -> if lower
  digitalWrite(LED_red,HIGH); // LED diode is signalizing heating 
  heating = true; // flag that indicates system is in heating mode
 } else if (currentTemperature > setTemperature + highBoundary) { //cooling -> system is cooling down to the given temperature (offset by upper boundary) -> if higher
  digitalWrite(LED_blue,HIGH); // LED diode is signalizing cooling down
  cooling=true; // flag that indicated system is in cooling down mode
 } 
 if(heating && currentTemperature >= setTemperature) { // heating mode is shut off when the wanted temperature is reached
  digitalWrite(LED_red,LOW);
  heating = false;
 } 
 if(cooling && currentTemperature <= setTemperature) { // cooling mode is shut off when the wanted temperature is reached
  digitalWrite(LED_blue,LOW);
  cooling = false;
  }
} 

 client.flush();
 client.print( header );
 client.print( html_1 );
 
 client.print(html_submit_temperature);
 client.print(html_print_temperature);
 
 client.print( html_end);
  
 delay(5);
 
}
