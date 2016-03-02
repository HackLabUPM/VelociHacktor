#include "ArrayIR.h"
#include "PID.h"

//MACROS
#define ledCalibration 23

//STRUCTS
typedef struct
{
    int p1;
    int p2;
} motor;

//DECLARATIONS
unsigned char pinArray[] = "01234567";
ArrayIR array;
motor m1 = {10, 11}, m2 = {8, 9}; //4 ->IN3, 4 ->IN4, 10 ->IN1, 11 ->IN2
int v = 50;  //Rated velocity

void move(int v1, int v2);

void setup()
{
	pinMode(ledCalibration, OUTPUT);
        pinMode(22, OUTPUT); //To use as 5V
        digitalWrite(22, HIGH);
        Serial.begin(19200);
    array.init(pinArray, ledCalibration);
}

void loop()
{
        Serial.println("Hello");
        //Serial.println(array.searchLine());
        //Serial.println();
	pid(array, v);
        
}

//Write the PWM values, we use the A4990. Note that IN2 and IN4 are inverted inputs
void move(int v1, int v2)
{
    if (v1 >= 0) {
        analogWrite(m1.p1, v1);
        analogWrite(m1.p2, 255);
    }
    else {
        analogWrite(m1.p1, 0);
        analogWrite(m1.p2, 255 - v1);
    }
    
    if (v2 >= 0) {
        analogWrite(m2.p1, v2);
        analogWrite(m2.p2, 255);
    }
    else {
        analogWrite(m2.p1, 0);
        analogWrite(m2.p2, 255 - v2);
    }
    
}
