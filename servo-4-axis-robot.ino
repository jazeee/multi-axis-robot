#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             100

void setup() {
  Serial.begin(115200);
  Serial.println("16 channel PWM test!");

  pwm1.begin();
  pwm1.setPWMFreq(FREQUENCY);  // This is the maximum PWM frequency
}

int startingPositions[] = {80, 70, 100, 140};
int endingPositions[] = {110, 100, 140, 120};
void loop() {
	Serial.println("Starting");
// 0 left, right
// 1 up down
// 2 reach
// 3 grabber
//	pwm1.setPWM(0, 0, pulseWidth(80));
//	pwm1.setPWM(1, 0, pulseWidth(70));
//	pwm1.setPWM(2, 0, pulseWidth(100));
//	pwm1.setPWM(3, 0, pulseWidth(140));//closed
	int* positions1 = startingPositions;
	moveTo(positions1);
	delay(500);
	Serial.println("Moving");
//	pwm1.setPWM(0, 0, pulseWidth(110));
//	pwm1.setPWM(1, 0, pulseWidth(100));
//	pwm1.setPWM(2, 0, pulseWidth(140));
//	pwm1.setPWM(3, 0, pulseWidth(120));// open
	int *positions2 = endingPositions;
	moveTo(positions2);
	delay(500);
}


int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}

int steps = 20;
int* lastPositions = endingPositions;
void moveTo(int positions[]) {
	for(int step = 0; step < steps; step++) {
		for(int axis = 0; axis < 4; axis++) {
			int angle = map(step, 0, steps, lastPositions[axis], positions[axis]);
			pwm1.setPWM(axis, 0, pulseWidth(angle));
		}
		delay(5);
	}
	lastPositions = positions;
}
