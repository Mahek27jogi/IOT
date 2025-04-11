
#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "FishFeeder"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

Servo feederServo;
int servoPin = D2;
int tempPin = A0;

BLYNK_WRITE(V0) {
  int value = param.asInt();
  if (value == 1) {
    feedFish();
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  feederServo.attach(servoPin);
  feederServo.write(0);
}

void loop() {
  Blynk.run();
}

void feedFish() {
  Serial.println("Feeding fish...");
  feederServo.write(90);
  delay(2000);
  feederServo.write(0);
}
