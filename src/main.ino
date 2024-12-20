#include "DHT.h"

#define DHT0PIN 8  
#define DHT1PIN 9    
#define DHT2PIN 10   
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define Humidity_Low_PIN 13
#define Humidity_High_PIN 14

#define Heater_Low_PIN 15
#define Heater_High_PIN 16 

#define Cooler_Low_PIN 17
#define Cooler_High_PIN 18

DHT dht0(DHT0PIN, DHTTYPE,4);
DHT dht1(DHT1PIN, DHTTYPE,4);
DHT dht2(DHT2PIN, DHTTYPE,4);

void setup() {

 Serial.begin(9600); 
 Serial.println("DHTxx test!");
 
 pinMode(Humidity_Low_PIN,OUTPUT);
 pinMode(Humidity_High_PIN,OUTPUT);
 
 pinMode(Heater_Low_PIN,OUTPUT);
 pinMode(Heater_High_PIN,OUTPUT);
 
 pinMode(Cooler_Low_PIN,OUTPUT);
 pinMode(Cooler_High_PIN,OUTPUT);
 
 dht0.begin();
 dht1.begin();
 dht2.begin();
}
 
void loop(void) {

 float h0 = dht0.readHumidity();
 float t0= dht0.readTemperature();
 
 if (isnan(h0) || isnan(t0)) {
    Serial.println("Failed to read from DHT0 sensor!");
    return;
  }
 
 float h1 = dht1.readHumidity();
 float t1 = dht1.readTemperature();
 
 if (isnan(h1) || isnan(t1)) {
    Serial.println("Failed to read from DHT1 sensor!");
    return;
  }
  
 float h2 = dht2.readHumidity();
 float t2 = dht2.readTemperature();
 
 if (isnan(h2) || isnan(t2)) {
    Serial.println("Failed to read from DHT2 sensor!");
    return;
  }
  
 float avgT; // avgT = average of Temperture
 avgT = (t0+t1+t2)/3;
 
 float avgH; //  avgH = average of Humidity
 avgH = (h0+h1+h2)/3;
 
 
 if(avgT<28){
  digitalWrite(Cooler_Low_PIN,LOW);
  digitalWrite(Cooler_High_PIN,LOW);
  delay(2000); }
  
 if(avgT>38){
  digitalWrite(Cooler_Low_PIN,LOW);
  digitalWrite(Cooler_High_PIN,HIGH);
  delay(2000); }
  
  else if(avgT>32){
  digitalWrite(Cooler_Low_PIN,HIGH);
  digitalWrite(Cooler_High_PIN,LOW);
  delay(2000); }


 if(avgT>23){
  digitalWrite(Heater_Low_PIN,LOW);
  digitalWrite(Heater_High_PIN,LOW);
  delay(2000);}

 if(avgT<15){
  digitalWrite(Heater_Low_PIN,LOW);
  digitalWrite(Heater_High_PIN,HIGH);
  delay(2000); }

 else if(avgT<20){
 digitalWrite(Heater_Low_PIN,HIGH);
 digitalWrite(Heater_High_PIN,LOW);
 delay(2000); }

  
 if(avgH>85){
  digitalWrite(Humidity_Low_PIN,LOW);
  digitalWrite(Humidity_High_PIN,LOW);
  delay(2000); }
  
 if(avgH<70){
  digitalWrite(Humidity_Low_PIN,LOW);
  digitalWrite(Humidity_High_PIN,HIGH);
  delay(2000); }
  
 else if(avgH<80){
 digitalWrite(Humidity_Low_PIN,HIGH);
 digitalWrite(Humidity_High_PIN,LOW);
 delay(2000); }



  Serial.print("Humidity: "); 
  Serial.print(avgH);
  Serial.print(" %           ");
  Serial.print("Temperature: "); 
  Serial.print(avgT);
  Serial.println(" *C ");
  Serial.println(" ");

 }
 
