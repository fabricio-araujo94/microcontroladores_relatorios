#include <WiFi.h>
#include <PubSubClient.h>

#define SSID ""
#define PASSWORD ""

#define MQTT_SERVER "broker.mqtt.cool"
#define PORT 1883

WiFiClient espClient;
PubSubClient client(espClient);

// LEDS
#define RED 18
#define GREEN 19
#define BLUE 21

void callback(char*, byte*, unsigned int);

void setup() {
  Serial.begin(9600);
  
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  
  
  client.setServer(MQTT_SERVER, PORT);
  client.setCallback(callback);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "led_algum") {
    Serial.print("Changing output to ");
    if(messageTemp == "red"){
      Serial.println("red");
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
    }
    else if(messageTemp == "green"){
      Serial.println("green");
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
    }
    else if(messageTemp == "blue") {
      Serial.println("blue");
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
    }
  }
  
  if(String(topic) == "mensagem_mensagem") {
    Serial.print("Conteúdo da mensagem: ");
    Serial.println(messageTemp);
	Serial.println("");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("led_algum");
	  client.subscribe("mensagem_alguma");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}