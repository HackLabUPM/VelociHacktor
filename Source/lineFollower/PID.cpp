/*******************************************
 *	Author: Enrique Heredia Aguado         *
 *	Last Actualization Date: 02-03-2016	   *
 *******************************************/
 
#include "Arduino.h"
#include "ArrayIR.h"
#include "PID.h"

/// PID variables
int  derivative=0, proportional=0, integral=0; //parametros
int  pwm_out=0, past_proportional=0;

unsigned int position;

void pid (ArrayIR array, int v) //Rated velocity, when moving straight this is the max velocity, PID limits it so pwm is not over this value
{ 
	Serial.println("Hello6");
	position = array.searchLine();

	proportional = position - 3500; //center of the line is between sensor 3 and 4 -> 3500
	integral += past_proportional;
	derivative = (proportional - past_proportional);

	if(integral>MAX_INTEGRAL) integral=MAX_INTEGRAL; //integral limited so to avoid problems
	if(integral<-MAX_INTEGRAL) integral=-MAX_INTEGRAL;

	pwm_out=(proportional * Kp) + (derivative * Kd) + (integral * Ki);

	if(pwm_out>v)  pwm_out=v; //velocity calculated from PID is limited
	if(pwm_out<-v)  pwm_out=-v;


	if(pwm_out < 0) move(v - pwm_out, v); //turn left
 
  	if(pwm_out >0) move(v, v - pwm_out); //turn right

 	past_proportional = proportional;
        Serial.println("Hello10");
}
