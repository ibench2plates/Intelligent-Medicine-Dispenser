#include <WiFi.h> 
#include <WiFiClientSecure.h> 
#include <UniversalTelegramBot.h> 
#include <ArduinoJson.h> 
#include <ESP32Servo.h> 
 
Servo servo1; 
Servo servo2; 
 
 
// Wifi network station credentials 
#define WIFI_SSID "PhysicsGA" 
#define WIFI_PASSWORD "xxxx" 
// Telegram BOT Token (Get from Botfather) 
#define BOT_TOKEN "5544380907:AAGo-0ZMIAd-UMOqtwpCgPVLu0RSxNRSuC4" 
 
// Use @myidbot (IDBot) to find out the chat ID of an individual or a group 
// Also note that you need to click "start" on a bot before it can 
// message you 
#define CHAT_ID "5284463373" 
 
 
WiFiClientSecure secured_client; 
UniversalTelegramBot bot(BOT_TOKEN, secured_client); 
 
unsigned long bot_lasttime; 
 
 
//message handler 
bool waiting = false; 
 
struct person { String id; String name_id; bool meds[2];}; 
//Wrapper struct for ID, name and medicine type 
struct person valid_id[3] = { {"123A", "WJ", {0,1}} , {"234B", "JOVEN", {1,0}},{"567C", "ZAHIR", {1,1}}};  
 
 
float get_distance() 
{ 
  digitalWrite(22, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(22, LOW); 
 
  float duration = pulseIn(23, HIGH); 
  float distance = (duration*.0343)/2; 
   
   
  return distance; 
} 
 
void spin_servo(bool meds[2]) 
{ 
    if (meds[0] == true) 
    { 
      servo1.write(75); 
      delay(500); 
      servo1.write(10); 
    } 
    if (meds[1] == true) 
    { 
      servo2.write(75); 
      delay(500); 
      servo2.write(0); 
    } 
     
} 
 
void handleNewMessages(int numNewMessages) 
{ 
  for (int i = 0; i < numNewMessages; i++) 
  { 
    Serial.println("got message"); 
    if (bot.messages[i].text == "get_med" && !waiting) 
    { 
      bot.sendMessage(bot.messages[i].chat_id, "Key in your ID", ""); 
      waiting = true; 
    } 
    else if (waiting) 
    { 
      for (int j = 0; j<3; j++) 
      { 
        if (bot.messages[i].text == valid_id[j].id) 
        { 
          bot.sendMessage(bot.messages[i].chat_id, "Hello " + valid_id[j].name_id, ""); 
          waiting = false; 
          if (get_distance() > 10.0) 
            bot.sendMessage(bot.messages[i].chat_id, "Put cup closer. Re-send get_med.", ""); 
          else 
            spin_servo(valid_id[j].meds); 
          break; 
        } 
      } 
      if (waiting) 
      { 
        bot.sendMessage(bot.messages[i].chat_id, "Invalid ID", ""); 
        waiting = false; 
      } 
       
    } 
  } 
} 
 
//Setup stuff
void setup() { 
  setCpuFrequencyMhz(80); //reduce clock speed; chip was getting hot at 240MHz 
  Serial.begin(115200); 
  Serial.println(); 
 
 
//WIFI connection and telegram connection template 
 // attempt to connect to Wifi network: 
  Serial.print("Connecting to Wifi SSID "); 
  Serial.print(WIFI_SSID); 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org 
  while (WiFi.status() != WL_CONNECTED) 
  { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.print("\nWiFi connected. IP address: "); 
  Serial.println(WiFi.localIP()); 
 
