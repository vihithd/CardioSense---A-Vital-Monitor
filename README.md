## CardioSense---A-Vital-Monitor
Wearable embedded health monitoring system for real-time cardiovascular parameter tracking with emergency alert notification system, and IoT-based remote monitoring. 
# Overview
CardioSense is an embedded health monitoring system designed to continuously monitor key cardiovascular parameters and alert users when abnormal trends or sudden changes are detected. The project combines physiological sensing, embedded processing, local visualization, and wireless data transmission to provide real-time health insights.

#  Objectives
- Monitor cardiovascular parameters in real time.
- Display vital signs locally on an OLED display.
- Transmit health data to a web dashboard for remote monitoring.
- Detect abnormal parameter variations and notify the user through alerts.
- Expand the system with ECG monitoring capabilities.

# Hardware Used
- ESP32-C3 Mini (Seeed Studio XIAO)
- MAX30102 Pulse Oximeter and Heart Rate Sensor
- DS18B20 Temperature Sensor
- MPU6050 Motion Sensor
- OLED Display
- Buzzer
- AD8232 ECG Module (currently under integration)

# Current Features
- Heart rate monitoring
- Blood oxygen (SpO₂) monitoring
Heart rate variability (HRV) estimation
Local OLED display of vital signs
Wireless transmission of data to a web dashboard
Emergency buzzer alerts for abnormal readings
