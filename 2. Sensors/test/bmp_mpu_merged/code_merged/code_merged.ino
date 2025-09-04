#include <Wire.h>
#include <Adafruit_BMP085.h>   // For BMP180
#include <Adafruit_MPU6050.h>  // For MPU6050
#include <Adafruit_Sensor.h>

// Define I2C pins for ESP32
#define SDA_PIN 21
#define SCL_PIN 22

// Create sensor objects
Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C with custom pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // --- BMP180 Initialization ---
  Serial.println("Initializing BMP180...");
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) delay(1000);
  }
  Serial.println("BMP180 initialized successfully!");

  // --- MPU6050 Initialization ---
  Serial.println("Initializing MPU6050...");
  if (!mpu.begin()) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    while (1) delay(1000);
  }
  Serial.println("MPU6050 initialized successfully!");

  // Configure MPU6050 sensor ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // --- BMP180 Data ---
  float bmpTemp = bmp.readTemperature();
  int32_t pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();

  // --- MPU6050 Data ---
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  // Print BMP180 data
  Serial.println("=== BMP180 (Barometer) ===");
  Serial.print("Temperature: ");
  Serial.print(bmpTemp);
  Serial.println(" °C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  // Print MPU6050 data
  Serial.println("=== MPU6050 (IMU) ===");
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  Serial.print("Acceleration -> X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(accel.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Gyro -> X: ");
  Serial.print(gyro.gyro.x);
  Serial.print(", Y: ");
  Serial.print(gyro.gyro.y);
  Serial.print(", Z: ");
  Serial.print(gyro.gyro.z);
  Serial.println(" rad/s");

  Serial.println("--------------------------\n");

  delay(2000); // Update every 2 seconds
}
