/*******************************************
 *		Author: Enrique Heredia Aguado     *
 *		Date: 21-02-2016				   *
 *******************************************/

#include "ArrayIR.h"
#include <math.h>

void ArrayIR::ArrayIR (unsigned char* _pins, char ledCalibrate ) //, unsigned int _white, unsigned int _black)
{
	//white = _white;
	//black = _black;

    white = 0;
    black = 0;
    Calibrate(ledCalibrate);

	for (int i=0; i<DIM_ARRAY; i++)
	{
		pins[i]=_pins[i];
	}

    borderBlack = black - (std::abs(white-black)/6);
    borderWhite = white + (std::abs(white-black)/6);
}

void ArrayIR::read ()
{
	// reset the values
    for(int i = 0; i < DIM_ARRAY; i++)
        sensorValue[i] = 0;

    //Reads and adds N_SAMPLES measures
    for(int i=0; i<N_SAMPLES;i++)
    {
    	for (int j=0; j<DIM_ARRAY; j++)
    	{
    		sensorValue[j] += analogRead (pin[j]);
    	}
    }

    //calculates the average, this will be the final value of the reading
    for (i = 0; i < DIM_ARRAY; i++)
    {
        sensorValue[i] = map ( (sensorValue[i] / (int)N_SAMPLES), white, black,0,1000;
        if (sensorValue[i]>1000) sensorValue=1000;
        else if (sensorValue[i]<0) sensorValue=0;
    }

    //map (var, lim1, lim1, med1, med2)
     /* var = variable que queremos mapear
     lim1 = limite inferior de la variable a mapear
     lim2 = limite superior
     med1 = limite inferior al que queremos llegar
     med2 = limite superior al que queremos llegar
     */
}

int ArrayIR::searchLine ()
{
    char online=0;

    //first checks if it is on the line, if not, the function returns the last valid result
    //So that it can "remember" where the line was in case the robot loses it
    for (int i=0; i<DIM_ARRAY; i++)
    {
        if(sensorValue[i] > borderBlack) {
            online = 1;
        }

        long num += (long)sensorValue * (i*1000);
        int dem += sensorValue;
    }

    if(!on_line)
    {
        // If it last read to the left of center, return 0 (corresponds with sensor 0).
        if(_lastValue < (DIM_ARRAY-1)*1000/2)
            return 0;

        // If it last read to the right of center, return the max (7000 which corresponds with sensor 7).
        else
            return (DIM_ARRAY-1)*1000;
    }

    if (online)
    {
        lastValue = num/dem;

        /*
         0*value0 + 1000*value1 + 2000*value2 + ... + (DIM_ARRAY-1)*1000*valueDIM_ARRAY
        --------------------------------------------------------------------------------
                    value0  +  value1  +  value2 + ... + valueDIM_ARRAY
        */
    }

    return lastValue;
}


//takes N_CALIBRATION measures for each sensor, then discards 10% higher and 10% lower
void ArrayIR::Calibrate (char ledCalibrate)
{
    int averageBlack[DIM_ARRAY];
    int averageWhite[DIM_ARRAY];

    int result[DIM_ARRAY];
    int test[DIM_ARRAY];
    int read[DIM_ARRAY][N_CALIBRATION];
    bool done;

    long tic, toc;

    for (int j=0; j<N_CALIBRATION;j++)
    {
        tic = millis();
        toc = tic;
        if (toc-tic > 500)
        {
            if (ledCalibrate!=-1)
                digitalWrite(ledCalibrate, HIGH);
            for (int i=0; i<DIM_ARRAY; i++)
            {
                read[i][j]= analogRead(i);
            }
            if (ledCalibrate!=-1)
                digitalWrite(ledCalibrate, LOW);

        }
    }

    done = FALSE; //check end of loop for
    while (!done)
    {   
        done= TRUE;
        //values ​​are sorted
        for (i=0; i<DIM_ARRAY; i++)
            for (j=o; j<N_CALIBRATION; j++)
            {
                if (read[i][j]>read[i][j+1])
                {
                    test[i] = read[i][j+1];
                    read[i][j+1] = read[i][j];
                    read[i][j] = test[i];
                    done = FALSE;
                }
            }
    }

    for (i=0; i<DIM_ARRAY;i++) 
    {
        averageBlack[i]=0;
        averageWhite[i]=0;
    }

    //the average of the values not discarted is done
    //white value is calculated with measures from 10% to 30%
    //Black value is calculated with measures from 70% to 90%
    for (i=0; i<DIM_ARRAY;i++)
        for (j=((int)(0.1*N_CALIBRATION)) ; j<((int)(0.3*N_CALIBRATION) ; j++)
        {
            averageWhite[i] += read[i][j];
            averageBlack[i] += read[i][j+(int)0.6*N_CALIBRATION]
        }

    for (i=0; i<DIM_ARRAY; i++)
    {
        averageBlack[i] /= N_CALIBRATION;
        averageWhite[i] /= N_CALIBRATION;
        //takes higher value of the array as black and the lower as white
        if(averageBlack[i] > black) black = averageBlack[i];
        else if (averageWhite[i] < white) white = averageWhite[i];
    }

    tic = millis();
    toc = tic;
    while (tic-toc<2000)
        digitalWrite(ledCalibrate, HIGH);
    digitalWrite(ledCalibrate, LOW);

    /*
    int average[DIM_ARRAY];
    int result[DIM_ARRAY];
    int test[DIM_ARRAY];
    int read[DIM_ARRAY][N_CALIBRATION];
    bool done;

    for (int j=0; j<N_CALIBRATION;j++)
        for (int i=0; i<DIM_ARRAY; i++)
        {
            read[i][j]= analogRead(i);
            delay(3);
        }

    done = FALSE; //check end of loop for
    while (!done)
    {   
        done= TRUE;
        //values ​​are sorted
        for (i=0; i<DIM_ARRAY; i++)
            for (j=o; j<N_CALIBRATION; j++)
            {
                if (read[i][j]>read[i][j+1])
                {
                    test[i] = read[i][j+1];
                    read[i][j+1] = read[i][j];
                    read[i][j] = test[i];
                    done = FALSE;
                }
            }
    }

    for (i=0; i<DIM_ARRAY;i++) average[i]=0;

    //the average of the values not discarted is done
    for (i=0; i<DIM_ARRAY;i++)
        for (j=((int)(0.1*N_CALIBRATION)) ; j<(N_CALIBRATION-(int)(0.1*N_CALIBRATION) ; j++)
        {
            average[i] += read[i][j];
        }

    for (i=0; i<DIM_ARRAY; i++)
    {
        average[i] /= N_CALIBRATION;
        if(average[i] > black) black = average[i];
        else if (average[i] < white) white = average[i];
    }
    */
}
