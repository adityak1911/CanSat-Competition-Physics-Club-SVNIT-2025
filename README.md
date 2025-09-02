# 🛰️ CanSat Competition 2025 – Physics Club SVNIT 🚀

This is the official repository for the **CanSat Design, Build & Launch Competition 2025**, organized by the **Physics Club, SVNIT Surat** as part of **National Space Day 2025**.  

Here you’ll find all the **Arduino/ESP32 code** required to test individual sensors and run the integrated **CanSat system**.

---

## 📂 Repository Structure

CanSat-Competition-Physics-Club-SVNIT-2025/
├── Ground station/
│ └── receiver/
│ └── receiver.ino
├── Sensors/
│ ├── All_integrated/
│ │ └── All_integrated.ino
│ ├── BMP180/
│ ├── MPU6050_6-axis/
│ └── transmitter/
└── README.md

## 🛠️ Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/PhysicsClubSVNIT/CanSat-Competition.git
   ```

2. Open `code/sensors/` in the Arduino IDE and upload individual test codes to verify each module.  
3. Once all sensors are working, open `code/main/cansat_main.ino`.  
4. Upload to your microcontroller (Arduino Nano/Uno or ESP32).  
5. Open **Serial Monitor** or ground station receiver to view live telemetry.  

---

## 🛰️ CanSat System Overview

Your CanSat will:
- Collect **temperature, pressure, altitude, orientation, and GPS data**
- Transmit telemetry via your chosen **communication module**
- Be launched up to **300 ft by a drone**

---

## 📅 Event Timeline

- **29 Aug** – Orientation  
- **1 Sept** – Workshop Session  
- **2–5 Sept** – Mentorship & Guidance  
- **7 Sept** – Final Launch 🚀  

---

## 🏆 Competition Details

- **Prize Pool**: ₹10,000+  
- Certificates for all participants  
- Individual & Team Registrations allowed  

---

## 📞 Contact

- Aditya Kumar: +91 7044635024  
- Abhishek: +91 96932 42982  
- Priyanshu: +91 89051 10384  

---

✨ Built with passion by the **Physics Club Rocketry Team – SVNIT Surat**
