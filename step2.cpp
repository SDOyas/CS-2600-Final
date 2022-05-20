#include <WiFi.h>
#include <PubSubClient.h>

int led1Pin = 2;
int led2Pin = 4;
int led3Pin = 12;
int led4Pin = 13;

// WiFi
const char *ssid = "Oyas"; // Enter your WiFi name
const char *password = "7144713266";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "192.168.0.32";
const char *topic = "esp32/test";
//const char *mqtt_username = "emqx";
//const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 // LED Output
 pinMode(led1Pin, OUTPUT);
 pinMode(led2Pin, OUTPUT);
 pinMode(led3Pin, OUTPUT);
 pinMode(led4Pin, OUTPUT);
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str())){
         Serial.println("MQTT broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
 client.publish(topic, "Hi I'm ESP32 ^^");
 client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 String message;
 for (int i = 0; i < length; i++) {
     message = message + (char) payload[i];
 }
  Serial.print(message);
  if (message == "1") { digitalWrite(led1Pin, HIGH); } // LED on
  if (message == "11") { digitalWrite(led1Pin, LOW); } // LED off
  if (message == "2") { digitalWrite(led2Pin, HIGH); } 
  if (message == "22") { digitalWrite(led2Pin, LOW); } 
  if (message == "3") { digitalWrite(led3Pin, HIGH); } 
  if (message == "33") { digitalWrite(led3Pin, LOW); } 
  if (message == "4") { digitalWrite(led4Pin, HIGH); } 
  if (message == "44") { digitalWrite(led4Pin, LOW); } 
  Serial.println();
  Serial.println("-----------------------");
}

void loop() {
 client.loop();
}