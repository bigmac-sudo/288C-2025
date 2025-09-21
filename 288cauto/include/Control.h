#pragma once
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"

class Control {
public:
    Control(); // Constructor
    void Intake(int speed_voltage);
    void Outake(int speed_voltage);
    void stop();


private:
    pros::Motor intakeMotor;
    pros::Motor combine1;
    pros::Motor flywheel;
    pros::MotorGroup motor_group;
};
