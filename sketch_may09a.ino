#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

int sensor = 13;              // the pin that the sensor is atteched to
int buzzerPin=D5;
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

const char* ssid="Manasa's Galaxy F42 5G";
const char* password = "varshaisawesome";
WiFiClient  client;
unsigned long myChannelNumber = 2152211;
const char* myWriteAPIKey = "XGCEAJMFMDBEI623";

void setup() {
  pinMode(D4,OUTPUT);
  digitalWrite(D4,LOW);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  digitalWrite( D4 , HIGH);
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  ThingSpeak.begin(client); 

  pinMode(buzzerPin, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
}

void loop() {  
     ThingSpeak.setField(1,val);
      val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
      digitalWrite(buzzerPin, HIGH);   // turn LED ON
    delay(1000);
    digitalWrite(buzzerPin, LOW);
    
    if (state == LOW) {   
      Serial.println("Motion was detected");
      state = HIGH;       // update variable state to HIGH
     }
  } 
  else {
       digitalWrite(buzzerPin, LOW); // turn LED OFF
      delay(200);    
      
      if (state == HIGH){
        state = LOW;       // update variable state to LOW
    }
  }
     { int x = ThingSpeak.writeField(myChannelNumber,1,val,myWriteAPIKey);
if(x == 200){
     Serial.println(val);
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  // delay(15000);  
  } 
}
