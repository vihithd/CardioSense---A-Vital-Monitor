#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30105.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// -------- I2C PINS --------
#define SDA_PIN 6
#define SCL_PIN 7

// -------- OLED --------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- MAX --------
MAX30105 particleSensor;

// -------- DS18B20 --------
#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

// -------- MPU --------
int16_t ax, ay, az;

void setup() {

  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("=== DIAGNOSTIC START ===");

  // OLED
  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("OLED: OK");
  } else {
    Serial.println("OLED: NOT FOUND");
  }

  // MAX30102
  if(particleSensor.begin(Wire)){
    Serial.println("MAX30102: OK");
    particleSensor.setup();
  } else {
    Serial.println("MAX30102: NOT FOUND");
  }

  // MPU
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  if(Wire.endTransmission()==0){
    Serial.println("MPU6050/6500: OK");
  } else {
    Serial.println("MPU: NOT FOUND");
  }

  // Temperature
  tempSensor.begin();
  Serial.println("DS18B20: Initialized");

  delay(1000);
}

void loop() {

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);

  // -------- I2C Scan --------
  Serial.println("\nScanning I2C...");
  for(byte address=1; address<127; address++){
    Wire.beginTransmission(address);
    if(Wire.endTransmission()==0){
      Serial.print("Found device at 0x");
      Serial.println(address, HEX);
    }
  }

  // -------- MPU --------
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,6);

  ax = Wire.read()<<8 | Wire.read();
  ay = Wire.read()<<8 | Wire.read();
  az = Wire.read()<<8 | Wire.read();

  float mag = sqrt(ax*ax + ay*ay + az*az);

  Serial.print("MPU Mag: ");
  Serial.println(mag);

  // -------- MAX --------
  long ir = particleSensor.getIR();
  long red = particleSensor.getRed();

  Serial.print("IR: ");
  Serial.print(ir);
  Serial.print(" RED: ");
  Serial.println(red);

  // -------- Temperature --------
  tempSensor.requestTemperatures();
  float tempC = tempSensor.getTempCByIndex(0);

  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.println(" C");

  // -------- OLED DISPLAY --------
  display.println("Diagnostic Mode");
  display.print("IR: "); display.println(ir);
  display.print("Temp: "); display.println(tempC);
  display.print("Motion: "); display.println(mag);
  display.display();

  delay(2000);
}
