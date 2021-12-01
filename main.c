#include <kipr/botball.h>
#include <stdbool.h>
#include <stdio.h>
#include <gyro.h>
#define leftMotor 0
#define rightMotor 1
#define claw 0
#define topHat 0
#define leftDistance 1
#define rightDistance 2 
// turn_with_gyro params: first is left motor speed, second is right motor speed

void followWall_black_R (int); //distance
void followWall_black_L (int); //distance
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
    calibrate_gyro(100);
    enable_servo(claw);
    servo(0, 1600, 100);
    
    followWall_black_R(2900); //starting position alignment for consistency 
    motor(leftMotor, -50);
    motor(rightMotor, 85);
    msleep(900); //left turn

    straight(90, 1700);
    followLineRight(3.1); 
    straight(90, 100); //on way to green crew mates

    turn_with_gyro(700, -700, 67);
    straight(90, 1700); //turns right and pushes green crewmates out 
    
    motor(leftMotor, 35);
    motor(rightMotor, 100); 
    msleep(2550);
    straight(90, 2275); //turns left, going under the bridge to the other side
    
    motor(leftMotor, -40);
    motor(rightMotor, 60); 
    msleep(1000);
    straight(100, 1050); //left turn, pushes the red crewmates
    straight(90, 3200);
    
    
    
    turn_with_gyro(900, 0, 80); //right turn, begins heading to med bay
    straight(90, 3400);
    turn_with_gyro(900, 0, 90); // seocnd right turn
    
    followWall_black_L(2000);//follows the boarder wall to the perimeter of medbay
    
    followWallLeft(2.8, 2000);
    ao();
    msleep(3100); //goes into med bay, waits 3s


    straight(-90, 2800);
    turn_with_gyro(100, -900, 90); //turns, heads back
    
    followWall_black_R(2700);
    
    //*/


    /*
    followWall_black_R(2700); //go into ramp entrance
    ramp();//goes up ramp + trash chute*/

    //optional: go down ramp, return to starting box
    return 0;

}

void followWall_black_R(int distance) {
    while (analog(topHat) < 3700) {
        if (analog(rightDistance) > distance -350) {
            motor(leftMotor, 13);
            motor(rightMotor, 100);
        }
        if (analog(rightDistance) < distance) {
            motor(leftMotor, 100);
            motor(rightMotor, 13);
        }
    }
}

void followWall_black_L(int distance) {
    while (analog(topHat) < 3700) {
        if (analog(leftDistance) > distance -350) {
            motor(leftMotor, 100);
            motor(rightMotor, 13);
        }
        if (analog(leftDistance) < distance) {
            motor(leftMotor, 13);
            motor(rightMotor, 100);
        }
    }
}

void followWallRight(double time, int distance) {
    double startTime = seconds();
    while (seconds()-startTime < time) {
        if (analog(rightDistance) > distance -350) {
            motor(leftMotor, 50);
            motor(rightMotor, 100);
        }
        if (analog(rightDistance) < distance) {
            motor(leftMotor, 100);
            motor(rightMotor, 50);
        }
    }
}

void followWallLeft(double time, int distance) {
    double startTime = seconds();
    while (seconds()-startTime < time) {
        if (analog(leftDistance) > distance -350) {
            motor(leftMotor, 100);
            motor(rightMotor, 50);
        }
        if (analog(leftDistance) < distance) {
            motor(leftMotor, 50);
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
    straight(80, 1800); //alignment

    turn_with_gyro(100, 1000, 80);//left turn 

    motor(leftMotor, 70);
    motor(rightMotor, 40); 
    msleep(200);
    followWallRight(4, 2900); 
    printf("done1");
    //straight(90, 150);

    turn_with_gyro(100, 900, 75);

    while (analog(leftDistance) > 600){ // while the bot detects the rail, follow line

        if (analog(0) < 3500){
            motor(leftMotor, 90);
            motor(rightMotor, 25);
        }
        if (analog(0) > 3500){
            motor(leftMotor,    25);
            motor(rightMotor, 90);
        }
    }
    printf("done \n");
    straight(90, 150);
    turn_with_gyro(400, 1000, 95); //left turn on bridge
    straight(50, 1000);
    followLineRight(3.7);
}
