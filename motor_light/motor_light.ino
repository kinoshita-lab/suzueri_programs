#include <stdint.h>
#include <MsTimer2.h>

/**
   configs
*/
constexpr uint32_t TIMER_COUNT = 8000; // [msec]

enum {
	LIGHT = 12,
	BUTTON = 7,
	MOTOR = 9,
};


/**
   vars
*/
bool fire = false;


void timerCallback() {
	fire = false;
	MsTimer2::stop();
	Serial.println("Finished!");
}

void waitSwitchOn()
{
	if (!digitalRead(BUTTON)) {
		fire = true;
		digitalWrite(LIGHT, HIGH);
		MsTimer2::start();
		Serial.println("fired!");	
	} else {
		digitalWrite(LIGHT, LOW);
		analogWrite(MOTOR, 0);
	}
}

void doSwitchOnWorks()
{
	const auto motorSpeed = analogRead(0) >> 2;
	analogWrite(MOTOR, motorSpeed);
}

void setup() {
	pinMode(LIGHT,OUTPUT);                                          
	pinMode(BUTTON,INPUT_PULLUP);
	pinMode(MOTOR, OUTPUT);

	// setting up PWM Timer for faster PWM
	TCCR1B = TCCR1B & 0b11111000;
	TCCR1B |= 1;

	Serial.begin(9600);

	// set up MsTimer2
	MsTimer2::set(8000, timerCallback);
	
}

void loop() {
	if (!fire) {
		waitSwitchOn();
		return;
	}

	doSwitchOnWorks();
} 
