//Program dibuat oleh M Reksa Sanjaya
//Alat monitoring suhu via internet
//ESP & Blynk
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
char auth[] = "F-vrWIk4Ooy92Zyvzw8pICI5A4iAbUlF";

//Wifi
char ssid[] = "reksa";
char pass[] = "reksa123";

//Timer
//#include <SimpleTimer.h>  // Tidak dibutuhkan pada library blynk versi 0.4.8 dan diatasnya
BlynkTimer timer;

//Sensor Suhu DS18B20
#include <OneWire.h>
#include<DallasTemperature.h> 
#define ONE_WIRE_BUS 4 // pin D2 di board di nodeMCU
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;

void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  DS18B20.begin();
  timer.setInterval(1000L, getSendData);
}

void loop() 
{
  timer.run();
  Blynk.run();
}

//mengirim data sensor ke Blynk
void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0);
  Serial.println(temp);
  Blynk.virtualWrite(10, temp); //virtual pin V10 untuk aplikasi Blynk
}
