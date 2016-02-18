/******************************************************************************
* File Name          : uArm_Library_Metal.h
* Author             : Joey Song
* Updated            : Joey Song
* Version            : V0.0.1 (BATE)
* Created Date       : 12 Dec, 2014
* Modified Date      : 17 Dec, 2015
* Description        : 
* License            : 
* Copyright(C) 2014 UFactory Team. All right reserved.
*******************************************************************************/

#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Servo.h>
#include "linreg.h"

#ifndef uArm_library_h
#define uArm_library_h

#define BUZZER                  				3
#define CALIBRATION_FLAG						0xEE

#define SERVO_ROT_NUM							1
#define SERVO_LEFT_NUM							2
#define SERVO_RIGHT_NUM							3
#define SERVO_HAND_ROT_NUM						4


// Action control
#define SERVO_HAND              9     
#define HAND_ANGLE_OPEN         25
#define HAND_ANGLE_CLOSE        70
#define PUMP_EN                 6     
#define VALVE_EN                5     
#define MATH_PI	3.141592653589793238463
#define MATH_TRANS  57.2958
#define MATH_L1	(10.645+0.6)
#define MATH_L2	2.117
#define MATH_L3	14.825
#define MATH_L4	16.02
#define MATH_L43 MATH_L4/MATH_L3

#define RELATIVE 1
#define ABSOLUTE 0

#define INTERP_INTVL     50

#define TopOffset -1.5
#define BottomOffset 1.5

#define LINEAR_START_ADDRESS 90
#define OFFSET_START_ADDRESS 60

#define SERVO_ROT_ANALOG_PIN 2
#define SERVO_LEFT_ANALOG_PIN 0
#define SERVO_RIGHT_ANALOG_PIN 1
#define SERVO_HAND_ROT_ANALOG_PIN 3


class uArmClass 
{
public:
	uArmClass();
	

	double readServoOffset(byte servo_num);
    void detachServo(byte servo_num);
	void alert(byte times, byte runTime, byte stopTime);
    void saveDataToRom(double data, int addr);
    void attachAll();
    void detachAll();
	void writeAngle(double servo_rot_angle, double servo_left_angle, double servo_right_angle, double servo_hand_rot_angle);
	byte inputToReal(byte servo_num , double input_angle);
	double readAngle(byte servo_num);
	double readToAngle(double input_angle, byte servo_num, byte trigger);
	void writeAngle(byte servo_rot_angle, byte servo_left_angle, byte servo_right_angle, byte servo_hand_rot_angle, byte trigger);
	// void writeAngle(byte servo_rot_angle, byte servo_left_angle, byte servo_right_angle);
	double readAngle(byte servo_num, byte trigger);

// Action control start

	void moveTo(double x, double y,double z);
	void moveTo(double x, double y,double z,int relative, double time);
	void moveTo(double x, double y,double z,int relative, double time_sepnd, double servo_4_angle);
	void moveTo(double x, double y, double z, int relative, double time_spend, int servo_4_relative, double servo_4_angle);
	void moveToAtOnce(double x, double y, double z, int relative, double servo_4_angle);

	void drawCur(double length_1,double length_2,int angle, double time_spend);
	void drawRec(double length_1,double length_2,double time_spend_per_length);

	double getTheta1() const {return g_theta_1;}
	double getTheta2() const {return g_theta_2;}
	double getTheta3() const {return g_theta_3;}

	double getCalX() {return g_cal_x;}
	double getCalY() {return g_cal_y;}
	double getCalZ() {return g_cal_z;}
	void getCalXYZ(double& x, double& y, double &z) {calXYZ(); x = g_cal_x; y = g_cal_y; z = g_cal_z;}
	void getCalXYZ(double theta_1, double theta_2, double theta_3, double& x, double& y, double &z) {calXYZ(theta_1, theta_2, theta_3); x = g_cal_x; y = g_cal_y; z = g_cal_z;}

	void calAngles(double x, double y, double z);
	void getCalAngles(double x, double y, double z, double& theta_1, double& theta_2, double& theta_3) {calAngles(x, y, z); theta_1 = g_theta_1; theta_2 = g_theta_2; theta_3 = g_theta_3;}

	void calXYZ(double theta_1, double theta_2, double theta_3);
	void calXYZ();

	void gripperCatch();
	void gripperRelease();
	void interpolation(double init_val, double final_val, double (&interpol_val_array)[INTERP_INTVL]);
	void pumpOn();
	void pumpOff();
protected:
	// double getInterPolValueArray(int num) const {return g_interpol_val_arr[10];}
	double calYonly(double theta_1, double theta_2, double theta_3);

	double g_theta_1;
	double g_theta_2;
	double g_theta_3;

	double g_cal_x;
	double g_cal_y;
	double g_cal_z;
		
	boolean g_gripper_reset;
// action control end
private:
	/*****************  Define variables  *****************/
    unsigned int addr;

	Servo g_servo_rot;
	Servo g_servo_left;
	Servo g_servo_right;
	Servo g_servo_hand_rot;
	Servo g_servo_hand;
	
	double g_servo_offset;

};

extern uArmClass uarm;

#endif

