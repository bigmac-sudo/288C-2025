#include "pros/motors.h"
#include "Control.h"
#include "pros/motors.hpp"
/* Control class:
Features: Controls Combines, Pneuamtics, and vision sensors.
Written with PROS by Carter 9/26/2025
*/
Control::Control():
        intakeMotor(2),
        combineBottom(1),
        combineMiddle(10),
        combineTop(21),
        piston(1)
        // vision_sensor(12)
        // flywheel(3)
    {
        //i like pointers
        motors = {&intakeMotor, &combineMiddle, &combineBottom, &combineTop};
        for (auto motor: motors){
            motor->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        }
}


//ways combine can move
//Intakes
void Control::combineIn(int speed){ //127 is max, 0 is min. 127 = full speed, 0 = no speed
    combineMiddle.move(speed);
    combineBottom.move(speed);
    intakeMotor.move(-speed);//-speed
    combineTop.move(speed);
    // for(auto motor : motors){
    //     motor -> move(-speed_voltage);
    // }

}
//Outakes through top
void Control::combineOutTop(int speed){
    intakeMotor.move(-speed);//-speed
    combineBottom.move(-speed);
    combineMiddle.move(speed);
    combineTop.move(-speed);
}
//Outakes through botoom
void Control::combineOutBottom(int speed){
    intakeMotor.move(speed);//speed
    combineBottom.move(-speed);
    combineMiddle.move(speed);
}
//pneumatics
//Extends Pistons
void Control::extendPistons(){
    piston.set_value(true);
}
//Retracts Pistons
void Control::retractPistons(){
    piston.set_value(false);
}


// //vision sensor for color sorting
// void Control::setColor(int color){
//     if (color==0){
//         selectedColor = 0;
//     }
//     if(color==1){
//         selectedColor = 1;
//     } else{
//         selectedColor = 0;
//     }
// }

// void Control::toggleColorSorting(bool v){
//     toggleColorSortin = v;
// }

// void Control::checkColor(){
    
// }

//stopping all motors
void Control::stop(){
    for(auto motor : motors){
        motor -> brake();
        motor -> move_velocity(0);
    }

}
