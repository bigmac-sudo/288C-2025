#include "liblvgl/llemu.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "robot_config.h"
#include "Auton/auton.h"
#include "Auton/utilities.h"
#include "Auton/PID.h"
#include <string>
#include <type_traits>
Position pos; 
Position targetPos;
parameters par;
PID drivePID(1);
PID rotationPID(2);
float Autonomous::distanceV;

/*
Auton doesn't support odometry right now, just PID based driveForward(inch) or driveBackward(inch)
and turnTo(deg)

First iteration, theoretically supports reverse driving, e
PID can be fine tuned in PID.cpp, read instructions for that. 

*/
 void Autonomous::moveMotors(double distancePID, double rotationVal1){
    config.leftchassis.move(distancePID);
    config.rightchassis.move(distancePID);
}

//its all relative to the current position right now
void Autonomous::driveFor(float distance){
    //sets distance traveled
    double distanceTraveled=0;
    double error = 0.99*distance - distanceTraveled;
    config.frontLeftMotor.tare_position();
    config.frontRightMotor.tare_position();
    while (config.inertialSenor.is_calibrating()){
        pros::delay(10);
    }
    //If error is larger than .2, PID runs
    while (fabs(error)> drivePID.smallerror){
        double avgdist = 
        // utilities::rad_to_inch(utilities::degrees_to_radian(
        //     utilities::calculateGearing(
        //         (config.frontLeftMotor.get_position()+
        //         config.frontRightMotor.get_position())/2)

        //     )

        // );  
        avgdist = utilities::ticks_to_inch((config.frontLeftMotor.get_position()+
                 config.frontRightMotor.get_position())/2);
        // distanceV = avgdist;          
        distanceTraveled = avgdist;
        pros::lcd::set_text(2, std::to_string(avgdist));
        Autonomous::moveMotors(drivePID.calculateSpeed(distance,distanceTraveled),0);
        pros::delay(20);
    }
    Autonomous::moveMotors(0,0);

}

/*
turnTo(deg)
Accepts values [-180,180], values beyond/below that can lead to unexpected behavior

It turns to headings relative to the robot heading 
before the turn started, so if you have mutliple turns, be mindful of that

PID based control
*/
void Autonomous::turnTo(double rotation ){
    config.inertialSenor.reset();
    double error;
    double normalizedRotation;
        if(rotation <= 0){
            normalizedRotation = rotation;
        } else if( rotation > 0){
            normalizedRotation = -rotation + 180;
        }
    double currentHeading;
    error = rotation - config.inertialSenor.get_heading();
        //gets absolute value of error and if its greater than tolerance, run PID
        while(fabs(error) > 1){
            currentHeading = config.inertialSenor.get_heading();

        error = normalizedRotation - currentHeading;
            Autonomous::moveMotors(0, rotationPID.calculateRotation(currentHeading, rotation));
            pros::delay(20);
        }  
}

//wont use this since auto runs on its own thread by default... Need to read better

/*void Autonomous::autonManager(void* param){
    while (true){
        if(pros::competition::is_autonomous()){
            config.frontLeftMotor.tare_position();
            config.frontRightMotor.tare_position();
            if(par.isAutonEnabled == true){
                Autonomous::driveFor(par.driveForward);
            }
        }
        pros::delay(20);
    }
}

*/
