#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

DeviceDriverSet_Motor AppMotor;
DeviceDriverSet_ULTRASONIC USensor;
Application_xxx Application_SmartRobotCarxxx0;

uint16_t prevDistance = 0;
bool hasDetected = false;
bool hasScanned = false; // Tracks if full scan was already done

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

  // Initial 360° spin to search for an object
  if (!hasDetected && !hasScanned) {
    unsigned long startTime = millis();
    unsigned long rotateDuration = 2000; // Adjust based on how long 360° spin takes

    ApplicationFunctionSet_SmartRobotCarMotionControl(3, 50); // Start spinning

    while (millis() - startTime < rotateDuration) {
      distance = USensor.DeviceDriverSet_ULTRASONIC_Get();
      Serial.print("Scanning... Distance: ");
      Serial.println(distance);

      if (distance <= 40 && distance >= 4) {
        hasDetected = true;
        break;
      }

      delay(100);
    }

    ApplicationFunctionSet_SmartRobotCarMotionControl(4, 0); // Stop after scanning
    hasScanned = true;
    return; // Wait until next loop
  }

  // If object detected during spin, approach it
  if (!hasDetected && hasScanned) {
    // Nothing was found after a full spin — stop or idle
    ApplicationFunctionSet_SmartRobotCarMotionControl(4, 0);
    return;
  }

  // Object was found previously — now follow obstacle logic
  if (distance > 45 && prevDistance <= 45) {
    ApplicationFunctionSet_SmartRobotCarMotionControl(1, 50); // Reverse
    delay(500);
    ApplicationFunctionSet_SmartRobotCarMotionControl(3, 50); // Spin to search
  }
  else if (distance <= 45 && distance >= 4) {
    ApplicationFunctionSet_SmartRobotCarMotionControl(0, 50); // Forward
  }
  else {
    ApplicationFunctionSet_SmartRobotCarMotionControl(3, 50); // Spin to search
  }

  prevDistance = distance;
  delay(100);
}

  
