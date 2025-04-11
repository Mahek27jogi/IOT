
#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>

RTC_DS3231 rtc;
Servo feederServo;

int tempPin = A0;
int turbidityPin = A1;

int feedHour = 9;
int feedMinute = 0;
bool hasFed = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  feederServo.attach(9);

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  feederServo.write(0);
}

void loop() {
  DateTime now = rtc.now();

  float temperature = readTemperature();
  float turbidity = readTurbidity();

  Serial.print("Time: ");
  Serial.print(now.timestamp());
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Turbidity: ");
  Serial.println(turbidity);

  if (now.hour() == feedHour && now.minute() == feedMinute && !hasFed) {
    feedFish();
    hasFed = true;
  }

  if (now.minute() != feedMinute) {
    hasFed = false;
  }

  delay(1000);
}

void feedFish() {
  Serial.println("Feeding fish...");
  feederServo.write(90);
  delay(2000);
  feederServo.write(0);
}

float readTemperature() {
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float tempC = voltage * 100.0;
  return tempC;
}

float readTurbidity() {
  int sensorValue = analogRead(turbidityPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  return voltage;
}
