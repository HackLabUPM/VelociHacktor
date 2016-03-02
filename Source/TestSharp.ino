//---------------------------------
//
//	Author: Javier García López
//	     Date: 02-03-2016
//
//---------------------------------

//STRUCTS
typedef struct
{
    int p1;
    int p2;
} motor;

//DECLARATIONS
motor m1 = {6, 7}, m2 = {10, 11};
int sharp = A0;
min_dist = 10; //Minimum distance in cm

//DEFINITIONS
int readSharp(int sensor);
void move(int v1, int v2);

//MAIN
void setup()
{
	pinMode (m1.p1, OUTPUT);
 	pinMode (m1.p2, OUTPUT);
 	pinMode (m2.p1, OUTPUT);
 	pinMode (m2.p2, OUTPUT);
}

void loop()
{
	if (readSharp (sharp) > min_dist)
		move (100, 100);

	if (readSharp (sharp) < min_dist)
		move (-50, -100);
}

//FUNCTIONS
//Reads the sharp sensor
int readSharp(int sensor)
{
	int lectura, cm;
	lectura = analogRead (sensor);
	cm = pow(3027.4 / lectura, 1.2134);
	return cm;
}

//Write the PWM values, we use the A4990. Note that IN2 and IN4 are logic inverted inputs
void move(int v1, int v2)
{
    if (v1 >= 0) {
        analogWrite(v1, m1.p1);
        analogWrite(255, m1.p2);
    }
    else {
        analogWrite(0, m1.p1);
        analogWrite(255 - v1, m1.p2);
    }
    if (v2 >= 0) {
        analogWrite(v2, m2.p1);
        analogWrite(255, m2.p2);
    }
    else {
        analogWrite(0, m2.p1);
        analogWrite(255 - v2, m2.p2);
    }
}