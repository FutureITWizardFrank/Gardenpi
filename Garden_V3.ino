#include <DHT.h>

#define DHT_PIN 6  // DHT22 sensor connected to pin 6
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

const int pumpPin = 4;        // Water Pump connected to pin 4
const int soilSensorPin = A0;
const int fanPin = 3;          // 12V Fan connected to pin 3
const int waterMixPin = 5;     // Water Mix connected to pin 5

bool isPumpOn = false;
bool isFanOn = false;
bool isWaterOn = false;

void setup() {
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(waterMixPin, OUTPUT);
  dht.begin();
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    if (command.startsWith("Water")) {
      int duration = command.substring(5).toInt();
      pumpWater(duration);
      Serial.println("Plant Watered!");
    } else if (command.equals("Status")) {
      float temperature = dht.readTemperature(true); // Set to true for Fahrenheit
      float humidity = dht.readHumidity();
      // Read soil moisture level
      int soilMoistureValue = analogRead(soilSensorPin);
      float soilMoisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(" °F");  // Temperature is reported in Fahrenheit
      Serial.println();
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.print("%");
      Serial.println();
      Serial.print("Soil Moisture Level: ");
      Serial.print(soilMoisturePercentage);
      Serial.print(" %");
      Serial.println();
      Serial.print("Fan Status: ");
      if (isFanOn) {
        Serial.println("On");
      } else {
        Serial.println("Off");
      }
      Serial.print("Water Status: ");
      if (isWaterOn) {
        Serial.println("On");
      } else {
        Serial.println("Off");
      }
      Serial.print("Pump Status: ");
      if (isPumpOn) {
        Serial.println("On");
      } else {
        Serial.println("Off");
      }
    } else if (command.equals("Fan On")) {
      isFanOn = true;
      digitalWrite(fanPin, HIGH);
      Serial.println("Fan turned on.");
    } else if (command.equals("Fan Off")) {
      isFanOn = false;
      digitalWrite(fanPin, LOW);
      Serial.println("Fan turned off.");
    } else if (command.equals("Pump On")) {
      isWaterOn = true;
      digitalWrite(waterMixPin, HIGH);
      Serial.println("Pump turned on.");
    } else if (command.equals("Pump Off")) {
      isWaterOn = false;
      digitalWrite(waterMixPin, LOW);
      Serial.println("Pump turned off.");
    } else if (command.equals("Water")) {
      isPumpOn = true;
      digitalWrite(pumpPin, HIGH);
      Serial.println("Watering");
    } else if (command.equals("Water Off")) {
      isPumpOn = false;
      digitalWrite(pumpPin, LOW);
      Serial.println("Water Off");
    } else {
      Serial.println("Invalid command");
    }
  }
}

void pumpWater(int duration) {
  digitalWrite(pumpPin, HIGH);
  delay(duration);
  digitalWrite(pumpPin, LOW);
}
