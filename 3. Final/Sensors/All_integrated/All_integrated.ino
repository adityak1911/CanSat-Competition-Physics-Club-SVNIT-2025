#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define SDA_PIN 21
#define SCL_PIN 22

// LoRa pins 
#define ss 5
#define rst 14
#define dio0 2
// Packet transmission number
unsigned long packets_transmitted=0;

// Create BMP085 object for BMP180 sensor, and global variables for BMP180
Adafruit_BMP085 bmp;
float initialAltitude = 0;
float absinitialAltitude = 0;
bool initialAltitudeSet = false;

// MPU6050 object
Adafruit_MPU6050 mpu;

// Kalman Filter Structure
struct KalmanFilter {
  float Q_angle;    // Process noise variance for the accelerometer
  float Q_bias;     // Process noise variance for the gyro bias
  float R_measure;  // Measurement noise variance
  
  float angle;      // The angle calculated by the Kalman filter
  float bias;       // The gyro bias calculated by the Kalman filter
  float rate;       // Unbiased rate calculated from the rate and the calculated bias
  
  float P[2][2];    // Error covariance matrix
};

// Kalman filters for roll and pitch
KalmanFilter kalmanX, kalmanY;

// Time tracking
unsigned long previousTime = 0;
float dt = 0;

// Sensor data
sensors_event_t accel, gyro, temp;

// Angle variables
float roll = 0, pitch = 0, yaw = 0;

// Velocity and position variables
float velX = 0, velY = 0, velZ = 0;
float posX = 0, posY = 0, posZ = 0;

// Acceleration in world frame
float accelWorldX = 0, accelWorldY = 0, accelWorldZ = 0;

// Gravity constant
const float GRAVITY = 9.81;

// Low-pass filter coefficients for acceleration
const float ACCEL_FILTER_ALPHA = 0.2;
float filteredAccelX = 0, filteredAccelY = 0, filteredAccelZ = 0;

// Stationary detection variables
const float STATIONARY_THRESHOLD = 0.2; // m/s^2
const int STATIONARY_SAMPLES = 10;
int stationaryCount = 0;
bool isStationary = false;

// Sensor bias calibration
float gyroBiasX = 0, gyroBiasY = 0, gyroBiasZ = 0;
float accelBiasX = 0, accelBiasY = 0, accelBiasZ = 0;

// Complementary filter for yaw (if magnetometer was available)
// float yawComp = 0;
// const float COMPLEMENTARY_ALPHA = 0.98;

// Initialize Kalman filter
void initKalman(KalmanFilter* kalman) {
  kalman->Q_angle = 0.001f;
  kalman->Q_bias = 0.003f;
  kalman->R_measure = 0.03f;
  
  kalman->angle = 0.0f;
  kalman->bias = 0.0f;
  
  kalman->P[0][0] = 0.0f;
  kalman->P[0][1] = 0.0f;
  kalman->P[1][0] = 0.0f;
  kalman->P[1][1] = 0.0f;
}

// Kalman filter update function
float kalmanUpdate(KalmanFilter* kalman, float newAngle, float newRate, float dt) {
  // Step 1: Predict
  kalman->rate = newRate - kalman->bias;
  kalman->angle += dt * kalman->rate;
  
  // Update estimation error covariance
  kalman->P[0][0] += dt * (dt * kalman->P[1][1] - kalman->P[0][1] - kalman->P[1][0] + kalman->Q_angle);
  kalman->P[0][1] -= dt * kalman->P[1][1];
  kalman->P[1][0] -= dt * kalman->P[1][1];
  kalman->P[1][1] += kalman->Q_bias * dt;
  
  // Step 2: Update
  float S = kalman->P[0][0] + kalman->R_measure;
  float K[2];
  K[0] = kalman->P[0][0] / S;
  K[1] = kalman->P[1][0] / S;
  
  float y = newAngle - kalman->angle;
  kalman->angle += K[0] * y;
  kalman->bias += K[1] * y;
  
  float P00_temp = kalman->P[0][0];
  float P01_temp = kalman->P[0][1];
  
  kalman->P[0][0] -= K[0] * P00_temp;
  kalman->P[0][1] -= K[0] * P01_temp;
  kalman->P[1][0] -= K[1] * P00_temp;
  kalman->P[1][1] -= K[1] * P01_temp;
  
  return kalman->angle;
}

// Calibrate sensors
void calibrateSensors() {
  Serial.println("Calibrating sensors... Keep the device stationary on a flat surface.");
  delay(1000);
  
  const int numSamples = 500;
  float gx = 0, gy = 0, gz = 0;
  float ax = 0, ay = 0, az = 0;
  
  for (int i = 0; i < numSamples; i++) {
    mpu.getEvent(&accel, &gyro, &temp);
    
    gx += gyro.gyro.x;
    gy += gyro.gyro.y;
    gz += gyro.gyro.z;
    
    ax += accel.acceleration.x;
    ay += accel.acceleration.y;
    az += accel.acceleration.z - GRAVITY; // Remove gravity
    
    delay(5);
  }
  
  gyroBiasX = gx / numSamples;
  gyroBiasY = gy / numSamples;
  gyroBiasZ = gz / numSamples;
  
  accelBiasX = ax / numSamples;
  accelBiasY = ay / numSamples;
  accelBiasZ = az / numSamples;
  
  Serial.println("Calibration complete:");
  Serial.print("Gyro bias - X: "); Serial.print(gyroBiasX, 6);
  Serial.print(", Y: "); Serial.print(gyroBiasY, 6);
  Serial.print(", Z: "); Serial.println(gyroBiasZ, 6);
  
  Serial.print("Accel bias - X: "); Serial.print(accelBiasX, 6);
  Serial.print(", Y: "); Serial.print(accelBiasY, 6);
  Serial.print(", Z: "); Serial.println(accelBiasZ, 6);
}

// Check if device is stationary
bool checkStationary(float accelX, float accelY, float accelZ, float gyroX, float gyroY, float gyroZ) {
  // Calculate magnitude of acceleration (excluding gravity)
  float accelMagnitude = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);
  
  // Calculate magnitude of angular velocity
  float gyroMagnitude = sqrt(gyroX * gyroX + gyroY * gyroY + gyroZ * gyroZ);
  
  // Check if both are below thresholds
  if (accelMagnitude < STATIONARY_THRESHOLD && gyroMagnitude < 0.5) {
    stationaryCount++;
  } else {
    stationaryCount = 0;
  }
  
  // Require multiple consecutive stationary samples
  return stationaryCount >= STATIONARY_SAMPLES;
}

// Set your local sea-level pressure in hPa
#define SEA_LEVEL_PRESSURE 100810.0

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Wire.begin(SDA_PIN, SCL_PIN); // single I2C bus for both sensors

  Serial.println("Initializing BMP180...");
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor!");
    while (1);
  }

  Serial.println("BMP180 Initialized!");

  Serial.println("Initializing MPU6050...");

  
  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  
  // Configure MPU6050 settings
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  // Calibrate sensors
  calibrateSensors();
  
  // Initialize Kalman filters
  initKalman(&kalmanX);
  initKalman(&kalmanY);
  
  // Get initial angles from accelerometer
  mpu.getEvent(&accel, &gyro, &temp);
  float initialRoll = atan2(accel.acceleration.y, accel.acceleration.z) * 180.0 / PI;
  float initialPitch = atan(-accel.acceleration.x / sqrt(accel.acceleration.y * accel.acceleration.y + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;
  
  // Set initial angles
  kalmanX.angle = initialRoll;
  kalmanY.angle = initialPitch;
  roll = initialRoll;
  pitch = initialPitch;
  
  previousTime = millis();

  // === LoRa ===

  Serial.println("Initializing LoRa...");
  LoRa.setPins(ss, rst, dio0);

  // Start LoRa at 433 MHz
  while (!LoRa.begin(433E6)) {
    Serial.print(".");
    delay(500);
  }

  LoRa.setSyncWord(0xA5);
  Serial.println("\nLoRa Initialization OK!");
}

void loop() {
  // === Read data from BMP180 ===
  long sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += bmp.readPressure();
    delay(20);
  }
  float pressurePa = sum / 5.0;
  float pressure = pressurePa / 100.0;  // in hPa

  // Read absolute altitude from BMP180
  // Read absolute altitude from BMP180
float readingAltitude = bmp.readAltitude(SEA_LEVEL_PRESSURE); // in meters

// Initialize base altitude at startup
if (!initialAltitudeSet) {
    initialAltitude = readingAltitude; // store actual altitude as reference
    initialAltitudeSet = true;
    
  Serial.print("initialAltitude: ");

  absinitialAltitude = abs(initialAltitude);

  Serial.print(absinitialAltitude);
}

// Altitude relative to start (first reading = 0)
float altitude = readingAltitude - initialAltitude + absinitialAltitude;



  float temperature = bmp.readTemperature(); // in °C

  // === Data from MPU 6050 ===
  unsigned long currentTime = millis();
  dt = (currentTime - previousTime) / 1000.0; // Convert to seconds
  
  if (dt < 0.001) return; // Skip if dt is too small
  
  previousTime = currentTime;
  
  // Read sensor data
  mpu.getEvent(&accel, &gyro, &temp);
  
  // Apply calibration offsets
  float calibratedGyroX = gyro.gyro.x - gyroBiasX;
  float calibratedGyroY = gyro.gyro.y - gyroBiasY;
  float calibratedGyroZ = gyro.gyro.z - gyroBiasZ;
  
  float calibratedAccelX = accel.acceleration.x - accelBiasX;
  float calibratedAccelY = accel.acceleration.y - accelBiasY;
  float calibratedAccelZ = accel.acceleration.z - accelBiasZ;
  
  // Convert gyroscope data from rad/s to deg/s
  float gyroX = calibratedGyroX * 180.0 / PI;
  float gyroY = calibratedGyroY * 180.0 / PI;
  float gyroZ = calibratedGyroZ * 180.0 / PI;
  
  // Calculate roll and pitch from accelerometer
  float accelRoll = atan2(calibratedAccelY, calibratedAccelZ) * 180.0 / PI;
  float accelPitch = atan(-calibratedAccelX / sqrt(calibratedAccelY * calibratedAccelY + calibratedAccelZ * calibratedAccelZ)) * 180.0 / PI;
  
  // Update angles using Kalman filter
  roll = kalmanUpdate(&kalmanX, accelRoll, gyroX, dt);
  pitch = kalmanUpdate(&kalmanY, accelPitch, gyroY, dt);
  
  // Simple integration for yaw (since we don't have magnetometer)
  yaw += gyroZ * dt;
  // Normalize yaw to stay within -180 to +180 degrees
  if (yaw > 180) yaw -= 360;
  else if (yaw < -180) yaw += 360;

  
  // Check if device is stationary
  isStationary = checkStationary(calibratedAccelX, calibratedAccelY, calibratedAccelZ, 
                                calibratedGyroX, calibratedGyroY, calibratedGyroZ);
  
  // Convert angles to radians for c180.0;
  float rollRad = roll * PI / 180.0;
  float pitchRad = pitch * PI / 180.0;
  float yawRad = yaw * PI / 180.0;
  
  // Apply low-pass filter to acceleration data
  filteredAccelX = ACCEL_FILTER_ALPHA * calibratedAccelX + (1 - ACCEL_FILTER_ALPHA) * filteredAccelX;
  filteredAccelY = ACCEL_FILTER_ALPHA * calibratedAccelY + (1 - ACCEL_FILTER_ALPHA) * filteredAccelY;
  filteredAccelZ = ACCEL_FILTER_ALPHA * calibratedAccelZ + (1 - ACCEL_FILTER_ALPHA) * filteredAccelZ;
  
  // Transform acceleration from body frame to world frame
  // Remove gravity component and rotate to world coordinates
  float accelBodyX = filteredAccelX;
  float accelBodyY = filteredAccelY;
  float accelBodyZ = filteredAccelZ; // Gravity already removed in calibration
  
  // Rotation matrix transformation
  accelWorldX = accelBodyX * cos(pitchRad) * cos(yawRad) + 
                accelBodyY * (sin(rollRad) * sin(pitchRad) * cos(yawRad) - cos(rollRad) * sin(yawRad)) +
                accelBodyZ * (cos(rollRad) * sin(pitchRad) * cos(yawRad) + sin(rollRad) * sin(yawRad));
                
  accelWorldY = accelBodyX * cos(pitchRad) * sin(yawRad) +
                accelBodyY * (sin(rollRad) * sin(pitchRad) * sin(yawRad) + cos(rollRad) * cos(yawRad)) +
                accelBodyZ * (cos(rollRad) * sin(pitchRad) * sin(yawRad) - sin(rollRad) * cos(yawRad));
                
  accelWorldZ = -accelBodyX * sin(pitchRad) +
                accelBodyY * sin(rollRad) * cos(pitchRad) +
                accelBodyZ * cos(rollRad) * cos(pitchRad);
  
  // Apply threshold to reduce noise (dead zone)
  const float ACCEL_THRESHOLD = 0.1; // m/s^2
  if (abs(accelWorldX) < ACCEL_THRESHOLD) accelWorldX = 0;
  if (abs(accelWorldY) < ACCEL_THRESHOLD) accelWorldY = 0;
  if (abs(accelWorldZ) < ACCEL_THRESHOLD) accelWorldZ = 0;
  
  // If stationary, apply zero-velocity update
  if (isStationary) {
    // Reset velocities
    velX = 0;
    velY = 0;
    velZ = 0;
    
    // Skip integration to prevent drift
  } else {
    // Integrate acceleration to get velocity
    velX += accelWorldX * dt;
    velY += accelWorldY * dt;
    velZ += accelWorldZ * dt;
  }
  
  // Apply velocity decay to reduce drift (less aggressive when stationary detection is active)
  const float VEL_DECAY = isStationary ? 0.9 : 0.98;
  velX *= VEL_DECAY;
  velY *= VEL_DECAY;
  velZ *= VEL_DECAY;
  
  // Integrate velocity to get position
  posX += velX * dt;
  posY += velY * dt;
  posZ += velZ * dt;

  // === Prepare timestamp ===
  unsigned long timestamp = millis();  // in ms since boot

  unsigned long hours = timestamp / 3600000;
  unsigned long minutes = (timestamp % 3600000) / 60000;
  unsigned long seconds = (timestamp % 60000) / 1000;
  unsigned long milliseconds = timestamp % 1000;

  String timeFormatted = String(hours) + ":" +
                        String(minutes) + ":" +
                        String(seconds) + "." +
                        String(milliseconds);

  // === Prepare message ===
  String message = "PK-" + String(packets_transmitted) +
                  "; TI-" + timeFormatted +
                  "; A-" + String(altitude, 2) +
                  "; T-" + String(temperature, 2) +
                  "; P-" + String(pressure, 2) + 
                  "; X-" + String(posX) +
                  "; Y-" + String(posY) +
                  "; Z-" + String(posZ) +
                  "; YX-" + String(roll) +
                  "; YY-" + String(pitch) +
                  "; YZ-" + String(yaw);

  packets_transmitted++;

  // === Send data via LoRa ===
  Serial.print("Sending message: ");
  Serial.println(message);

  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  Serial.println("Message sent!");
  Serial.println("-----------------------------");
}
