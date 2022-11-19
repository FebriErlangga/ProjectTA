#include <WiFi.h>
#include <FirebaseESP32.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//turbidity
float volt;
float ntu;

#define WIFI_SSID "erlanggaaa"
#define WIFI_PASSWORD "12345123"

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  /*WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }*/
  // Tampilan awal pada LCD

  // Start the DS18B20 sensor
  pinMode (15, INPUT);
  sensors.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" DS18B20 with ");
  lcd.setCursor(0, 1);
  lcd.print(" ESP32 DevKit ");
  delay(2000);
  lcd.clear();
}

void loop()
{
  float tmp = ReadTemperature();
  float tbd = ReadTurbidity();
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(tmp);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print(tbd);
  lcd.print(" NTU");
  delay(1000);
}

float ReadTemperature()
{
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  return temperatureC;
}

float ReadTurbidity()
{
  //volt=analogRead(15);
  volt = 0;
  for (int i = 0; i < 50; i++)
  {
    volt += ((float)analogRead(15) / 4096) * 3.3;
  }
  volt = volt / 50;
  volt = round_to_dp(volt, 2);
  if (volt < 1.65) {
    ntu = 3000;
  } else {
    ntu = -1120.4 * sq(volt) + 5742.3 * volt - 4353.8;
  }
  
  Serial.print (volt);
  Serial.println ("V");
  Serial.print (ntu);
  Serial.println ("NTU");
  return ntu;
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
