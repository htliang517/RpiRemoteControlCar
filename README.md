# Raspberry Pi Remote Control Car

This is a simple project based on Arduino and Raspberry Pi.

The goal of this project is to build a remote control car that is able to control with smartphone.


## Hardware

##### 1.Raspberry Pi

- Connected with a webcam.
- Running a local server with Flask as the control panel of the car.
- Sending signals to Arduino for motor control with serial port.

##### 2.Arduino Uno

- Served as the motor controller.
- Recieving signals from raspberry pi to adjust motor speed.

##### 3. L298n

- H-bridge (Used for pwm control.)


## Requirements

Python 3 with the following packages:

- Flask
- pyserial
