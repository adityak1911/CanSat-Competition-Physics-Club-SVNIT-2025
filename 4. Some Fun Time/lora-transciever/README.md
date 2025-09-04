# ESP32 LoRa Chat System – Sender & Receiver  

This project demonstrates a **two-way chat system** using ESP32 boards with **LoRa transceiver modules**.  
Each device can **send and receive messages** over LoRa, with messages tagged by a **team name** for easy identification.  

---

## 🛠 Pin Connections  

| ESP32 Pin | LoRa Pin |
|-----------|----------|
| GPIO5     | NSS / CS |
| GPIO14    | RESET    |
| GPIO2     | DIO0     |
| 3.3V      | VCC      |
| GND       | GND      |
| GPIO18    | SCK      |
| GPIO23    | MOSI     |
| GPIO19    | MISO     |

📷 Example LoRa wiring (SX1278 / RFM95):  
![LoRa ESP32 Connection](https://lastminuteengineers.com/wp-content/uploads/arduino/ESP32-LoRa-Wiring-Diagram.png)  

---

## 💬 How it Works  

- Each ESP32 acts as **both a transmitter and receiver**.  
- You type a message in the **Serial Monitor**, and it is broadcast over LoRa with your **team name**.  
- Incoming messages are displayed with **RSSI values** (signal strength).  
- Example message format:  


[TeamA]: Hello from my ESP32!
[TeamB]: Hi TeamA, I got your message!


---

## 🚀 Upload Code  

1. Connect your ESP32 + LoRa module to the computer  
2. Open Arduino IDE  
3. Copy the code from `esp32_lora_chat.ino`  
4. Select **Board: ESP32 Dev Module** and the correct **COM port**  
5. Upload the sketch to at least **two ESP32 boards**  
6. Open Serial Monitor (115200 baud) on both boards  
7. Type a message in one window → it appears on the other!  

---

## 📊 Example Output  

**Serial Monitor (TeamA device):**  

📤 Sending: [TeamA]: Hello TeamB
✅ Message sent!
📩 New Message:
[TeamB]: Hi TeamA, message received!
RSSI: -72

---

## ⚙️ Configuration  

- Change the **team name** at the top of the code:  
  ```
  String teamName = "TeamA";   // set your unique team name
  ```
  Frequency is set to 433 MHz by default:

LoRa.begin(433E6);


Use 433E6 (Asia), 866E6 (Europe), or 915E6 (North America).

⚠️ Notes

Both devices must use the same frequency and sync word:
LoRa.setSyncWord(0xA5);

LoRa range depends on environment, antenna quality, and power supply.

Use a proper antenna to avoid damaging the LoRa module.




# LoRa Sync Word – Documentation  

The **sync word** in LoRa communication is an **8-bit identifier** (1 byte) used to separate one network from another.  
Devices with different sync words will **ignore each other’s packets**, even if they share the same frequency and bandwidth.  

---

## 🔢 Format  

- **1 byte value** (8 bits)  
- Represented in **hexadecimal**: `0x00` to `0xFF`  
- Example values:  
  - `0x12`  
  - `0x34`  
  - `0xA5`  
  - `0xFF`  

---

## ⚙️ Common Sync Words  

| Sync Word | Description |
|-----------|-------------|
| `0x34`    | Default **public LoRaWAN** sync word |
| `0x12`    | Often used for **private LoRa networks** |
| `0xA5`    | Example custom sync word (used in many tutorials) |
| `0xFF`    | Sometimes used in test/demo networks |
| `0x00`    | Valid but rarely used (easy to confuse with noise) |

---

## 🛠 Usage in Code  

```cpp
#include <LoRa.h>

// Set sync word before transmitting or receiving
LoRa.setSyncWord(0x34);  // Public LoRaWAN default
// or
LoRa.setSyncWord(0xA5);  // Custom sync word for private network




⚠️ All devices in the same LoRa network must use the same sync word to communicate.

🎯 Example – Team Networks

You can assign different sync words per team to create isolated networks:

Team	Sync Word
Team A	0xA1
Team B	0xB2
Team C	0xC3
Team D	0xD4

This way, devices from Team A won’t hear messages from Team B, even if they share the same frequency.


📡 Notes

Sync word only filters packets at the LoRa physical layer.

Devices must also match on frequency, spreading factor, and bandwidth.

Changing the sync word is an easy way to create separate LoRa chat groups.