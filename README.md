# IR Counter - Get Count Digitally

A simple yet effective object counter using **ESP32** and **IR Obstacle Avoidance Sensor**, with a visually rich OLED animation and real-time counting. This project is designed to be beginner-friendly, modular, and open to reuse across multiple embedded setups.

## 🚀 Features

* 📟 Real-time object counting using IR sensor (active-low output)
* 📊 Dynamic font-based count rendering on OLED (auto-adjusts with digit length)
* 🎞️ Boot-time animated GIF display on SH1106 OLED
* 🖱️ Manual reset functionality via push-button
* 👨‍💻 Modular design with reusable `Button.h`, `OLED_Print.h`, and animation headers
* 🔁 Debounced IR input and reset logic for accurate counting

## 🔌 Components Used

| Component                    | Description                   |
| ---------------------------- | ----------------------------- |
| ESP32 DevKit V1              | Microcontroller board         |
| IR Obstacle Avoidance Sensor | Active-low digital output     |
| SH1106 OLED 128x64           | Display for animation + count |
| Mini Push Button (Momentary) | For reset functionality       |


## 📂 VScode Folder Structure

```
IR Counter/
├── .pio/                  # PlatformIO build system
├── include/               # Header files
├── lib/                   # Custom libraries (if extended)
├── src/                   # Main source code
│   ├── main.cpp
│   ├── Button.cpp
|   |── Button.h
│   ├── car_frames.cpp
|   ├── car_frames.h
|   ├── u8g2_oledPrint.cpp
│   └── u8g2_oledPrint.h
├── test 
├── platformio.ini         # Project configuration
└── .gitignore

## ⚙️ PlatformIO Configuration

[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
monitor_speed = 115200
upload_port = COM3
monitor_port = COM3
lib_deps =
	olikraus/U8g2 @ ^2.36.5

## 🔁 How It Works

1. On boot, an animated counter GIF is shown using frame-by-frame rendering.
2. The welcome sequence is displayed, followed by the main count display.
3. Each time the IR sensor detects an object passing in front of it, the counter increments.
4. A push-button can be pressed to reset the counter to zero.
5. Display dynamically adjusts font size based on digit length.

## 🧠 Concepts Used

* 🧱 **Object-Oriented Programming (OOP)**

  * Reusable `Button` class
  * Modular print functions via `u8g2_oledPrint`
* 🖼 **Frame-Based Animation** using `counter_Frame.h`
* 🛠️ **Interrupt Handling** for sensor accuracy (`IRAM_ATTR` based counting)
* 🧠 **Debouncing Logic** for both button and sensor

## 📷 Circuit Diagram

[Schematic_IR-Counter_2025-06-23.pdf](https://github.com/user-attachments/files/20862251/Schematic_IR-Counter_2025-06-23.pdf)

## 📝 License

This project is licensed under the **Custom License**:

* Attribution required
* No commercial use without permission
* No modification or redistribution allowed
* Provided "as-is" without warranty

> 🔐 LICENSE file is included in the repository.

## 🙋‍♂️ About the Author

Developed with ❤️ by **Abhishek Kumar Vishwakarma**
I believe in making **embedded projects reusable and beginner-friendly**. Feel free to explore my other works like **Fire Thermomist**, **Ultragauge**, and more.

📬 *For queries, collaborations, or access permissions, reach out via LinkedIn or GitHub.*
