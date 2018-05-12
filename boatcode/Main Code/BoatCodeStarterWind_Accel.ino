/* BoatCodeStarterWind_Accel rev 4/22/2016
© 2014-2016 RoboSail
Find detailed description in Decription tab
*/

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include "RoboSail.h"
//Fill in min/max parameters for the RC Receiver and WindSensor in RoboSail.h tab
boolean verbose = true;  //true calls function for values to be printed to monitor


void setup() {
  Serial.begin(115200);
  accel.begin();
  Serial.println("\nRoboSail BoatCode using Wind and Accel - XXXXX");  //write program name here
  // Set RC receiver and WindSensor on digital input pins
  declarePins();
 
}

void loop() {
//*********** Read in data from the RC receiver and sensors *********
readReceiver();
readWind();
readAccel();

//Auto Sail
if (windAngle >= 30 || windAngle <= - 30){
  sailPosition = abs(0.5 * windAngle);
}
else{
  sailPosition = 0;
}

//Heel
if (abs(roll) > 3.0){
  sailPosition += (roll - 3.0) * 5;
}
if (sailPosition > 180)
  sailPosition = 180;
else if (sailPosition < -180)
  sailPosition = -180;

//AutoRudderSwitch
if (sailPulseWidth > 1500){
//Cues
  if (rudderPulseWidth < 1600 && rudderPulseWidth > 1400)
    checkCues = true;
  if (checkCues){
    if (rudderPulseWidth <= 1250){
      if (targetPosition - 45 != 0)
        targetPosition -= 45;
      else
        targetPosition -= 90;
      checkCues = false;
    } 
    else if (rudderPulseWidth >= 1750){
      if (targetPosition + 45 != 0)
        targetPosition += 45;
      else
        targetPosition += 90;
      checkCues = false;
    }
  }
  if (targetPosition > 180){
    targetPosition = 180;
  }
  else if (targetPosition < -180){
    targetPosition = -180;
  }
  Serial.print(targetPosition);

//AutoRudder
  rudderPosition = targetPosition - windAngle;
  if (abs(rudderPosition) < 180){
    rudderPosition *= -1;
  }
  if (rudderPosition > 50){
    rudderPosition = 50;
  }
  else if (rudderPosition < - 50){
    rudderPosition = -50;
  }
  driveRudderServo(rudderPosition);
}

//ManualRudder
else{
  driveRudderServo(rudderPosition);
}
// You now have values from the RC Receiver and Sensors in these variable: 
// rudderPosition, sailPosition, and windAngle, pitch, roll, yaw as
// defined in the RoboSail.h tab
// Calculate new values for rudderPosition and sailPosition in degrees 
// and set those variables to the new values.
// If you do not set the values, it will use the values from the RC Receiver
//**************** your code here - add lines as needed ******************


  
/********************* send commands to motors *************************/
  driveSailServo(sailPosition);
  if (verbose) {printToMonitor();}
  
} //end of loop()


