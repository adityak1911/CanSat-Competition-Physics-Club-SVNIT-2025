# ESP32 with MPU6050 Sensor

This project demonstrates how to interface a **MPU6050 (Accelerometer + Gyroscope)** sensor with an **ESP32** using I²C communication.  
The code reads **acceleration, gyroscope, and temperature** values and prints them to the Serial Monitor.

---

## 🛠 Pin Connections

| MPU6050 Pin | ESP32 Pin |
|-------------|-----------|
| VCC         | 3V3       |
| GND         | GND       |
| SCL         | GPIO22    |
| SDA         | GPIO21    |

📷 Sensor Module (MPU6050):  
![MPU6050 Sensor](https://cdn.sparkfun.com//assets/parts/1/1/0/7/6/MPU-6050_Breakout_-_InvenSense_IC_-_SEN-11028-01.jpg)

---

## 📦 Library Installation

To use the MPU6050 with ESP32, install the **Adafruit MPU6050** library:  

1. Open **Arduino IDE**  
2. Go to **Sketch → Include Library → Manage Libraries**  
3. In the Library Manager, search for **Adafruit MPU6050**  
4. Install it  
5. Also install the **Adafruit Unified Sensor** library (dependency)  

---

## 🚀 Upload Code

1. Connect your ESP32 to the computer  
2. Open the Arduino IDE and paste the code from `mpu6050_test.ino`  
3. Select **Board: ESP32 Dev Module** and the correct **COM port**  
4. Upload the code  
5. Open the **Serial Monitor** at `115200 baud` to see live sensor readings  

---

## 📊 Example Output

Initializing MPU6050...
MPU6050 Found!

Temperature = 26.5 *C
Acceleration X: -0.02 m/s^2, Y: 0.01 m/s^2, Z: 9.81 m/s^2
Rotation X: 0.03 rad/s, Y: -0.01 rad/s, Z: 0.02 rad/s


---

## ⚠️ Notes

- The **MPU6050 works on 3.3V**, so connect `VCC → 3V3` of ESP32.  
- Always connect **GND → GND**.  
- Ensure **SCL = GPIO22** and **SDA = GPIO21** (default ESP32 I²C pins).  
- If the sensor is not detected, run an **I²C Scanner** sketch to confirm the device address (default: `0x68`).  
