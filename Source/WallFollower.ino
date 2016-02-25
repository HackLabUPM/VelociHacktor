int sensorfwd = A0;
int sensorright = A1;
int min_distance = 10;

void move(int v1, int v2)
{
}
int readSensor(int sensor)
{
	int lectura, cm;
	lectura = analogRead (sensor);
	cm = pow(3027.4 / lectura, 1.2134);
	return cm;
}

void setup()
{
 	pinMode (motor1fwd, OUTPUT);
 	pinMode (motor1bck, OUTPUT);
 	pinMode (motor2fwd, OUTPUT);
 	pinMode (motor2bck, OUTPUT);
 	Serial.begin(9600);
}

void loop()
{
	//If there's a wall in front, it tries to turn right, if there's another wall to the right, it turns to the left
	if (readSensor(sensorfwd) < min_distance)
	{
		if (readSensor(sensorright) < min_distance)
			move (0, 50);
		else
			move (50, 0);
	}

	//If there is a right wall, it keeps going fordwards, otherwise, it turns right
	else if (readSensor(sensorright) < min_distance)
		move (0, 50);

	else if (readSensor(sensorright) > min_distance)
		move (50, 0);
}
