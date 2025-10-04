#include "main.h"
#include "Control.h"
#include "robot_config.h"
#include "Auton/auton.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
 //Front,middle,back
int leftports[3] = {-5, 4, -3};
int rightports[3] = {6, -7, 8};

Control control;
Configuration config(
    Wheel::TWO_POINT_SEVEN_FIVE, // Wheel size
    20, //IMU port
    leftports, //left chassis
    rightports //right chassis
	
);


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	Autonomous::driveFor(10);
	control.combineIn(20);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER); //  creates controller

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		// Arcade control scheme
		int dir = controller.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = controller.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		config.leftchassis.move(dir + turn);                    // Sets left motor voltage
		config.rightchassis.move(dir - turn);  // Sets right motor voltage
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			control.combineIn(127);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            control.combineOutTop(127);
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            control.combineOutBottom(127);
        }else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
            control.retractPistons();
        } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
            control.extendPistons();
        } else {
            control.stop();
        }                   
		pros::delay(20);                               // Run for 20 ms then update
	
	}
}