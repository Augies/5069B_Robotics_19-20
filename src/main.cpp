/**
 * Program for 5096B Robotics Team in Tower Takeover
 * Has basic autonomous and driver control in Vex PROS
 * @author Augie S., Andrew L.
 */
#include "../include/main.h"

double intakeLiftRPos = 0;
double intakeLiftLPos = 0;

pros::Controller controller(CONTROLLER_MASTER);
pros::Motor DriveTrainL(1);
pros::Motor DriveTrainR(2, true);
pros::Motor DriveTrainMid(3, true);
pros::Motor RampExtender(4);
pros::Motor IntakeL(5);
pros::Motor IntakeR(6, true);
pros::Motor IntakeLiftL(7);
pros::Motor IntakeLiftR(8, true);

bool moveRampRelease = false;
bool setIntakeRelease = false;
bool liftIntakeRelease = false;

bool brelease = false;
void toBasePosition(bool b){
	if(b && !brelease){
		intakeLiftLPos = 50;
		intakeLiftRPos = 50;
		RampExtender.move_absolute(225, 127);
		brelease = true;
	}else if(brelease){
		brelease = false;
	}
}

/**
 * Controls the Drive Train for the bot with a left and right velocity.
 */
void setDriveTrain(int velocityL, int velocityR){
	DriveTrainL.move_velocity(velocityL);
	DriveTrainR.move_velocity(velocityR);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Initializing...");
	tareMotors();
}

/**
 * Tares all of the motors for the robot.
 */
 void tareMotors(){
	 DriveTrainL.tare_position();
	 DriveTrainR.tare_position();
	 DriveTrainMid.tare_position();
	 RampExtender.tare_position();
	 IntakeL.tare_position();
	 IntakeR.tare_position();
	 IntakeLiftL.tare_position();
	 IntakeLiftR.tare_position();
 }

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	tareMotors();
	DriveTrainL.move_velocity(0);
	DriveTrainR.move_velocity(0);
	controller.print(0, 0, "Disabled.");
}

/**
 * Controls the running of the intake motors.
 * Only runs if either L1 or L2 is pressed but not both
 * L1 = backwards
 * L2 = forwards
 */
void setIntake(bool isL1Pressed, bool isR1Pressed){
	if(!(isL1Pressed&&isR1Pressed)){
		if(isL1Pressed){
			IntakeL.move_velocity(-255);
			IntakeR.move_velocity(-255);
			setIntakeRelease = true;
		}else if(isR1Pressed){
			IntakeL.move_velocity(255);
			IntakeR.move_velocity(255);
			setIntakeRelease = true;
		}else if(setIntakeRelease){
			IntakeL.move_absolute(IntakeL.get_position(), 40);
			IntakeR.move_absolute(IntakeR.get_position(), 40);
			setIntakeRelease = false;
		}
	}
}

/**
 * Controls the lifting/lowering of the intakes in order to move cubes upwards.
 */
// int heights[] = {40,80,120,160,200,240,280,320};
// int heightIndex = 0;
void liftIntakes(bool up, bool down){
	// if(!(up&&down)){
	// 	if(up&&heightIndex<sizeof(heights)&&!liftIntakeRelease){
	// 		heightIndex++;
	// 		IntakeLiftL.move_absolute(heights[heightIndex], 127);
	// 		IntakeLiftR.move_absolute(heights[heightIndex], 127);
	// 		liftIntakeRelease = true;
	// 	}else if(down&&heightIndex>0&&liftIntakeRelease){
	// 		heightIndex--;
	// 		IntakeLiftL.move_absolute(heights[heightIndex], 127);
	// 		IntakeLiftR.move_absolute(heights[heightIndex], 127);
	// 		liftIntakeRelease = true;
	// 	}else{
	// 		liftIntakeRelease = false;
	// 	}
	// }
	if(!(up&&down)){
		if(up){
			if(RampExtender.get_position()<600 && IntakeLiftL.get_position()>=600){
				RampExtender.move_absolute(600, 127);
			}
			IntakeLiftL.move_velocity(127);
			IntakeLiftR.move_velocity(127);
			liftIntakeRelease = true;
		}else if(down){
			IntakeLiftR.move_velocity(-127);
			IntakeLiftL.move_velocity(-127);
			liftIntakeRelease = true;
		}else if(liftIntakeRelease){
			intakeLiftLPos = IntakeLiftL.get_position();
			intakeLiftRPos = IntakeLiftR.get_position();
			liftIntakeRelease = false;
			IntakeLiftL.move_absolute(intakeLiftLPos, 127);
			IntakeLiftR.move_absolute(intakeLiftRPos, 127);
		}else{
			IntakeLiftR.move_absolute(intakeLiftRPos, 127);
			IntakeLiftL.move_absolute(intakeLiftLPos, 127);
		}
	}
}
/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	tareMotors();
}

/**
 * Controls movoing of the bot right/left without rotating it.
 * Right trigger moves right, left moves left.
 */
void moveHorizontal(bool isL2Pressed, bool isR2Pressed){
	if(!(isL2Pressed&&isR2Pressed)){
		if(isL2Pressed){
			DriveTrainMid.move_velocity(64);
		}else if(isR2Pressed){
			DriveTrainMid.move_velocity(-64);
		}else{
			DriveTrainMid.move_velocity(0);
		}
	}
}

/**
 * Used to move the Ramp that holds the Cubes foward/backward
 * L = Back R = Forward
 */
void moveRamp(bool isLPressed, bool isRPressed){
	if(!(isLPressed&&isRPressed)){
		if(isLPressed){
			RampExtender.move_velocity(-127);
			moveRampRelease = true;
		}else if(isRPressed){
			RampExtender.move_velocity(127);
			moveRampRelease = true;
		}else if(moveRampRelease){
			RampExtender.move_absolute(RampExtender.get_position(), 40);
			moveRampRelease = false;
		}
	}
}

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
	//TODO This needs done in time for February's competition. If confused, ask me about it - Augie
	//ramp forwards
	// DriveTrainL.move_velocity(127);
	// DriveTrainR.move_velocity(127);
	// pros::delay(1000);
	// DriveTrainL.move_velocity(0);
	// DriveTrainR.move_velocity(0);
	// RampExtender.move_absolute(650, 127);
	// pros::delay(1500);
	// DriveTrainL.move_velocity(-127);
	// DriveTrainR.move_velocity(-127);
	// pros::delay(1000);
	// DriveTrainL.move_velocity(0);
	// DriveTrainR.move_velocity(0);
	// RampExtender.move_absolute(0, -127);
	// pros::delay(1500);
	// RampExtender.move_velocity(0);

	// RampExtender.move_velocity(127);
	// pros::delay(1000);
	// RampExtender.move_velocity(-127);
	// pros::delay(1000);
	// IntakeLiftL.move_velocity(127);
	// IntakeLiftR.move_velocity(127);
	// pros::delay(1000);
	// IntakeLiftR.move_velocity(-127);
	// IntakeLiftL.move_velocity(-127);
	// pros::delay(1000);
	// IntakeLiftL.move_velocity(0);
	// IntakeLiftR.move_velocity(0);
	DriveTrainL.move_absolute(715, 127);
	DriveTrainR.move_absolute(715, 127);
	pros::delay(1600);
	DriveTrainL.move_absolute(0, 127);
	DriveTrainR.move_absolute(0, 127);
	DriveTrainL.move_absolute(0,128);
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
	tareMotors();
	while (true) {
		//Tank Mode
		setDriveTrain(
			controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
			controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)
		);

		//Buttons L1 and R1 for Controlling the Intake
		setIntake(
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1),
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
		);

		//Buttons L2 and R2 for Controlling the Horizontal Translation of the bot
		moveHorizontal(
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2),
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)
		);

		//Lifting the intake in increments
		liftIntakes(
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP),
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)
		);

		//Moving the ramp forwards and backwards
		moveRamp(
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT),
			controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)
		);

		toBasePosition(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B));
		pros::lcd::set_text(1, std::to_string(DriveTrainL.get_position()));
		pros::lcd::set_text(2, std::to_string(DriveTrainR.get_position()));
		pros::delay(10);

	}
}
