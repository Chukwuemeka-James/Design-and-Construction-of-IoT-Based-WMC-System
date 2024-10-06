#define BLYNK_TEMPLATE_ID "TMPL2xf0eyi3_"
#define BLYNK_TEMPLATE_NAME "Water level monitoring"
#define BLYNK_AUTH_TOKEN "biqObD4nbFW2E2M613znJrN9VXhrGRPl"
#define BLYNK_PRINT Serial

// Your WiFi credentials.
char ssid[] = "Infinix HOT 12";
char pass[] = "38391628Wi";

// Set Water Level Distance in CM
int emptyTankDistance = 14;  // Distance when tank is empty
int fullTankDistance = 4;    // Distance when tank is full
int emptyTankDistance2 = 14; // Distance when tank is empty (second sensor)
int fullTankDistance2 = 4;   // Distance when tank is full (second sensor)

// Set trigger value in percentage
int triggerPer = 10; // Alarm will start when water level drops below triggerPer

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0X27, 20, 4);

// Define connections to sensor
#define TRIGPIN 26    // D27
#define ECHOPIN 25    // D26
#define TRIGPIN2 5    // D5
#define ECHOPIN2 18   // D18
#define BuzzerPin 13  // D13
#define OHTRelayPin 4 // D4
#define RTRelayPin 2  // D2

float duration1;
float duration2;
float distance1;
float distance2;
float waterlevel1;
float waterlevel2;
int temp = 0;
bool toggleBuzzer = HIGH;
char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

void checkBlynkStatus() { // called every 3 seconds by SimpleTimer
  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    Serial.println("Blynk Not Connected");
  }
  if (isconnected == true) {
    Serial.println("Blynk Connected");
  }
}

void Measurement2() {
  if ((distance2 > 16) && (distance1 > 16)) {
    digitalWrite(RTRelayPin, HIGH);
    lcd.setCursor(13, 3);
    lcd.print(" OFF ");
  } else {
    digitalWrite(RTRelayPin, LOW);
  }
}

void measureDistance() {
  // Set the trigger pin LOW for 2us
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  // Set the trigger pin HIGH for 20us to send pulse
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(20);
  // Return the trigger pin to LOW
  digitalWrite(TRIGPIN, LOW);
  // Measure the width of the incoming pulse
  duration1 = pulseIn(ECHOPIN, HIGH);

  // Determine distance from duration
  distance1 = ((duration1 / 2) * 0.343) / 10;

  // Measurement for second sensor
  digitalWrite(TRIGPIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIGPIN2, LOW);
  duration2 = pulseIn(ECHOPIN2, HIGH);
  distance2 = ((duration2 / 2) * 0.343) / 10;

  waterlevel1 = (21.33 - distance1);
  waterlevel2 = (22.30 - distance2);

  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.println("cm");
  Serial.print("Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.print(waterlevel1);

  Blynk.virtualWrite(V0, waterlevel1);
  Blynk.virtualWrite(V1, distance1);
  Blynk.virtualWrite(V2, waterlevel2);
  Blynk.virtualWrite(V3, distance2);

  lcd.setCursor(0, 0);
  lcd.print("IOT WATER LEVEL MONITOR");
  lcd.setCursor(0, 1);
  lcd.print("OHTW LEVEL:");
  lcd.setCursor(12, 1);
  lcd.print(waterlevel1);
  lcd.print("cm");
  lcd.setCursor(0, 2);
  lcd.print("UGW LEVEL:");
  lcd.setCursor(11, 2);
  lcd.print(waterlevel2);
  lcd.print("cm");
  lcd.setCursor(0, 3);
  lcd.print("PUMP STATUS:");

  if (distance1 < 4 && temp == 0) {
    digitalWrite(OHTRelayPin, LOW);
    digitalWrite(BuzzerPin, HIGH);
    delay(500);
    digitalWrite(BuzzerPin, LOW);
    lcd.setCursor(13, 3);
    lcd.print("OFF");
    temp = 1;
  } else if (distance1 < 4 && temp == 1) {
    digitalWrite(OHTRelayPin, LOW);
    lcd.setCursor(13, 3);
    lcd.print("OFF");
  } else if (distance1 >= 14) {
    digitalWrite(OHTRelayPin, HIGH);
    digitalWrite(BuzzerPin, HIGH);
    delay(3000);
    digitalWrite(BuzzerPin, LOW);
    lcd.setCursor(13, 3);
    lcd.print(" ON ");
    temp = 0;
  }
}

void setup() {
  // Set up serial monitor
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);

  pinMode(TRIGPIN, OUTPUT);
  pinMode(TRIGPIN2, OUTPUT);
  pinMode(OHTRelayPin, OUTPUT);
  pinMode(RTRelayPin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(ECHOPIN2, INPUT);
  digitalWrite(BuzzerPin, LOW);

  WiFi.begin(ssid, pass);
  timer.setInterval(1000L, checkBlynkStatus); // check if Blynk server is connected every 1 second
  Blynk.config(auth);
  delay(1000);
}

void loop() {
  Measurement2();
  measureDistance();
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
