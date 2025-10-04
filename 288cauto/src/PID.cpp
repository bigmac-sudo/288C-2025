#include "Auton/PID.h"
#include "pros/adi.h"

/*
'type' is how the type of PID is defined. 
The only difference between each type of PID is the constants.
Only the kD and kP term are being used now, that may change in future iterations
Self explanatory.
KEY:
TYPES of PID,
1- Speed PID
2- rotation pID

*/
PID::PID(signed char type){ 
    //Speed PID
    /*
    You can add more types by following the format below, 
    useful when you have multiple robots or own commands
    */
    if(type == 1){
        kd=2;
        ki= 0.2;
        kp =10;

    } else if(type==2){ //rotation PID
        kd=3;
        kp=10;
        ki = 0;
    }
        error=0;
        pasterror = 0;
        derivative = 0;
        largeError = 2;
        smallerror =1;
        dt = 0.02;
        largeErrorRange =2;
        MaxAcceleration = 10; 
}

//Speed PID
double PID::calculateSpeed(double distance,double currentD){
    error = distance - currentD;
    //dt normalizes it, so we divide derivative by change of time
    derivative = (error - pasterror)/dt;
    integral+= error;
    pasterror = error;

    double output = kp*error+kd*derivative+ki*integral;
    /*
    Oddly, PROS makes motor voltage -127 to 127, 

    Clamps heading between -127 to 127
    */
    if (output > 127){
        output = 127;
    } else if(output < -127) {
        output = -127;
    }
    return output;
    // return 12;
}

double PID::calculateRotation(double currentHeading, float targetHeading){
    // if(currentHeading <= 180){
    //     normalizedHeading = currentHeading;
    // } else if( currentHeading > 180){
    //     normalizedHeading = currentHeading - 360;;
    // }
    error = targetHeading - currentHeading;
    derivative = (error-pasterror)/dt;
    pasterror = error;

    double output = kp*error+kd*derivative;
    //Clamps output between -127 and 127, since max and min voltage in PROS are -127 to 127
    if (output > 127){
        output = 127;
    } else if(output < -127) {
        output = -127;
    }
    return output;
 
 }