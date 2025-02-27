# Security Door Arduino Project

A secure door lock system using Arduino, implementing both password and fingerprint authentication mechanisms.

## Components Used
- Arduino Board
- Fingerprint Sensor
- LCD Display (I2C)
- 4x4 Matrix Keypad
- Servo Motor
- Jumper Wires

## Features
- Dual authentication system (Password + Fingerprint)
- 16x2 LCD display for user interface
- Servo motor for door lock mechanism
- Reset functionality
- Error handling for sensor issues

## Libraries Required
- Servo.h
- Keypad.h
- Wire.h
- LiquidCrystal_I2C.h
- SoftwareSerial.h
- Adafruit_Fingerprint.h

## Setup Instructions
1. Connect all components according to the pin configuration in the code
2. Install required libraries through Arduino IDE
3. Upload the code to your Arduino board
4. Power up the system

## Usage
1. Enter the 4-digit password using the keypad
2. Press '#' to confirm password
3. If password is correct, scan your fingerprint
4. Door will unlock upon successful authentication
5. Press '*' to reset the system

## Author
Nooraddin Ismail
