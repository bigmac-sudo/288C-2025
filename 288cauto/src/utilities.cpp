#include "cmath"
#include "robot_config.h"
#include <numbers>
#include "Auton/utilities.h"
/*Utilities class

To store functions that is used in Odometry, like gearing and stuff. 

*/
utilities util;
 float gearRatio = .75; //put gear ratio here
const double utilities::circumference = 4.3196898987;
float utilities::WheelSize;
const float utilities::oneTickis = 0.02153;

float utilities::degrees_to_radian(float deg){
    return deg*((std::numbers::pi)/180);
}

// utilities::utilities(){

//     WheelSize = utilities::getwheelDiameter(config.wheelType);
//     // circumference = utilities::calculateCircumference(WheelSize);
// }
 float utilities::calculateCircumference(float wheelSize){
    return wheelSize*std::numbers::pi;
}

 double utilities::calculateGearing(double motorRotations){
return utilities::ticks_to_degrees(motorRotations)/gearRatio; 
}
 float utilities::getwheelDiameter(Wheel WheelSize){
    switch(WheelSize){
        case Wheel::TWO_POINT_SEVEN_FIVE: return 2.75;
        case Wheel::THREE_POINT_TWO_FIVE: return 3.25;
        case Wheel::FOUR_POINT_ZERO: return 4.0;
    }
}

// double utilities::ticks_to_degrees(float ticks){
//     //600 RPM motors have 300 ticks per rev, so i felt like dividing 360(ticks)/300 whcih simplifies 
//     return (18*ticks)/15;
// }

 double utilities::ticks_to_inch(float ticks){
    return ticks*oneTickis;
}
