# Installing ESP32 Boards in Arduino IDE (Windows 11 / 64-bit)

After installing the **Arduino IDE** and the necessary USB drivers, you need to install the **ESP32 board package** so the IDE can compile and upload code to your ESP32 board.

---

## Step 1: Open Arduino IDE

1. Launch the **Arduino IDE**.
2. Go to the menu:  
   **File → Preferences**

---

## Step 2: Add ESP32 Board Manager URL

1. In the **Preferences** window, look for the field:  
   **Additional Boards Manager URLs**
2. Copy and paste the following URL into that field:

https://espressif.github.io/arduino-esp32/package_esp32_index.json


3. If you already have another URL there, click the small **icon at the right** and add a new line for the ESP32 URL.

4. Click **OK** to save.

---

## Step 3: Open Boards Manager

1. Go to the menu:  
**Tools → Board → Board Manager**
2. In the search bar, type:  
`esp32`
3. Find **ESP32 by Espressif Systems**.
4. Click **Install** (this may take a few minutes).

---

## Step 4: Select Your ESP32 Board

1. Connect your ESP32 board via USB.
2. Go to:  
**Tools → Board → ESP32 Arduino → [Your Board Model]**  
For most boards: select **ESP32 Dev Module**.
3. Go to:  
**Tools → Port** and choose the COM port detected earlier.

---

## Step 5: Verify Installation

1. Go to **File → Examples → Basics → Blink**.
2. Upload the sketch.
3. If the onboard LED blinks, your ESP32 setup is complete 🎉.

---

## Troubleshooting

- If no COM port is visible:
- Check if CP210x or CH340 drivers are installed (see previous README).
- Try a different USB cable (must support data transfer).
- If upload fails:
- Hold the **BOOT** button on the ESP32 while uploading, release when upload begins.

---

## Summary

1. Add ESP32 URL in **Preferences**  
https://espressif.github.io/arduino-esp32/package_esp32_index.json
2. Open **Boards Manager** → Install **ESP32 by Espressif Systems**.
3. Select your **ESP32 Dev Module** under **Tools → Board**.
4. Select the correct **COM port**.
5. Upload **Blink** to test.

---

✅ You are now ready to start programming your ESP32 in the Arduino IDE.
