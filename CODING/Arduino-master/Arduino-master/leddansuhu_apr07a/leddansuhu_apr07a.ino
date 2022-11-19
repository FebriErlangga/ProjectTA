#include <WiFi.h>
#include <DHT.h>
#define BLYNK_PRINT Serial

int ledm =5;


char auth[]="btR2vOsGgOWarArvtAcpyfezS1O0qcou";
char ssid[]="Yoru";
char pass[]="ihandlethis16";

#define DHTPIN 18
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {
  // put your setup code here, to run once:
  Blynk.begin(auth,ssid,pass);
  Serial.begin(115200);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
    pinMode(ledm, OUTPUT);
    pinMode(ledk, OUTPUT);
    pinMode(ledh, OUTPUT);

}

BLYNK_WRITE(V1){
  int runled = param.asInt();
  if (runled == HIGH){
    digitalWrite(ledm, HIGH);
      delay(500);
    digitalWrite(ledk, HIGH);
      delay(500);
    digitalWrite(ledh, HIGH);
      delay(500);

    digitalWrite(ledh, LOW);
      delay(500);
    digitalWrite(ledk, LOW);
      delay(500);
    digitalWrite(ledm, LOW);
      delay(500);
  }
  if (runled == LOW){
    digitalWrite(ledm, LOW);
    digitalWrite(ledk, LOW);
    digitalWrite(ledh, LOW);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
