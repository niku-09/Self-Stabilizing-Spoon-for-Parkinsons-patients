# Self-Stabilizing Spoon for Parkinson's Patients

A real-time tremor-cancelling utensil using a dual-axis servo gimbal controlled by an IMU. Built as a low-cost assistive device for individuals with Parkinson's disease. **Patent pending.**

## How it works

The MPU-6050 IMU continuously reads wrist orientation. A Kalman filter cleans up the noisy accelerometer and gyroscope data, and quaternion-based control computes the corrective angle needed to keep the spoon level. Two servos drive the gimbal in real time to counteract the tremor motion.

## Hardware

- Arduino Nano
- MPU-6050 IMU (I2C)
- 2× micro servo motors (dual-axis gimbal)
- Custom 3D-printed gimbal frame

## Repository contents

```
├── spoon_stabilizer.ino   # Main Arduino sketch
└── README.md
```

## Dependencies

- [MPU6050 library](https://github.com/electroniccats/mpu6050) — Jeff Rowberg
- [Servo.h](https://www.arduino.cc/reference/en/libraries/servo/) — Arduino built-in

## Status

Prototype functional. PCB redesign and TinyML-based tremor classification planned for future iterations.

## More details

Full project write-up and demo: [niku-09.github.io/parkinsons-spoon.html](https://niku-09.github.io/parkinsons-spoon.html)
