#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESPTEST";      
const char* password = "123456789";
const char* serverUrl = "http://192.168.18.58:3000/api/telemetry"; 
const char* device_id = "GATE_B"; 
const int ledPin = 2; 

void sendTelemetry();

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, HIGH);

  Serial.print("Connecting to WiFi\n");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP: "); 
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("Simulating Person Entry...");
  
  sendTelemetry();

  int waitTime = random(2000, 5000); 
  delay(waitTime);
}

void sendTelemetry() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"device_id\": \"" + String(device_id) + "\", \"count\": 1}";
    
    int httpResponseCode = http.POST(jsonPayload);
    
    if(httpResponseCode > 0){
      Serial.print("Server Response: ");
      Serial.println(httpResponseCode); 
    } else {
      Serial.print("HTTP Error: ");
      Serial.println(httpResponseCode);
    }
    http.end();
    digitalWrite(ledPin, LOW); 

  } else {
    Serial.println("WiFi Disconnected");
  }
}