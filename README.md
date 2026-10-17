# ultrasonic-sensor-code
# 📡 Ultrasonic Radar Tracking System

A 2-part mechatronics engineering project that uses an ultrasonic sensor swept by a servo motor to map surrounding objects, outputting a live radar sweep on a digital interface.

## 🛠️ System Architecture

This project is split into two distinct software layers to separate hardware control from the visual user interface:

* **Hardware Control (`arduino-code`):** Runs directly on an Arduino microcontroller. It controls the servo motor's sweep, fires the ultrasonic sensor pulses, calculates target distances based on sonic echo timings, and transmits the raw data packets over Serial communication.
* **Visual Display Interface (`processing-code`):** Runs on the host PC using the Processing IDE (Java). It listens to the incoming Serial data streams, dynamically draws the radar visual display on screen, and highlights detected targets within the path.

## 📂 Repository Structure

* `📁 arduino-code/` — Contains the C++ microcontroller firmware handling sensor telemetry and servo actuation.
* `📁 processing-code/` — Contains the Java-based UI code used to draw the live graphical display.

## 🚀 Future Enhancements
* Integrating physical feedback alerts (such as a buzzer or warning LEDs) triggered directly by the Processing UI when a target enters a critical proximity zone.


