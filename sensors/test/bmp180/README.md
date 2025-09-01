# ESP32 with BMP180 Sensor

This project demonstrates how to interface a **BMP180 barometric pressure and temperature sensor** with an **ESP32** using I²C communication.  
The code reads **temperature, pressure, and altitude** and prints the values to the Serial Monitor.

---

## 🛠 Pin Connections

| BMP180 Pin | ESP32 Pin |
|------------|-----------|
| VIN        | 3V3       |
| GND        | GND       |
| SCL        | GPIO22    |
| SDA        | GPIO21    |

📷 Sensor Module (BMP180):  
![BMP180 Sensor](A_digital_instructional_guide_features_a_BMP180_ba.png)

---

## 📦 Library Installation

The BMP180 is supported by the **Adafruit BMP085 Unified Library**.  
To install it in the **Arduino IDE**:

1. Open **Arduino IDE**  
2. Go to **Sketch → Include Library → Manage Libraries**  
3. In the Library Manager, search for **Adafruit BMP085 Unified**  
4. Install it (this library supports **BMP180** as well)  
5. Also make sure the **Adafruit Unified Sensor** library is installed (dependency)

---

## 🚀 Upload Code

1. Connect your ESP32 to the computer  
2. Open the Arduino IDE and paste the code from `bmp180_test.ino`  
3. Select **Board: ESP32 Dev Module** and the correct **COM port**  
4. Upload the code  
5. Open the **Serial Monitor** at `115200 baud` to see live sensor readings  

---

## 📊 Example Output

Initializing BMP180...
BMP180 initialized successfully!
Temperature = 28.4 *C
Pressure = 100912 Pa
Altitude = 98.6 m


---

## ⚠️ Notes

- The BMP180 works with **3.3V or 5V** depending on your breakout board. For ESP32, connect to **3V3**.  
- Always connect **GND → GND**.  
- Ensure **SCL = GPIO22** and **SDA = GPIO21** (default ESP32 I²C pins).  