#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "BananaBoat";
//Feel free to change the pass before you flash it to the ESP :P
const char *password = "incorrect";

ESP8266WebServer server(80);

const int DATA_LINES = 100;
String data[DATA_LINES];

/*
* Default address is: http://192.168.4.1
* Connect once you enter the Wifi AP
*/

/*
* This WILL (does not work yet) handle adding the Serial data to the data array
*/
void addData(){
  // I will figure this out later
  Serial.flush();
  /*char * buffer;
  String line[1];
  line[0] = String(buffer);

  if(Serial.readBytesUntil('/', buffer, 10) <= 0){
    return;
  }*/
  /*
  int new_data_lines = 1;
  
  for( unsigned int i = DATA_LINES -1 - new_data_lines; i >= 0; i--){
    data[i] = data[i + new_data_lines];
  }
  
  for( unsigned int i = 0; i < new_data_lines; i++){
    data[i] = line[i];
  }*/
}

/*
* Returns HTML with data
*/
void handleRoot() {
  String html = String("<h1>Banaboat Data</h1>");
  // Should print the Serial text to HTMl if we manage to actually add some data
  for( unsigned int i = 0; i < 100; i++){
    html = html + "<br>";
    html = html + String(data[i]);
  }
  
  server.send(200, "text/html", html);
}

void setup() {  
  delay(1000);
  // Let's fill the data with stuff so we know it's printing
  for( unsigned int i = 0; i < DATA_LINES; i++){
    data[i] = String("--");
  }

  Serial.begin(9600);
  WiFi.softAP(ssid, password);

  IPAddress ip = WiFi.softAPIP(ssid, password);
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  if(Serial.available() > 0){
    addData();
  }
  server.handleClient();
}
