
int buttonPin = 12;
int GreenLed = 3;
int RedLed = 2;

bool isButtonPressed = false;
unsigned long buttonPressedTime = 0;
unsigned long currentTime = 0;



bool flipflop = false;
unsigned long flipflopTime = 0;
unsigned long latestflipflopTime = 0;

unsigned long flipflopDelayTime = 200; // dalam mili second
int flipflopCount = 4; // kedip berapa kali untuk led hijau
int currentflipflopCount = 0;

void setup() {
	pinMode(buttonPin, INPUT_PULLUP);
	// Define pin #13 as output, for the LED
	pinMode(GreenLed, OUTPUT);
	pinMode(RedLed, OUTPUT);
	isButtonPressed = false;
}

void loop() {
	currentTime = millis();
	int buttonValue = digitalRead(buttonPin);

	if (buttonValue == LOW) {
		digitalWrite(RedLed, LOW);
		if (!isButtonPressed) {
			isButtonPressed = true;
			flipflop = false;
			latestflipflopTime = currentTime;
			currentflipflopCount = 0;
		}
		if (currentflipflopCount <= flipflopCount) {
			if (currentTime - latestflipflopTime > flipflopDelayTime) {
				flipflop = !flipflop;
				latestflipflopTime = currentTime;
				if (flipflop)
					currentflipflopCount++;
			}
			if (flipflop)
				digitalWrite(GreenLed, HIGH);
			else
				digitalWrite(GreenLed, LOW);
		}
		else {
			digitalWrite(GreenLed, HIGH);
		}
	}
	else {
		digitalWrite(GreenLed, LOW);
		if (isButtonPressed) {
			isButtonPressed = false;
			flipflop = false;
			latestflipflopTime = currentTime;
		}
		if (currentTime - latestflipflopTime > flipflopDelayTime) {
			flipflop = !flipflop;
			latestflipflopTime = currentTime;
		}
		if (flipflop)
			digitalWrite(RedLed, HIGH);
		else
			digitalWrite(RedLed, LOW);
	}
}