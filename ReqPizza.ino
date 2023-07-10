#include <ESP8266WiFi.h>

// Replace with your SSID and Password
const char* ssid     = "AndroidAP536C";
const char* password = "sss22222";


const char* resource = "/asciiart/pizza.txt";
const char* server = "fiikus.net";
const char* resource1 = "/asciiart/face.txt";


void setup() {
  Serial.begin(115200); 

  initWiFi();
  SendReqPizza();
  delay(1000);
  SendReqChatdemo();
  ESP.deepSleep(0);

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void initWiFi(){
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  
  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }
  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

void SendReqPizza(){
  Serial.print("Connecting to "); 
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while(!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!client.connected()){
    Serial.println("Failed to connect, going back to sleep");
  }
  Serial.print("Request resource: "); 
  Serial.println(resource);
  client.print(String("GET ") + resource + 
                  " HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" + 
                  "Connection: close\r\n\r\n");
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!client.available()) {
     Serial.println("No response, going back to sleep");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop();

}

void SendReqChatdemo(){
  Serial.print("Connecting to "); 
  Serial.print(server);

  WiFiClient client1;
  int retries = 5;
  while(!client1.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!client1.connected()){
    Serial.println("Failed to connect, going back to sleep");
  }
  Serial.print("Request resource: "); 
  Serial.println(resource);
  client1.print(String("GET ") + resource1 + 
                  " HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" + 
                  "Connection: close\r\n\r\n");
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client1.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!client1.available()) {
     Serial.println("No response, going back to sleep");
  }
  while(client1.available()){
    Serial.write(client1.read());
  }
  
  Serial.println("\nclosing connection");
  client1.stop();

}