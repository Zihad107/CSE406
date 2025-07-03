# 💧 Water Level Monitor

This is a simple yet effective Arduino-based project designed to monitor water levels using a sensor and indicate the status using LEDs. It's perfect for use in overhead tanks, sumps, or any container where keeping an eye on the water level matters. The goal is to help prevent overflow or drying out.

---


## 🤝 Collaboration

This project was built together by a team of four contributors:

- [Nusrat Jaben Aurnima](https://github.com/NushratJabenAurnima)
- [Zihad Khan](https://github.com/Zihad107)
- [Shairin Akter Hashi](https://github.com/Shairin207)
- [MD Shahrukh Hossain Shihab](https://github.com/shihab372)

Thanks to everyone for their hard work and dedication in building this project. 🤗

---


## 🔧 Components You'll Need

To build this project, you’ll need the following components:

| Component              | Quantity   |
|------------------------|------------|
| Arduino Uno            | 1          |
| Water Level Sensor     | 1          |
| Red LED                | 1          |
| Yellow LED             | 1          |
| Green LED              | 1          |
| 220Ω Resistors         | 3          |
| Breadboard             | 1          |
| Wires                  | As needed  |

---

## ⚡ Wiring Guide

Here’s how to connect everything:

| Arduino Pin | Connect To            |
|-------------|------------------------|
| D7          | Sensor Power (VCC)     |
| A0          | Sensor Output Signal   |
| D2          | Red LED (Low Level)    |
| D3          | Yellow LED (Medium)    |
| D4          | Green LED (High Level) |
| GND         | Common Ground          |

---

📸 Actual Project Setup

![Wiring Diagram](https://github.com/Zihad107/CSE406/blob/master/Lab-02(Water%20Level%20Detection)/Real%20Setup.jpg)

## 📊 Understanding the Water Levels

The sensor gives analog values based on how much water is present. These values are divided into ranges:

- **Empty:** Value = 0
- **Low:** 1 to 200
- **Medium:** 201 to 400
- **High:** Above 400

Feel free to adjust these threshold values in the code depending on your sensor’s readings and environment.

---

## 🚦 LED Behavior

Based on the sensor reading, one of the three LEDs will light up to indicate the current water level:

| Level   | LED Status         |
|---------|--------------------|
| Empty   | All LEDs OFF       |
| Low     | Red LED ON         |
| Medium  | Yellow LED ON      |
| High    | Green LED ON       |

---
## 📽️ Demo Video

[Click here to watch the demo video](https://github.com/Zihad107/Water-Level-Monitor/blob/master/Demo%20video.mp4)
## 🧠 How It Works (In Simple Terms)

1. The Arduino powers up the sensor briefly to get a fresh reading.
2. It reads the analog signal coming from the sensor.
3. Based on how high or low the signal is, it turns on the right LED.
4. It also prints the current water level to the Serial Monitor for you to see.

It repeats this process every second.

---

## 💻 Example Serial Output

When you open the Serial Monitor (set at 9600 baud), you’ll see messages like:

```
Water Level: Empty
Water Level: Low
Water Level: Medium
Water Level: High
```
## 👨‍💻 Author

**Zihad Khan**  
🎓 **ID:** 2022-2-60-107  
💻 **Course:** CSE406(Internet of Things)
📅 **Semester:** Summer 2025
