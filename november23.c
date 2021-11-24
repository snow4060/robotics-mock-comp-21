#include <kipr/botball.h>
#include <stdbool.h>
#include <gyro.h>
#define leftMotor 0
#define rightMotor 1
#define claw 0
#define topHat 0
#define leftDistance 1
#define rightDistance 2
// turn_with_gyro params: first is left motor speed, second is right motor speed

void followWall_black (int, int); //distance, port#
void followWallRight (double, int); //time in seconds, distance
void followWallLeft (double, int);//time in seconds, distance
void servo (int, int, int); //port, position, time in ms
void followLineLeft (double); //turns left on white; time in seconds
void followLineRight (double); //turns right on white; time in seconds
void straight (int, int); //speed (-100 to 100), time in ms
void ramp(); //before this: followWallBlack(2700, 2); 


int main() {
    //leftMotor = 0.7* rightMotor
    //code to make gyro work
    declare_motors(0, 1); 
    int gyroZ = gyro_z();
    calibrate_gyro(gyroZ);
    enable_servo(claw);

    /*servo(claw, 400, 200);
    straight(-80, 1500);
    motor(leftMotor, -25);
    msleep(45); //purpenticular alignment
    
    servo(claw, 1600, 200);*/
    
    followWall_black(2900, 2);
    motor(leftMotor, -50);
    motor(rightMotor, 75);
    msleep(900);
    straight(90, 1700);
    followLineRight(3);
    straight(90, 400);
    motor(leftMotor, 90);
    motor(rightMotor, -75);
    msleep(850);
    straight(90, 550);
    
    straight(-100, 2600);
    turn_with_gyro(-900, 400, 100);
    straight(90, 450);
    motor(leftMotor, 70);
    msleep(150);
    
   followWallLeft(6, 2100);




    /*// go into ramp entrance
    followWall_black(2700, 2);
    ramp();//goes up ramp + trash chute*/
    return 0;

}

void followWall_black(int distance, int port) {
    while (analog(topHat) < 3700) {
        if (analog(port) > distance -350) {
            motor(leftMotor, 13);
            motor(rightMotor, 100);
        }
        if (analog(port) < distance) {
            motor(leftMotor, 100);
            motor(rightMotor, 13);
        }
    }
}

void followWallRight(double time, int distance) {
    double startTime = seconds();
    while (seconds()-startTime < time) {
        if (analog(2) > distance -350) {
            motor(leftMotor, 13);
            motor(rightMotor, 100);
        }
        if (analog(2) < distance) {
            motor(leftMotor, 100);
            motor(rightMotor, 13);
        }
    }
}

void followWallLeft(double time, int distance) {
	double startTime = seconds();
	while (seconds()-startTime < time) {
		if (analog(1) > distance -350) {
            motor(leftMotor, 100);
            motor(rightMotor, 13);
        }
        if (analog(1) < distance) {
            motor(leftMotor, 13);
            motor(rightMotor, 100);
        }
    }
}


void servo(int port, int pos, int time) {
    set_servo_position(port, pos);
    msleep(time);
}

void followLineLeft(double time) {
    double startTime = seconds();
    while (seconds() - startTime < time){

        if (analog(topHat) < 3500){
            motor(leftMotor, 45);
            motor(rightMotor, 90);
        }
        if (analog(topHat) > 3500){
            motor(leftMotor, 90);
            motor(rightMotor, 45);
        }
    }
}

void followLineRight(double time) {
    double startTime = seconds();
    while (seconds() - startTime < time){

        if (analog(topHat) < 3500){
            motor(leftMotor, 90);
            motor(rightMotor, 45);
        }
        if (analog(topHat) > 3500){
            motor(leftMotor, 45);
            motor(rightMotor, 90);
        }
    }
}

void straight(int speed, int time) {
    motor(leftMotor, speed * 0.7);//bias
    motor(rightMotor, speed);
    msleep(time);
}

void ramp() {
    motor(leftMotor, 60);
    motor(rightMotor, 80);
    msleep(1800); //alignment

    turn_with_gyro(100, 1000, 80);//left turn 
    motor(leftMotor, 70);
    motor(rightMotor, 40);
    msleep(200);
    followWallRight(5, 2900);
    straight(80, 400);
    turn_with_gyro(100, 900, 85);
    // while the bot detects the rail, follow line
    while (analog(leftDistance) > 600){

        if (analog(0) < 3500){
            motor(leftMotor, 90);
            motor(rightMotor, 25);
        }
        if (analog(0) > 3500){
            motor(leftMotor, 	25);
            motor(rightMotor, 90);
        }
    }
    printf("done \n");
    straight(90, 150);
    turn_with_gyro(400, 1000, 80); //left turn on bridge
    followLineLeft(1); //straight
    followLineRight(4);
}
