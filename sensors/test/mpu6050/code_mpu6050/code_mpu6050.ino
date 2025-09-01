#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Define I2C pins for ESP32
#define SDA_PIN 21
#define SCL_PIN 22

// Create MPU6050 object
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Initializing MPU6050...");

  // Initialize I2C with custom pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // Try to initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("MPU6050 Found!");

  // Configure sensor ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Temperature = ");
  Serial.print(temp.temperature);
  Serial.println(" *C");

  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.println("--------------------------");

  delay(2000); // Update every 2 seconds
}
