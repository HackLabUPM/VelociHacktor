/*******************************************
 *		Author: Enrique Heredia Aguado     *
 *		Date: 24-02-2016				   *
 *******************************************/

#include "ArrayIR.h"

#define MAX_INTEGRAL 1000

#define Kp 0.18
#define Kd 4
#define Ki 0.001

/// PID variables
int  derivative=0, proportional=0, integral=0; //parametros
int  pwm_out=0, past_proportional=0;

unsigned int position=0;

void pid (ArrayIR *array, int v1) //v1 is max velocity value, PID limits it so pwm is not over this value
{ 
	
	position = array.searchLine();

	proportional = position - 3500; //center of the line is between sensor 3 and 4 -> 3500
	integral += past_proportional;
	derivative = (proportional - past_proportional)

	if (integral>MAX_INTEGRAL) integral=MAX_INTEGRAL; //integral limited so to avoid problems
	if (integral<-MAX_INTEGRAL) integral=-MAX_INTEGRAL;

	pwm_out =(proportional * Kp) + (derivative * Kd) + (integral * Ki);

	if (pwm_out>v1)  pwm_out=v1; //velocity calculated from PID is limited
	if (pwm_out<-v1)  pwm_out=-v1;


	if (pwm_out < 0) move (v1+pwm_out, v1); //turn left
 
  	if (pwm_out >0) move (v1, v1-pwm_out); //turn right

 	past_proportional = proportional;

}