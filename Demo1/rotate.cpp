void loop() {
    static bool hasRotated = false;
  
    if (!hasRotated) {
      unsigned long startTime = millis();
      unsigned long rotateDuration = 2000; // Adjust this for a full 360 rotation
  
      while (millis() - startTime < rotateDuration) {
        ApplicationFunctionSet_SmartRobotCarMotionControl(6 /*rotate left*/, 50);
      }
  
      ApplicationFunctionSet_SmartRobotCarMotionControl(4 /*stop*/, 0);
      hasRotated = true;
    }
  
    // After rotating, do nothing
  }
  