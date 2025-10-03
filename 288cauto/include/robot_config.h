#pragma once

#include "pros/imu.hpp"
#include "pros/motor_group.hpp"

#include "pros/motors.hpp"
#include <vector>
//so you can select wheel size :+)
enum class Wheel {
    TWO_POINT_SEVEN_FIVE,
    THREE_POINT_TWO_FIVE,
    FOUR_POINT_ZERO,
};

struct Configuration {
    Wheel wheelType;
    pros::Imu inertialSenor;
    pros::MotorGroup leftchassis;
    pros::MotorGroup rightchassis;
    pros::Motor frontRightMotor;
    pros::Motor frontLeftMotor;    //config file makes it eaiser to change values
    Configuration(enum Wheel wheelArg,int imu, int left[3], int right[3]):
    //create motor groups
        leftchassis({
            //need to cast to signed char because it doesn't accept integers, braces to convert a list
            static_cast<signed char>(left[0]),
            static_cast<signed char>(left[1]), 
            static_cast<signed char>(left[2])}),
        rightchassis({
            static_cast<signed char>(right[0]),
            static_cast<signed char>(right[1]),
            static_cast<signed char>(right[2])}),
        //make inertial sensor
        inertialSenor(static_cast<signed char>(imu)),
        //make wheel with wheel
        wheelType(wheelArg),
        frontLeftMotor(static_cast<signed char>(left[0])),
        frontRightMotor(static_cast<signed char>(right[0]))
        
        {}
};


extern Configuration config;
