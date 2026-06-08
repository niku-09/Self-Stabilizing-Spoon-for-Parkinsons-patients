#include <Wire.h>
#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;

Servo servoX;  // Pitch control (D9)
Servo servoY;  // Roll control  (D10)

Quaternion q;
VectorFloat gravity;
float ypr[3];

uint16_t packetSize;
uint8_t fifoBuffer[64];

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Initialize MPU
  mpu.initialize();

  // Check if MPU is connected
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);  // Halt execution
  }

  // Initialize DMP
  if (mpu.dmpInitialize() == 0) {
    mpu.setDMPEnabled(true);
    packetSize = mpu.dmpGetFIFOPacketSize();
    Serial.println("DMP ready!");
  } else {
    Serial.println("DMP initialization failed!");
    while (1);
  }

  // Attach servos
  servoX.attach(9);  // Pitch
  servoY.attach(10); // Roll
}

void loop() {
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    float pitch = ypr[1] * 180 / M_PI;
    float roll  = ypr[2] * 180 / M_PI;

    // Map angles to servo range
    int servoPitch = map(-pitch, -30, 30, 60, 120);
    int servoRoll  = map(-roll,  -30, 30, 60, 120);

    servoPitch = constrain(servoPitch, 0, 180);
    servoRoll  = constrain(servoRoll, 0, 180);

    servoX.write(servoPitch);
    servoY.write(servoRoll);

    // Debug output
    Serial.print("Pitch: "); Serial.print(pitch);
    Serial.print(" | Roll: "); Serial.print(roll);
    Serial.print(" | ServoX: "); Serial.print(servoPitch);
    Serial.print(" | ServoY: "); Serial.println(servoRoll);
  }
}