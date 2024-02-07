#include <PubSubClient.h>
#include "WiFi.h"
#include <Tomoto_HM330X.h>

Tomoto_HM330X sensor;

// Network credentials
const char* ssid = "WAEL-PC";
const char* password = "Aulnay93";

// MQTT credentials
const char* mqtt_server = "mqtt.flespi.io";
const int mqtt_port = 1883; 
const char* mqtt_user ="zmfAERX4akr6mAu9UrmHBvlqOYMFY2VndYNFFyzDJQzVhRSZ92uymFOYrqrghcti";
const char* mqtt_pwd = "";

WiFiClient espClient;
PubSubClient client(espClient);

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to Wifi with IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  if ((char)payload[0] == 'O' && (char)payload[1] == 'N') //on
  {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println(" ->> on");
    client.publish("lpdw", "LED turned ON");

    // Affichage des valeurs du capteur HM330X uniquement lorsque le message est "ON"
    if (sensor.readSensor()) {
      
      client.publish("lpdw", String(sensor.std.getPM2_5()).c_str());
    } else {
      Serial.println("Failed to read HM330X");
    }
  }
  else if ((char)payload[0] == 'O' && (char)payload[1] == 'F' && (char)payload[2] == 'F') //off
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(" ->> off");
    client.publish("lpdw", "LED turned OFF");
  }
  Serial.println();
}

void connectmqtt()
{
  client.connect("ESP32_clientID", mqtt_user, mqtt_pwd);  // ESP will connect to mqtt broker with clientID
  {
    Serial.println("connected to MQTT");
    // Once connected, publish an announcement...

    // ... and resubscribe
    client.subscribe("lpdw"); //topic=Demo
    client.publish("lpdw",  "Xiao connected to MQTT!");

    if (!client.connected())
    {
      reconnect();
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32_clientID", mqtt_user, mqtt_pwd)) {
      Serial.println("(re)connected");
      // Once connected, publish an announcement...
      client.publish("lpdw", "Xiao connected to MQTT");
      // ... and resubscribe
      client.subscribe("lpdw");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  if (!sensor.begin()) {
    Serial.println("Failed to initialize HM330X");
    while (1)
      ;
  }

  Serial.println("HM330X initialized");
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  initWiFi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  connectmqtt();
}

void loop() {
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();
}
