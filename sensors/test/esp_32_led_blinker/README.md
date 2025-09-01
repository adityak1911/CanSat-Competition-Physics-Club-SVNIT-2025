# ESP32 Debug Test – LED Blinker

This project demonstrates how to **debug and test** an ESP32 board by blinking an LED.  
The LED is connected to **GPIO2 (D2)**, which is available on most ESP32 development boards.

---

## 🛠 Pin Connections

| ESP32 Pin | LED Pin |
|-----------|---------|
| GPIO2 (D2)| Anode (+)|
| GND       | Cathode (-) through 220Ω resistor |

📷 Example LED connection:  
![ESP32 LED Test](https://content.arduino.cc/assets/Arduino-UNO_Blink.jpg)

---

## 🚦 How it Works

- The code sets **GPIO2 (D2)** as an output pin.  
- The LED turns **ON** for 1 second and **OFF** for 1 second in a loop.  
- This confirms that the ESP32 board is **working correctly** and that the Arduino IDE upload process is functional.

---

## 🚀 Upload Code

1. Connect your ESP32 to the computer  
2. Open Arduino IDE  
3. Copy the code from `esp32_blink_test.ino`  
4. Select **Board: ESP32 Dev Module** and the correct **COM port**  
5. Upload the sketch  
6. The LED connected to **GPIO2** should start blinking  

---

## 📊 Example Output

ESP32 Blink Test
LED ON
LED OFF
LED ON
LED OFF
...


---

## ⚠️ Notes

- Some ESP32 boards already have a **built-in LED** on **GPIO2**. If so, you don’t need an external LED.  
- If your board’s onboard LED is mapped to another pin (e.g., GPIO 13 or GPIO 25), update the `LED_PIN` in the code.  
