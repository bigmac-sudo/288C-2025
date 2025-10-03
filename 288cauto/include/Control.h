#pragma once
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/vision.hpp"

class Control {
public:
    Control(); // Constructor
    void combineOutTop(int speed);
    void combineOutBottom(int speed);
    void combineIn(int speed);
    void retractPistons();
    void extendPistons();
    //if we decide to color sort
    void toggleColorSorting(bool v); //whether to color sort
    void setColor(int color); //0 is blue, 1 is red
    void checkColor();
    void stop();
    


private:
    pros::Motor intakeMotor;
    pros::Motor combineTop;
    pros::Motor combineBottom;
    pros::Motor combineMiddle;
    //pneumatics
    pros::adi::DigitalOut piston;
    //vision sensor for color sorting
    // motor group;
    std::vector<pros::Motor*> motors;

    int selectedColor;
    bool toggleColorSortin;
    // pros::MotorGroup motor_group;
};
