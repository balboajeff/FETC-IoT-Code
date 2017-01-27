/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     ="sparkfun-workshop";
const char* password = "sparkfun";

const char* host = "data.sparkfun.com";
const char* streamId   = "DJqz9MZQrjijQXKpDoj2";//put your public key in the quotation marks
const char* privateKey = "P4pBao280eiYndvgezY0";//put your private key in the quotation marks
//below is an example feed
//http://data.sparkfun.com/input/DJqz9MZQrjijQXKpDoj2?private_key=P4pBao280eiYndvgezY0&pot1=19.12

void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 51;

void loop() {
  
  //++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/input/";
  url += streamId;
  url += "?private_key=";
  url += privateKey;
  url += "&pot1=";
  url += analogRead(A0);
  
  //sample channel= http://data.sparkfun.com/input/DJqz9MZQrjijQXKpDoj2?private_key=P4pBao280eiYndvgezY0&pot1=19.12
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.print("posted value= ");
  Serial.println(analogRead(A0));
  Serial.println();
  Serial.println("closing connection");
 delay(12000);
}

