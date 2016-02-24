/*******************************************
 *		Author: Enrique Heredia Aguado     *
 *		Date: 21-02-2016				   *
 *******************************************/

// Class to manage the use of the Array of 8 IR sensors to follow a black line

#define DIM_ARRAY  8
#define N_SAMPLES 5  //number of measures taken in read function, final value is the average 
#define N_CALIBRATION 50 //number of measures taken in calibration function

class ArrayIR {
	private:
		unsigned char pins[DIM_ARRAY];
		unsigned int white, black, borderBlack, borderWhite;
		unsigned int sensorValue[DIM_ARRAY];
		int lastValue; 

		void calibrate (char ledCalibrate);
		void read ();

	public:
		~ArrayIR();
		ArrayIR(unsigned char* _pins, char ledCalibrate = -1) //, unsigned int _white, unsigned int _black);
		//reads the analogPin of the sensor, takes N_SAMPLES measures and does the average. Then maps them between 0 and 1000
		int searchLine ();
}