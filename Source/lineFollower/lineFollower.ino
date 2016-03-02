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
int sharp = 0, lectura;
float cm;
unsigned char pinArray[] = "01234567";
ArrayIR array;
motor m1 = {6, 7}, m2 = {8, 9}; //4 ->IN3, 4 ->IN4, 10 ->IN1, 11 ->IN2
int v = 50;  //Rated velocity

void move(int v1, int v2);

void setup()
{
	pinMode(ledCalibration, OUTPUT);
        pinMode(22, OUTPUT); //To use as 5V
        digitalWrite(22, HIGH);
        Serial.begin(9600);
        array.init(pinArray, ledCalibration);
}

void loop()
{
        //Serial.println("Hello");
        //Serial.println(array.searchLine());
        //Serial.println();
	pid(array, v);
        
        //Detectar pared
        //lectura = analogRead(sharp); // lectura del sensor 0
        //cm = pow(3027.4 / lectura, 1.2134); // conversión a centímetros
        //Serial.println(cm);
        //if(cm < 10) move(-20, -20);
        //else if(cm > 10) move(0,0);
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
