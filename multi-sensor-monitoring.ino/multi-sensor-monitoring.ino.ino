#include <DHT.h>
#include <NewPing.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200

#define SOIL_PIN A0
#define GAS_PIN A1
#define FLAME_PIN 7
#define BUZZER_PIN 8

DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Soil Moisture Reading
  int soilMoisture = analogRead(SOIL_PIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  // DHT22 - Temperature & Humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" C, Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // Gas Sensor Reading
  int gasLevel = analogRead(GAS_PIN);
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  // Flame Detection
  int flame = digitalRead(FLAME_PIN);
  if (flame == LOW) {
    Serial.println("🔥 Flame Detected!");
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Ultrasonic - Human/Intruder Detection
  delay(50); // small delay for sonar to settle
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 50) {
    Serial.println("👤 Human or Object Detected!");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000); // Wait before next cycle
}