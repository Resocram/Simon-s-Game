/*
 * Author: Marco Ser   
 * Student Number:  44403061 
 * Lab Section:     L1Q 
 * Date:             12/1/2018 6:35:20 PM
 *           
 * Purpose:  To create the Simon's Game
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#define ON 1 
#define OFF 0 
#define LED0 0 
#define LED1 1 
#define LED2 2
#define LED3 3
#define PUSHBUTTON0 0 
#define PUSHBUTTON1 1
#define PUSHBUTTON2 2
#define PUSHBUTTON3 3
#define GAMESIZE 5

#include <stdio.h>
#include <stdlib.h>
#include <DAQlib.h>
#include <time.h>
#include <Windows.h>
int randInt(int lower, int upper);
void generateSequence(int length, int data[]);
void runSimon(void);
void LightUpLED(int array[], int size);
int PushButtonCheck(int array[], int size);
void LEDLightControl(int toggle0, int toggle1, int toggle2, int toggle3);
void victory(void);
void defeat(void);
int main(void)
{
	int setupNum;
	printf("Please enter a number(0 for hardware)(6 for simulator):\n");
	scanf("%d", &setupNum);
	if (setupDAQ(setupNum) == TRUE) {
		runSimon();

	}
	else {
		printf("Error initializing DAQ.\n");
	}

	return 0;
}

void runSimon(void) {
	srand((unsigned)time(NULL));
	int array[GAMESIZE];
	while (continueSuperLoop() == TRUE) {
		generateSequence(GAMESIZE, array);
		int level = 1;
		while (level <= GAMESIZE) {
			LightUpLED(array, level);
			int value = PushButtonCheck(array, level);

			if (value == 1) {
				level += 1;
				Sleep(500);
			}
			else {
				defeat();
				level = 1;
				break;
			}

		}
		if (level-1 == GAMESIZE) {
			victory();
		}
	}
}
void LightUpLED(int array[], int size) {
	int index;
	for (index = 0; index < size; index++) {
		digitalWrite(array[index], ON);
		Sleep(1000);
		digitalWrite(array[index], OFF);
		Sleep(100);
	}
}
int ReadButton() {
	
	while (TRUE) {
		if (digitalRead(PUSHBUTTON0) == TRUE) {
			return 0;
		}
		else if (digitalRead(PUSHBUTTON1) == TRUE) {
			return 1;
		}
		else if (digitalRead(PUSHBUTTON2) == TRUE) {
			return 2;
		}
		else if (digitalRead(PUSHBUTTON3) == TRUE) {
			return 3;
		}
	}
}
int PushButtonCheck(int array[], int size) {
	int index = 0;
	int buttonPressed = -1;
	while (index < size) {
		buttonPressed = ReadButton();
		digitalWrite(buttonPressed, ON);
		Sleep(500);
		LEDLightControl(OFF, OFF, OFF, OFF);
		if (buttonPressed != array[index]) {
			return 0;
		}
		else {
			index++;
		}

	}
	return 1;
}


void LEDLightControl(int toggle0, int toggle1, int toggle2, int toggle3) {
	digitalWrite(LED0, toggle0);
	digitalWrite(LED1, toggle1);
	digitalWrite(LED2, toggle2);
	digitalWrite(LED3, toggle3);
}

void victory(void) {
	int index;
	for (index = 0; index < 3; index++) {
		digitalWrite(LED0, ON);
		Sleep(500);
		digitalWrite(LED0, OFF);
		Sleep(500);
	}

}

void defeat(void) {
	int index;
	for (index = 0; index < 3; index++) {
		digitalWrite(LED1, ON);
		Sleep(500);
		digitalWrite(LED1, OFF);
		Sleep(500);
	}

}

int randInt(int lower, int upper) {
	int random = rand()%(upper-lower+1) + lower;
	return random;
}
void generateSequence(int length, int data[]) {
	int index;
	for (index = 0; index < length; index++) {
		data[index] = randInt(0, 3);
	}
}