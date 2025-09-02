# ESP32 with LoRa (SX1276/78) Receiver

This project demonstrates how to interface a **LoRa module (SX1276/SX1278)** with an **ESP32** using SPI communication.  
The ESP32 will act as a **LoRa receiver**, listening for packets sent by another LoRa transmitter.

---

## 🛠 Pin Connections

| LoRa Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3V3       |
| GND      | GND       |
| NSS (CS) | GPIO5 (D5)|
| MOSI     | GPIO23    |
| MISO     | GPIO19    |
| SCK      | GPIO18    |
| RST      | GPIO14    |
| DIO0     | GPIO2     |

📷 LoRa SX1276/78 Module:  
![LoRa SX1276 Module](https://content.arduino.cc/assets/LoRa_Module.jpg)

---

## 📦 Library Installation

To use the LoRa module with ESP32, install the **LoRa library by Sandeep Mistry**:

1. Open **Arduino IDE**  
2. Go to **Sketch → Include Library → Manage Libraries**  
3. Search for **LoRa**  
4. Install **LoRa by Sandeep Mistry**  

---

## 🚀 Upload Code

1. Connect your ESP32 to the computer  
2. Open the Arduino IDE and paste the code from `lora_rx_test.ino`  
3. Select **Board: ESP32 Dev Module** and the correct **COM port**  
4. Upload the code  
5. Open the **Serial Monitor** at `115200 baud` to see received packets  

---

## 📊 Example Output

LoRa Receiver
Received packet: 'Hello LoRa - packet 0' with RSSI -57
Received packet: 'Hello LoRa - packet 1' with RSSI -59
...



---

## ⚠️ Notes

- Ensure your LoRa module is **3.3V compatible** (SX1276/78 typically is).  
- Attach an **antenna** to the LoRa module for proper operation.  
- Both transmitter and receiver must use the **same frequency** (e.g., 433 MHz, 868 MHz, or 915 MHz depending on your region).  
