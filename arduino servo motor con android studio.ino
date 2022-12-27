#include <WiFi.h>

#include

#include <FILENAME.>

#include <NTPClient.h>

#include <WiFiUdp.h>

#define FIREBASE_HOST "https://basededatosappdispet-default-rtdb.firebaseio.com"

#define FIREBASE_AUTH "sCzwZPUqeBTHFbsYpUuaRwMK3wT9bTo5tKE9ovDn"

#define WIFI_SSID "Olivares"

#define WIFI_PASSWORD "208270508-88457067"

// Define NTP Client to get time

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP);

// Variables to save date and time

String formattedDate;

String dayStamp;

String timeStamp;

//Define FirebaseESP32 data object

FirebaseData firebaseData;

FirebaseJson json;


int angle = 161
int online = 0
int withAsus = 0
int withXt = 0


int valuePrueba = 13;

void setup()

{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)

  {

    Serial.print(".");

    delay(300);

  }

  Serial.println();

  Serial.print("Connected with IP: ");

  Serial.println(WiFi.localIP());

  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);

 //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).

  Firebase.setwriteSizeLimit(firebaseData, "");

}

void loop()

{

    while(!timeClient.update()) {

      timeClient.forceUpdate();

    }

    formattedDate = timeClient.getFormattedDate();

    json.clear().add("Value", valuePrueba);

    json.add("Date", formattedDate);

    if (Firebase.pushJSON(firebaseData, angle + online + withAsus + withXt, json))

    {

      Serial.println("PASSED");

      Serial.println("PATH: " + firebaseData.dataPath());

      Serial.print("PUSH NAME: ");

      Serial.println(firebaseData.pushName());

      Serial.println("ETag: " + firebaseData.ETag());

      Serial.println("------------------------------------");

      Serial.println();

    }

    else

    {

      Serial.println("FAILED");

      Serial.println("REASON: " + firebaseData.errorReason());

      Serial.println("------------------------------------");

      Serial.println();

    }

 

    delay(1000);

}