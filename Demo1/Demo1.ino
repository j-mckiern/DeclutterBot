#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

DeviceDriverSet_Motor AppMotor;
DeviceDriverSet_ULTRASONIC USensor;
Application_xxx Application_SmartRobotCarxxx0;

void setup() {
  AppMotor.DeviceDriverSet_Motor_Init();
  USensor.DeviceDriverSet_ULTRASONIC_Init();

  Serial.begin(9600);
  delay(2000);
}
void loop() {
  uint16_t distance = 0;
  distance = USensor.DeviceDriverSet_ULTRASONIC_Get();

  Serial.print("Distance:");
  Serial.print(distance);
  Serial.print("\n");
  if (distance <= 40 && distance >= 3){
    ApplicationFunctionSet_SmartRobotCarMotionControl(0 /*direction*/, 50 /*speed*/);
  }
  else if (distance > 40) {
        ApplicationFunctionSet_SmartRobotCarMotionControl(3, 50);
  }

  delay(100);

}
