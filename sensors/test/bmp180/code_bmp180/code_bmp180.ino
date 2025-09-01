#include <Wire.h>
#include <Adafruit_BMP085.h>  // BMP180 uses this library

// Create BMP180 object
Adafruit_BMP085 bmp;

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
  delay(1000);
  Serial.println("Initializing BMP180...");

  // Initialize I2C with custom pins (SDA=21, SCL=22)
  Wire.begin(21, 22);

  // Initialize BMP180
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("BMP180 initialized successfully!");
}

void loop() {
  // Read temperature
  float temperature = bmp.readTemperature();
  
  // Read pressure (in Pa)
  int32_t pressure = bmp.readPressure();

  // Calculate altitude (using standard sea-level pressure 101325 Pa)
  float altitude = bmp.readAltitude();

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" Pa");

  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  Serial.println("--------------------------");

  delay(2000); // Update every 2 seconds
}
