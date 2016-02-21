//-----------------------------------------
//
//		Author: Luis H. Porras
//		Date: 17-02-2016
//
//-----------------------------------------

//MACROS
#define DIM = 8;

//DECLARATIONS
//IR sensors
int ir[DIM] = {0, 1, 2, 3, 4, 5, 6, 7};
int black, white;
//Motors
int m1[] = {6,7}, m2[] = {9,10};

//DEFINITIONS
void calibrate();
void move(int v1, int v2);
void sniff(int v1, int semiperiod);

//MAIN
void setup()
{
	

}
void loop()
{


}

//FUNCTIONS

//Calibrates the IR array by taking the highest and lowest reflectivness
void calibrate()
{
	int tic, toc, i, m;

	tic = millis();
	toc = tic;
	while(toc - tic < 5000)
	{
		sniff(40, 2000);
		for(i = 0; i < DIM; i++){
			m = analogRead(i);
			if(m > black) black = m;
			else if (m < white) white = m;
		}
		toc = millis();
	}

}

//Write the PWM values, we use the A4990. Note that IN2 and IN4 are inverted inputs
void move(int v1, int v2)
{
	


}

//The robot moves it's nose side to side:
//The function must be called while the action has to be performed.
//Once it's been used, no initialization will be performed, caution.
void sniff(int v1, int semiperiod) 
{
	//Initialization only first time
	volatile int stic = 0, stoc, v2 = 0, auxv; 

	stoc = millis();

	//The robot will oscillate with the given period
	if (stic = 0)
	{
		stic = millis();
		move(v1, v2);
	}
	else if(stoc - stic >= semiperiod)
	{
		auxv = v1;	
		v1 = v2;
		v2 = auxv;
		move(v1, v2);
		stic = millis();
	}

}












