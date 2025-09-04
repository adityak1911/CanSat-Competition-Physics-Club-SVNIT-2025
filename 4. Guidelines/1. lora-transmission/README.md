# 📡 LoRa Transmission Guidelines – Physics Club CanSat Competition

This document defines the **data transmission format** to be used by all teams in the Physics Club **CanSat Competition**.
Standardized formatting ensures that every ground station can reliably decode telemetry packets.

---

## 🔑 General Rules

* All data must be transmitted as a **single string**.
* Each parameter is separated by a **semicolon `;`**.
* Each packet must begin with the **team identifier** and include a **timestamp**.
* Values must be formatted with the specified precision.

---

## 📝 Transmission Format

```
CAN-Team-XX; Ti-HH:MM:SS:MS; A-XXX.X; Pr-XXXX.XX; T-XX.X; Ro-XX.X; Pi-XX.X; Ya-XX.X; AX-XX.XX; AY-XX.XX; AZ-XX.XX;
```

---

## 📊 Field Descriptions

| Field                 | Description                                   | Units   | Precision  |
| --------------------- | --------------------------------------------- | ------- | ---------- |
| **CAN-Team-XX**       | Unique team identifier (e.g., CAN-Team-01)    | –       | –          |
| **Ti-HH\:MM\:SS\:MS** | Timestamp (Hour\:Minute\:Second\:Millisecond) | –       | –          |
| **A**                 | Altitude                                      | metres  | 1 decimal  |
| **Pr**                | Pressure                                      | Pa      | 2 decimals |
| **T**                 | Temperature                                   | °C      | 1 decimal  |
| **Ro**                | Roll                                          | degrees | 1 decimal  |
| **Pi**                | Pitch                                         | degrees | 1 decimal  |
| **Ya**                | Yaw                                           | degrees | 1 decimal  |
| **AX**                | Acceleration X                                | m/s²    | 2 decimals |
| **AY**                | Acceleration Y                                | m/s²    | 2 decimals |
| **AZ**                | Acceleration Z                                | m/s²    | 2 decimals |

---

## ✅ Example Transmission

```
CAN-Team-01; Ti-17:03:01:451; A-78.5; Pr-1008.23; T-28.2; Ro-4.1; Pi-45.3; Ya-50.7; AX-4.12; AY-5.09; AZ-8.33;
```

---

## ⚠️ Notes

* **Semicolon `;` is mandatory** between fields.
* Ensure **units and precision** are followed exactly.
* Extra spaces should be avoided except after semicolons.
* Teams must **not change identifiers** (A, Pr, T, Ro, Pi, Ya, AX, AY, AZ).
* Ground stations will parse packets based on this exact format.

---

## 🏆 Competition Requirement

All participating teams **must implement this format** in their LoRa transmissions. Any deviation may lead to data rejection during judging.

---
