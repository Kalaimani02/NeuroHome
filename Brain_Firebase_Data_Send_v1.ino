#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Set these to run example.
#define FIREBASE_HOST "<Your_Firebase_Host_address"
#define FIREBASE_AUTH "<Your_Auth_Key>"
#define WIFI_SSID "<Your_WiFi_ssid>"
#define WIFI_PASSWORD "<Your_Wifi_pass>"
#define BAUDRATE 57600

// Set up serial connection with Mindwave headset
SoftwareSerial mindwaveSerial(D5, D6); //RX,TX
FirebaseData EEGData;

byte payloadData[32] = {0};
byte checksum = 0;
byte generatedchecksum = 0;
int Plength,Temp,Temp1;
int k=0;
signed int j=0;

void setup() 
{
  Serial.begin(9600);
  mindwaveSerial.begin(BAUDRATE);

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

byte ReadOneByte()
{
  int ByteRead;
  while(!mindwaveSerial.available());
  ByteRead = mindwaveSerial.read();
  //Serial.println(ByteRead);
  return ByteRead;
}

void loop() 
{
  while(1)
  {
    Decode_TGAM(payloadData);
  }
}

void Decode_TGAM(byte payloadData[])
{
  if(ReadOneByte() == 170)
    {
      if(ReadOneByte() == 170)
      {
        Plength = ReadOneByte();
        //Serial.println(Plength);
        if(Plength == 32)
        {
          generatedchecksum = 0;
          for(int i=0;i<Plength;i++)
          {
            payloadData[i] = ReadOneByte();
            generatedchecksum += payloadData[i];
            //Serial.println(payloadData[i]);
          }
          generatedchecksum = 255 - generatedchecksum;
          checksum = ReadOneByte();

          if(checksum == generatedchecksum)
          {
            Serial.println("IN");
            GetAttention(payloadData);
            GetMeditation(payloadData);
            Firebase.setBool(EEGData,"/NewInst",true) ? NULL : Serial.println(EEGData.errorReason());
          }
        }
      }
    }
}

void GetAttention(byte payloadData[])
{
  int Att_Avg=0;
  if(payloadData[28]==4)
  {
    if(j<3)
    {
       Temp += payloadData[29]; //Attention
       j++;
    }
    else
    {
       Att_Avg = Temp/3;
       Firebase.setInt(EEGData, "/Attention",Att_Avg) ? Serial.print("Att OK, ") : Serial.println(EEGData.errorReason());
       j=0; Temp = 0;
    }
  }
}

void GetMeditation(byte payloadData[])
{
  int Med_Avg=0;
  if(payloadData[30]==5)
  {
    if(k<3)
    {
       Temp1 += payloadData[31]; //Meditation
       k++;
    }
    else
    {
       Med_Avg = Temp1/3;
       Firebase.setInt(EEGData, "/Meditation",Med_Avg) ? Serial.println("Med OK") : Serial.println(EEGData.errorReason());
       k=0; Temp1=0;
    }
  }
}
