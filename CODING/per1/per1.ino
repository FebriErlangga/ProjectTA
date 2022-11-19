#include <dummy.h>


#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 18
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensorSuhu(&oneWire);

#define led 19
float nilai_suhu;

void setup() 
{
 Serial.begin(115200);
 pinMode(led, OUTPUT);
   digitalWrite(led, HIGH);
}

float baca_suhu(){
  sensorSuhu.requestTemperatures();
  float suhu = sensorSuhu.getTempCByIndex(0);
  return suhu; }

void loop() 
{
  nilai_suhu=baca_suhu();
  Serial.print(nilai_suhu);
  Serial.println("Celcius");
}
