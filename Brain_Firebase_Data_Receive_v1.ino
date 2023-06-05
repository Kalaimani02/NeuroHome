#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Set these to run example.
#define FIREBASE_HOST "<Your_Firebase_Host_address>"
#define FIREBASE_AUTH "<Your_Auth_Key>"
#define WIFI_SSID "<Your_WiFi_ssid>"
#define WIFI_PASSWORD "<Your_Wifi_pass>"
#define LED D1
FirebaseData EEGData;
int Att=0, Med=0, count=0;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);
  delay(1000);
}

void loop()
{
    if(GetInst())
    {
      Att = GetAttention();
      Med = GetMeditation();
      Serial.print("Attention:"); Serial.print(Att);
      Serial.print(", Meditation:"); Serial.println(Med);
      Firebase.setBool(EEGData,"/NewInst",false) ? NULL : Serial.println(EEGData.errorReason());
      Light_control(Att);
    }
    
}

int GetAttention()
{
  return Firebase.getInt(EEGData, "/Attention") ? EEGData.to<int>() : Serial.println(EEGData.errorReason());
}

int GetMeditation()
{
  return Firebase.getInt(EEGData, "/Meditation") ? EEGData.to<int>() : Serial.println(EEGData.errorReason());
}

bool GetInst()
{
  return Firebase.getBool(EEGData, "/NewInst") ? EEGData.to<bool>() ? true : false : Serial.println(EEGData.errorReason());
}

void Light_control(int Att)
{
    if(Att > 65) 
    {
      if(count == 0) 
      {
        digitalWrite(LED,!digitalRead(LED));
      }
      count++;
    }
    else
    {
      count=0;
    }
}
