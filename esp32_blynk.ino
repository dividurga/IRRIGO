#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include "DHT.h"

#define DHTPIN 19
#define DHTTYPE DHT11 

const int sensor_pin = 34;
const int sensor_pin2 = 35;
const int sensor_pin3 = 32;
bool l = true;
bool i = true;
bool j = true;


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;




char auth[] = "quj92szKHA-cgfUlC5pwkaoSAqyo-oZt";       // You should get Auth Token in the Blynk App.
char ssid[] = "ad";
char pass[] = "divij@123";

void sendSensor1()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
    
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
 
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V5, h);

}

void setup() {
  Serial.begin(9600);
  Serial.println("WiFi connected");
  Blynk.begin("quj92szKHA-cgfUlC5pwkaoSAqyo-oZt", "ad", "divij@123");

dht.begin();
timer.setInterval(2000L, sendSensor1);

}


void loop() {

  Blynk.run();
  timer.run();
 
  float moisture_percentage;
  float moisture_percentage2;
  float moisture_percentage3;
  int sensor_analog;
  int sensor_analog2;
  int sensor_analog3;
  sensor_analog = analogRead(sensor_pin);
  sensor_analog2 = analogRead(sensor_pin2);
  sensor_analog3 = analogRead(sensor_pin3);
  moisture_percentage = ( 100 - ( (sensor_analog / 4095.00) * 100 ) );
  moisture_percentage2 = ( 100 - ( (sensor_analog2 / 4095.00) * 100 ) );
  moisture_percentage3 = ( 100 - ( (sensor_analog3 / 4095.00) * 100 ) );



  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage, moisture_percentage2);
  Serial.print("%\n\n");
  delay(1000);

  if ((moisture_percentage <= 60) && (l == true))

  {
    Blynk.notify("Water Plant 1");
    Serial.println("Water your Plant");
    l = false;
    Serial.println(moisture_percentage);
  }

  if (moisture_percentage > 88)
  {
    l = true;
  }

  if ((moisture_percentage2 <= 40) && (i == true))

  {
    Blynk.notify("Water Plant 2");
    Serial.println("Water your Plant");
    i = false;
    Serial.println(moisture_percentage);
  }

  if (moisture_percentage2 > 70)
  {
    i = true;
  }

  if ((moisture_percentage3 <= 20) && (j == true))

  {
    Blynk.notify("Water Plant 3");
    Serial.println("Water your Plant");
    j = false;
    Serial.println(moisture_percentage);
  }

  if (moisture_percentage3 > 40)
  {
    j = true;
  }


}
