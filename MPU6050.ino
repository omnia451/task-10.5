#include <Wire.h>

#define MPU6050_ADD 0x68
#define MPU6050_PWR 0x6B
#define MPU6050_GYRO_ZOUT_H 0x47

float gyroYaw = 0;
float prevTime = 0;
float yaw = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Wire.beginTransmission(MPU6050_ADD);
  Wire.write(MPU6050_PWR);
  Wire.write(0);
  Wire.endTransmission(true);

  prevTime = millis();
}

void loop() {
  float currentTime = millis();
  float deltaTime = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;

  int16_t gyroZ = readGyroZ();

  gyroYaw = gyroZ / 131.0;

  yaw += gyroYaw * deltaTime;

  Serial.print("Yaw: ");
  Serial.println(yaw);
  
  delay(100);
}

int16_t readGyroZ() {
  Wire.beginTransmission(MPU6050_ADD);
  Wire.write(MPU6050_GYRO_ZOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADD, 2, true);
  
  int16_t rawGyroZ = Wire.read() << 8 | Wire.read();
  return rawGyroZ;
}
