# 🛰️ CanSat Competition 2025 – Physics Club SVNIT 🚀

This is the official repository for the **CanSat Design, Build & Launch Competition 2025**, organized by the **Physics Club, SVNIT Surat** as part of **National Space Day 2025**.  

Here you’ll find all the **Arduino/ESP32 code** required to test individual sensors and run the integrated **CanSat system**.

---

## 📂 Repository Structure

```
CanSat-Competition/
│
├── code/                         # All Arduino/ESP32 codes
│   ├── sensors/                  # Individual sensor test codes
│   │   ├── temperature_test.ino  # e.g. BMP280/DHT11/DHT22
│   │   ├── pressure_test.ino     # e.g. BMP280/BMP180
│   │   ├── imu_test.ino          # e.g. MPU6050/MPU9250
│   │   ├── gps_test.ino          # e.g. NEO-6M GPS
│   │   └── communication_test.ino# e.g. LoRa / RF / Bluetooth
│   │
│   └── main/
│       └── cansat_main.ino       # Integrated telemetry + transmission
│
├── hardware/                     # Hardware setup resources
│   ├── wiring_diagrams/          # Circuit connections & pin mappings
│   └── components_list.md        # All parts used (sensors, MCU, comms)
│
├── docs/                         # Documentation & learning
│   ├── workshops.md              # Notes from orientation/workshops
│   ├── competition_rules.md      # Event rules & judging criteria
│   └── troubleshooting.md        # Common issues & fixes
│
├── data/                         # Sample telemetry
│   ├── sample_log.csv            # Example CanSat telemetry log
│   └── visualization.ipynb       # Jupyter notebook for plotting data
│
└── README.md                     # Repo overview & instructions
```

---

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
