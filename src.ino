//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __|
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/
//
// Board Computer
//
// Made by roberto debarba
// License: GPL 3.0

const int ledPins[] = { 8, 7, 6, 5 };
const int ledRgbPins[] = { 3, 2, 1 };
const int buttonPins[] = { 12, 11, 10, 9 };
int buttonStatus[] = { 0, 0, 0, 0 };

void setupEntries() {
	for (int i = 0; i < 4; i++) {
		pinMode(buttonPins[i], INPUT);
		pinMode(ledPins[i], OUTPUT);
	}

	for (int i = 0; i < 3; i++) {
		pinMode(ledRgbPins[i], OUTPUT);
	}
}

void setup() {
	setupEntries();
}

void startCar() {
	digitalWrite(ledRgbPins[0], LOW);
	digitalWrite(ledRgbPins[1], LOW);
	digitalWrite(ledRgbPins[2], HIGH);
}

void stopCar() {
	digitalWrite(ledRgbPins[0], HIGH);
	digitalWrite(ledRgbPins[1], LOW);
	digitalWrite(ledRgbPins[2], LOW);
}

boolean isPressed(int buttonKey) {
	return (buttonStatus[buttonKey] == HIGH);
}

void invertButtonStatus(int buttonKey) {
	if (isPressed(buttonKey) == HIGH) {
		buttonStatus[buttonKey] = LOW;
	} else {
		buttonStatus[buttonKey] = HIGH;
	}
}
void checkButton(int buttonKey, int buttonRead) {
	if (buttonRead == HIGH) {
		invertButtonStatus(buttonKey);
		delay(500);
	}
}

void readEntries() {
	for (int i = 0;	i < 4; i++) {
		checkButton(i, digitalRead(buttonPins[i]));

		if (buttonStatus[i] == HIGH) {
			digitalWrite(ledPins[i], HIGH);
		} else {
			digitalWrite(ledPins[i], LOW);
		}
	}
}

boolean checkStart() {
	const int PORTA = 0;
	const int CINTO = 1;
	const int MARCHA = 2;
	const int EMBREAGEM = 3;

	return (isPressed(PORTA) && isPressed(CINTO) && !isPressed(MARCHA)
		|| isPressed(PORTA) && isPressed(CINTO) && isPressed(MARCHA) && isPressed(EMBREAGEM));
}

void loop() {
	readEntries();

	if (checkStart()) {
		startCar();
	} else {
		stopCar();
	}
}

