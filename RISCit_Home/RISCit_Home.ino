#include <ESP8266WiFi.h>

const char* ssid     = "wes";
const char* password = "riscit";

int BRIGHTNESS = 0;
int new_BRIGHTNESS = 0;

WiFiServer server(80);

String header;

String output2State = "off";
String output13State = "off";

const int output2 = 2;
const int output13 = 13;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  pinMode(output2, OUTPUT);
  pinMode(output13, OUTPUT);
  pinMode(12,INPUT_PULLUP);

  digitalWrite(output2, LOW);
  digitalWrite(output13, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop() {
  static int min=100;
  static int max=600;
  int send = analogRead(A0);
  Serial.println(send);

  float calc=(100.0-100.0*(send-min)/(max-min));
  if (calc>100) calc=100;
  else if(calc<0) calc=0;
  String aml=String(calc);
  WiFiClient client = server.available();   
  
  if (!client){
    client.readStringUntil('>');
    return;
  }  
    
  if (client){    
    Serial.println("New Client.");          
    String currentLine = "";                
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { 
      currentTime = millis();         
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                   
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if(header.indexOf("slider")>=0){
              int index=header.indexOf("=");
              String value = header.substring(index+1, header.length());
              int pwm_val= value.toInt();
              new_BRIGHTNESS=pwm_val;
              analogWrite(0,pwm_val);
            }
            
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            } else if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("GPIO 13 on");
              output13State = "on";
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("GPIO 13 off");
              output13State = "off";
              digitalWrite(output13, LOW);
            }
                       
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 5px 20px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            client.println("<body><h1>RISCit home</h1>");
                
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">SOBA 1 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">SOBA 1 OFF</button></a></p>");
            } 
       
            if (output13State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">SOBA 2 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">SOBA 2 OFF</button></a></p>");
            }
            client.println("</body></html>");


            String sResponse = "</p>";
            sResponse += "<form action=\"\" >";  
            sResponse += "<BR>Osvjetljenje SOBA 3 : &nbsp;&nbsp";  
            sResponse += round(new_BRIGHTNESS / 2.5);    
            sResponse += " %";
            sResponse += "<BR>";
            sResponse += "<input style=\"width:200px; height:50px\" type=\"range\" name=\"=slider\" id=\"cmd\" value=\"";   
            sResponse += BRIGHTNESS;
            sResponse += "\" min=0 max=250 step=5 onchange=\"showValue(points)\" />";
            sResponse += "<BR><BR>";
            sResponse += "<input type=\"submit\">";
            sResponse += "</form>";
            sResponse += "<p>";

            client.println(sResponse);

            client.println("<p> Osvjetljenje SOBA 4 :</p>");
            client.println("<h1>" + aml + "%</h1>");
            client.println("<p><a href=\"/\"><button class=\"button\">Osvjezi</button></a></p>");
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}  
