#include "PID.cpp"
#include <Servo.h>

#define ledCalibration 8
unsigned char pinArray[] = "01234567";

ArrayIR arrayIR (pinArray, ledCalibration);
//Motors
int m1[] = {6,7}, m2[] = {9,10};
int v1 = 170;  //v1 max velocity value


void move(int v1, int v2);


void setup()
{
	pinMode(ledCalibration, OUTPUT);
}

void loop()
{
	pid (arrayIR, v1);
}

//Write the PWM values, we use the A4990. Note that IN2 and IN4 are inverted inputs
void move(int v1, int v2)
{
	


}
