int motor1fwd = 5;
int motor1bck = 6;
int motor2fwd = 9;
int motor2bck = 10;
int sensorfwd = A0;
int sensorright = A1;
int dist_min = 10;

void mover(int v1, int v2)
{
}
int leer(int sensor)
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

 	mover (50, 50);
}

void loop()
{
	if (leer(sensorfwd) < dist_min)
	{
		if (leer(sensorright) < dist_min)
			mover (-50, 50);
		else
			mover (50, -50);
	}

	else if (leer(sensorright) < dist_min)
		mover (0, 50);

	else if (leer(sensorright) > dist_min)
		mover (50, 0);
}
