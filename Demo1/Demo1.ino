#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

DeviceDriverSet_Motor AppMotor;
DeviceDriverSet_ULTRASONIC USensor;
Application_xxx Application_SmartRobotCarxxx0;

uint16_t prevDistance = 0;
bool hasDetected = false;

void setup() {
  AppMotor.DeviceDriverSet_Motor_Init();
  USensor.DeviceDriverSet_ULTRASONIC_Init();

  Serial.begin(9600);
  delay(2000);
}

void loop() {
  uint16_t distance = USensor.DeviceDriverSet_ULTRASONIC_Get();
  
  Serial.print("Distance: ");
  Serial.println(distance);

  //Spins at start until item is detected
  if(!hasDetected){
    if(distance <= 40 && distance >=4){
      hasDetected = true;
      while(distance <=40 && distance >=4){
        ApplicationFunctionSet_SmartRobotCarMotionControl(0,50);
        distance = USensor.DeviceDriverSet_ULTRASONIC_Get();
        Serial.print("Distance: ");
        Serial.println(distance);
      }
    }
    else{
      ApplicationFunctionSet_SmartRobotCarMotionControl(3, 50);
    }
    return;
  }

  if (distance > 45 && prevDistance <= 45) {
    ApplicationFunctionSet_SmartRobotCarMotionControl(1,50); // Reverse
    delay(500);
    ApplicationFunctionSet_SmartRobotCarMotionControl(3,50); // Turn
  }
  else if (distance <= 45 && distance >= 4) {
    ApplicationFunctionSet_SmartRobotCarMotionControl(0,50); // Forward
  }
  else {
    ApplicationFunctionSet_SmartRobotCarMotionControl(3,50); // Spin to search
  }

  prevDistance = distance;
  delay(100);
}
