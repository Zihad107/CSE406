# UART Communication Stress Test with NodeMCU ESP8266

This project evaluates the performance of UART (Universal Asynchronous Receiver-Transmitter) communication between two NodeMCU ESP8266 boards using the `SoftwareSerial` library. It measures throughput, transfer speed, and error rate under different configurations to identify optimal conditions for reliable communication.

---

## 📚 Project Details

- **Course**: Internet of Things (CSE 406)
- **Section**: 01  
- **Submitted by**: Zihad Khan ([ID: 2022-2-60-107](https://github.com/Zihad107))
- **Group Members**:
  - Shairin Akter Hashi ([ID: 2022-2-60-102](https://github.com/Shairin207))
  - Nushrat Jaben Aurnima ([ID: 2022-2-60-146](https://github.com/NushratJabenAurnima))
  - Md Shahrukh Hossain Shihab ([ID: 2022-1-60-372](https://github.com/shihab372))
- **Instructor**: Dr. Raihan Ul Islam (DRUI)
- **Date**: 13 July 2025

---

## 🧪 Objective

Perform a **stress test** on UART communication between two ESP8266 NodeMCUs using varying:

- Baud rates: `9600`, `38400`, `115200`
- Message sizes: `10`, `50`, `100` bytes
- Transfer intervals: `0ms`, `10ms`, `100ms`

---

## 🔌 Hardware Setup

- **Boards**: 2 × NodeMCU ESP8266  
- **Wiring**:
  - NodeMCU 1 `D5 (TX)` → NodeMCU 2 `D6 (RX)`
  - NodeMCU 2 `D5 (TX)` → NodeMCU 1 `D6 (RX)`
  - Both GND pins connected via breadboard

📸 *Hardware Setup Image:*  
![Hardware Setup](https://github.com/Zihad107/CSE406/blob/master/Lab-03(UART)/Hardware_setup.jpg)

---

## 🛠️ Software Configuration

- **Platform**: [Arduino IDE](https://www.arduino.cc/en/software)
- **Board Package**: ESP8266 v3.1.2  
- **Monitoring Tool**: [CoolTerm](https://freeware.the-meiers.org/)
- **Sketches**:
  - [`Master_Final.ino`](https://github.com/Zihad107/CSE406/blob/master/Lab-03(UART)/Master_Final.ino) – controls transmission (NodeMCU 1)
  - [`Slave.ino`](https://github.com/Zihad107/CSE406/blob/master/Lab-03(UART)/Slave.ino) – listens and echoes back (NodeMCU 2)

---

## 📊 Results Summary

| Baud Rate | Message Size | Interval | Throughput (bytes/s) | Message Rate (msg/s) | Error Rate |
|-----------|---------------|----------|-----------------------|-----------------------|------------|
| 9600      | 50 bytes      | 10 ms    | 440                   | 9                     | 0.00%      |
| 38400     | 10 bytes      | 0 ms     | 17                    | 2                     | 100.00%    |
| 115200    | 10 bytes      | 0 ms     | 17                    | 2                     | 100.00%    |

✅ **Best config:** 9600 baud, 50 bytes, 10 ms interval  
❌ **Worst:** 38400 & 115200 due to 100% error rate

---

## 🔍 Key Observations

- High baud rates = unstable communication with `SoftwareSerial`.
- Larger messages = higher throughput but slower rate.
- ESP8266 software UART fails above 9600 baud due to timing/buffering limits.

---

## 📁 Repository Contents

| File | Description |
|------|-------------|
| [`Master_Final.ino`](https://github.com/Zihad107/CSE406/blob/master/Lab-03(UART)/Master_Final.ino) | Code for transmitter (NodeMCU 1) |
| [`Slave.ino`](https://github.com/Zihad107/CSE406/blob/master/Lab-03(UART)/Slave.ino) | Code for receiver (NodeMCU 2) |
| [`nodemcu1_output.txt`](https://github.com/Zihad107/CSE406/blob/master/Lab-03(UART)/nodemcu1_output.txt) | Output log from Master |
| [`nodemcu2_output.txt`](https://github.com/Zihad107/CSE406/blob/master/Lab-03(UART)/nodemcu2_output.txt) | Output log from Slave |
| [`Zihad_Khan_UART_Lab_Report.pdf`](https://github.com/Zihad107/CSE406/blob/master/Lab-03(UART)/Zihad_Khan_UART_Lab_Report.pdf) | Full lab report PDF |

---

## 📖 References

- 📘 [ESP8266 Technical Reference Manual (Espressif)](https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf)  
- 💬 [Arduino Forum – Serial Monitor & ESP8266](https://forum.arduino.cc/t/serial-monitor-and-esp8266/480428/6)

---

## 📬 Contact

For any questions, reach out to **Zihad Khan (2022-2-60-107)** or any of the group members listed above.

---  
