const int irSensorPin1 = 12;  
const int irSensorPin2 = 14;  
const int ldrPin = 32;       
const int ledPins[]={0,4,16,17};  
const int ldrPins[]={34,35,33,21};
unsigned long previousMillis = 0;
unsigned long previousMilli = 0;
bool ledsOn = false;
bool led =false;  
const int glowDuration = 5000;  
  float latitude;
  float longitude;


#include <Arduino.h>

#include <WiFi.h>

#include <Firebase_ESP_Client.h>
#include <TinyGPS++.h>
#define GPS_SERIAL Serial2 
#define GPS_BAUD 9600  

#include "addons/TokenHelper.h"

#include "addons/RTDBHelper.h"


#define WIFI_SSID "streetlight"
#define WIFI_PASSWORD "12345678"
TinyGPSPlus gps;

#define API_KEY "PASTE_YOUR_API_KEY_OF_PROJECT"

#define DATABASE_URL "PASTE_YOUR_REALTIME_DATABASE_URL_FROM_FIREBASE" 


FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup() {
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
 pinMode(ldrPin, INPUT);
   latitude = 0.0;
    longitude =0.0;

 for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(ldrPins[i],INPUT);
  }
  Serial.begin(9600);

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

 
  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;

 
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }


  config.token_status_callback = tokenStatusCallback; 
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
}



void loop() {
  int ldrValue = analogRead(ldrPin); 

  if (ldrValue > 500 && digitalRead(irSensorPin1) == LOW) { 
  
    turnOnLEDs();
     checkAndSendLEDStatus();
    previousMillis = millis();
    ledsOn = true;
  }

  
  if (ledsOn && (millis() - previousMillis >= glowDuration || digitalRead(irSensorPin2) == LOW) && ldrValue > 500 ) {
   
   
    turnOffLEDs();
     turnOnLED();
     checkAndSendLEDStatus1();
     previousMilli =millis();
    ledsOn = false;
    led =true;
  }

   if (led && (millis() - previousMilli >= glowDuration )) {
  
    turnOffLED();
    
   
    led = false;
  }
  delay(500);
}



void checkAndSendLEDStatus() {

  for (int i = 0; i < 2; i++) {
  
    int ldrValue = analogRead(ldrPins[i]);
   
  if (ldrValue > 500) {
 
      Serial.print(i);
      Serial.print(0);
      sendData(i,0); 
       gpstrack();
     sendLocationData(i,latitude ,longitude);     
     delay(1000);
   }
   else{
     Serial.print(i);
      Serial.print(1);
    
    sendData(i,1);
    delay(1000);
   }
  }
}




void checkAndSendLEDStatus1() {

 
  for (int i = 2; i < 4; i++) {
  
    int ldrValue = analogRead(ldrPins[i]);
  
    if (ldrValue > 500) {
      
      Serial.print(i);
      Serial.print(0);
    sendData(i,0);
    gpstrack();
     sendLocationData(i,latitude ,longitude);

     delay(1000);
      //delay(500);
    }else{
       Serial.print(i);
      Serial.print(1);
      sendData(i,1);
       delay(1000);
    }
  }
}


void turnOnLEDs() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}


void turnOffLEDs() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}


void turnOnLED() {
  for (int i = 2; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}


void turnOffLED() {
  for (int i = 2; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}


void gpstrack(){
   while (GPS_SERIAL.available() > 0) {
    if (gps.encode(GPS_SERIAL.read())) {
    
      if (gps.location.isValid()) {
        updateLocations(gps.location.lat(), gps.location.lng());
       
      }
    }
  }
}



void sendData(int i , int status){
   if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo,(String)"ledStatus/led"+i, status)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  
}
}

void updateLocations(float lati, float longi) {

  latitude = lati;
  longitude = longi;
  
}

 void sendLocationData( int i ,float latitude , float longitude){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 200 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setFloat(&fbdo,(String)"faultledlocation/ledLatitude"+i, latitude)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }

      if (Firebase.RTDB.setFloat(&fbdo,(String)"faultledlocation/ledLongitude"+i, longitude)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  
}


 }

