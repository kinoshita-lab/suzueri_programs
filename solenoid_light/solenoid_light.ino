#include <stdint.h>
#include <MsTimer2.h>

/**
   configs
*/
constexpr uint32_t TIMER_COUNT = 8000; // [msec]

enum {
	LIGHT = 12,
	BUTTON = 7,
	SOLENOID = 9,
};


/**
   vars
*/
bool fire = false;
bool solenoidMoved = false;


void timerCallback() {
	fire = false;
	solenoidMoved = false;
	
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
		digitalWrite(SOLENOID, 0);
	}
}

void doSwitchOnWorks()
{
	if (!solenoidMoved) {
		digitalWrite(SOLENOID, HIGH);
		delay(100);
		solenoidMoved = true;
	}
	
	digitalWrite(SOLENOID, LOW);
}

void setup() {
	pinMode(LIGHT,OUTPUT);                                          
	pinMode(BUTTON,INPUT_PULLUP);
	pinMode(SOLENOID, OUTPUT);

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
