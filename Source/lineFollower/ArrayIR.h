/*******************************************
 *		Author: Enrique Heredia Aguado     *
 *		Date: 21-02-2016				   *
 *******************************************/

// Class to manage the use of the Array of 8 IR sensors to follow a black line

#define DIM_ARRAY  8
#define N_SAMPLES 5  //number of measures taken in read function, final value is the average 
#define N_CALIBRATION 50 //number of measures taken in calibration function
#define LECTURE_TIME 250 //ms of time in calibration for each lecture
#define CALIB_CONFIRMATION 3000 //time led will be one once calibration is over

class ArrayIR { 
	private:
		unsigned char pins[DIM_ARRAY];
		unsigned int white, black, minBlack, minWhite;
		int sensorValue[DIM_ARRAY];
		int lastValue; 

		//reads the analogPin of the sensor, takes N_SAMPLES measures and does the average. Then maps them between 0 and 1000
		//calibration must be done moving the robot with the array parallel to the line and movin it forward until LED stops blinking (in case ther's a LED)
		//time needed can be calculated by multiplying N_SAMPLES X LECUTRE_TIME
		//once finished LED will be on for 3000 ms 
		void calibrate(char ledCalibrate);
		void read();

	public:
		~ArrayIR();
		ArrayIR(unsigned char* _pins, char ledCalibrate = -1);
		//if calibration measures are given from outside: , unsigned int _white, unsigned int _black)

		int searchLine ();
};
