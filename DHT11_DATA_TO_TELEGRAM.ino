#include <DHT.h> //Look at Section 1 Unit 6 for more info
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "network-name";
const char* password = "network-password";

#define DHT_PIN D4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE); //configure dht mode, which pin and what type

#define BOTtoken "0000000000:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"  // Token that we already collect
#define CHAT_ID "000000000" //Chat ID which we got from Bot with "getid"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  client.setInsecure();
  
  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up\nWaiting for sensor to get temperature", "");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  getTemperature();
  delay(10000); // NodeMCU will send every 10 Seconds to Our Bot
}

void getTemperature(){
  float temperatur = dht.readTemperature();
  float kelembaban = dht.readHumidity();
  
  Serial.print("\nTemperatur : ");
  Serial.print(temperatur);
  Serial.print(" °C\nKelembaban : ");
  Serial.print(kelembaban);
  Serial.print("\n");
  
  String temp = "Temperature : "+String((int)temperatur)+" C";
  String humd = "Humidity : "+String((int)kelembaban)+" %";
  bot.sendMessage(CHAT_ID, temp+"\n"+humd, "");
}
