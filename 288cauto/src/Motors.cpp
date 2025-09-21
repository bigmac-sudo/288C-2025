#include "pros/motors.h"
#include "Control.h"
#include "pros/abstract_motor.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"


Control::Control():
        intakeMotor(1),
        combine1(2),
        flywheel(3), 
        motor_group({1, 2, 3}) //   intakeMotor, combine1, flywheel
    {
    motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);//coast is better on motors than brake
}


void Control::Intake(int speed_voltage){ //127 is max, 0 is min. 227 = full speed, 0 = no speed.
        intakeMotor.move(speed_voltage);
        combine1.move(speed_voltage);

}

void Control::Outake(int speed_voltage){
        intakeMotor.move(speed_voltage);
        combine1.move(speed_voltage);
        flywheel.move(speed_voltage);
}

void Control::stop(){
    motor_group.brake();

}
