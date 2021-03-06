#include <kipr/botball.h>
#include <stdbool.h>
#include <stdio.h>
#include <gyro.h>
#define leftMotor 0
#define rightMotor 1
#define claw 1
#define topHat 0
#define leftDistance 1
#define rightDistance 2 
// turn_with_gyro params: first is left motor speed, second is right motor speed

void followWallBlackRight (int); //distance
void followWallBlackLeft (int); //distance
void followWallRight (double, int); //time in seconds, distance
void followWallLeft (double, int);//time in seconds, distance
void servo (int, int, int); //port, position, time in ms
void followLineLeft (double); //turns left on white; time in seconds
void followLineRight (double); //turns right on white; time in seconds
void straight (int, int); //speed (-100 to 100), time in ms
void ramp(); //before this: followWallBlack(2700, 2); 
void followLine_reverse (double); //reverse follow line, time in seconds
void offRamp(); //off ramp


int main() {
    //servo stratingn pos: 300
    //leftMotor = 0.7* rightMotor
    //code to make gyro work
    declare_motors(0, 1); 
    calibrate_gyro(1000);
    enable_servo(claw);
    servo(1, 1300, 100);
    double startingTime = seconds();
	
    followWallBlackRight(2900); //starting position alignment for consistency 
    motor(leftMotor, -50);
    motor(rightMotor, 85);
    msleep(950); //left turn

    straight(90, 1700);
    followLineRight(3.2); 
    straight(90, 300); //on way to green crew mates

    turn_with_gyro(700, -700, 67);
    straight(90, 1700); //turns right and pushes green crewmates out 

    motor(leftMotor, 40);
    motor(rightMotor, 95); 
    msleep(2700);
    straight(90, 2240); //turns left, going under the bridge to the other side

    motor(leftMotor, -40);
    motor(rightMotor, 60); 
    msleep(1300); 
    straight(100, 1075); //crewmates oushed
    printf("%f, crewmates \n", seconds() - startingTime);
    while(analog(0) < 3700){ //alignment
        straight(100, 10); 
    }
    printf("red align %f \n", seconds() - startingTime);
    motor(leftMotor, 25);
    msleep(100);
    straight(90, 3125);
    servo(1, 2000, 100);

    turn_with_gyro(900, -250, 60); //right turn, begins heading to med bay

    straight(90, 400); //alignment + collection for wires
    ao();
    motor(leftMotor, 60); 
    msleep(225);
    straight(90, 500); //first alignment 
    ao();

    motor(leftMotor, 100);
    msleep(325);
    straight(90, 2500); //second alignment
    ao();

    motor(leftMotor, 50); //third alignment
    msleep(125);

    turn_with_gyro(900, 0, 82); // seocnd right turn

    straight(90, 2500); //to medbay
    
    //motor(rightMotor, 50);
    //msleep(200);
    motor(leftMotor, 50); //alignment
    msleep(175);


    //followWallBlackLeft(1700);//follows the boarder wall to the perimeter of medbay

    followWallLeft(2, 1700);


    servo(1, 0, 100);
    ao();
    msleep(3100); //goes into med bay, waits 3s

    servo(1, 1300, 100);


    turn_with_gyro(900, -900, 55);
    straight(90, 850);
    ao();
    msleep(100); //goes into red wires box 

    straight(-90, 850);
    turn_with_gyro(-900, 900, 80);
    //msleep(775); //backs out of red wires box

    straight(-90, 3550);
    turn_with_gyro(100, -900, 90); //turns, heads back
	ao();
    msleep(25);
    motor(leftMotor, 65);
    msleep(225); //alignment
    straight(90, 2200);
    ao();

    motor(rightMotor, 60); //alignment against wall
    msleep(200);
	

    followWallBlackRight(2700); //heads to ramp
    ramp(); //goes up ramp, pushes trash
    ao();
    msleep(400);
    servo(1, 2400, 100);
    offRamp(); //exits ramp back to starting box*/

    printf("%f", seconds() - startingTime);
    return 0;

}

void followWallBlackRight(int distance) {
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

void followWallBlackLeft(int distance) {
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
    straight(80, 1900); //alignment

    turn_with_gyro(100, 1000, 80);//left turn 

    motor(leftMotor, 70);
    motor(rightMotor, 40); 
    msleep(500);
    followWallLeft(3.7, 2900); 
    printf("done1\n");
    straight(90, 175);

    turn_with_gyro(100, 900, 67);

    while (analog(leftDistance) > 800){ // while the bot detects the rail, follow line

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
    straight(90, 225);
    turn_with_gyro(400, 1000, 95); //left turn on bridge
    straight(90, 550);
    followLineRight(3.6);
    straight(90, 300);
}


void offRamp(){
    straight(-80, 1600);
    motor(leftMotor, -90*0.7);
    motor(rightMotor, 90);
    msleep(250); 
    while (analog(0) < 3700){
        motor(leftMotor, -90*0.7);
        motor(rightMotor, 90);
    }
    ao();
    msleep(200); //u-turn, starts exit

    straight(90, 600);
    followLineRight(3.4);
    straight(90, 250);
    while (analog(0) < 3700){
        straight(90, 10); //traves the upper segment of ramp
    }
    ao();
    msleep(35);
    straight(-90, 325); //alignment

    motor(leftMotor, 90);
    motor(rightMotor, -75); //right turn
    msleep(675);

    straight(90, 1225); //alignment 
    while(analog(rightDistance) > 600){
        if (analog(topHat) < 3500){
            motor(leftMotor, 45);
            motor(rightMotor, 90);
        }
        if (analog(topHat) > 3500){
            motor(leftMotor, 90);
            motor(rightMotor, 45);
        }
    } //off ramp

    straight(90, 525);
    turn_with_gyro(900, -100, 85); //right turn, exits ramp

    followWallLeft(3, 2300);

}

void fuel(){
    int counter;
    for(counter = 0; counter < 3; counter++){
        set_servo_position(1, 1300);
        msleep(200);
        straight(90, 2050);
        ao();
        msleep(500);
        set_servo_position(1, 700);
        msleep(600);
        straight(-80, 500);
        set_servo_position(1, 1600);
        msleep(700);
        motor(leftMotor, 30);
        msleep(25);
        straight(90, 600);
    }
}

