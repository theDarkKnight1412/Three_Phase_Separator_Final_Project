#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

//addonnya nggih 
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

//wifi api dan lain lain
#define WIFI_SSID "loll"
#define WIFI_PASSWORD "dwikiopganteng"
#define API_KEY "AIzaSyBe9fRKlnYlljyceRQEcuXn-CoiuFuojPQ"
#define DATABASE_URL "https://human-machine-interface-336e5-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//inisialisasi firebase data objek ke kodingan 
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

void initFirebase(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}
void writeToFirebase(float data, const char *path){
  Firebase.RTDB.setFloat(&fbdo, path, data);
  }

// float readFromFirebase(const char *path){
//  }
