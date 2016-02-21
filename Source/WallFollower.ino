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

 	move (50, 50);
}

void loop()
{
	if (readSensor(sensorfwd) < min_distance)
	{
		if (readSensor(sensorright) < min_distance)
			move (-50, 50);
		else
			move (50, -50);
	}

	else if (readSensor(sensorright) < min_distance)
		move (0, 50);

	else if (readSensor(sensorright) > min_distance)
		move (50, 0);
}
