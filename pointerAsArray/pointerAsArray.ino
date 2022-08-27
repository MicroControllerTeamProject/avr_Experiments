/*
 Name:		pointerAsArray.ino
 Created:	8/12/2022 2:46:09 PM
 Author:	luigi.santagada
*/

#include <SoftwareSerial.h>

SoftwareSerial sf(99, 0);
// the setup function runs once when you press reset or power the board
void setup() {
	sf.begin(9600);
	sf.println(F("RESTART"));
}

int freeRam() {
	extern int __heap_start, * __brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
// the loop function runs over and over again until power down or reset
int ciclo = 0;
int* s;
void loop() {
	sf.println(F("giro"));
	if (freeRam() >= 200)
	{
		s = (int*)malloc(sizeof(int));
		*s = ciclo;
		sf.println(*s);
		ciclo++;
	}
	else
	{
		sf.print(F("p: ")); sf.println(*(s - 4));
		delay(10000);
	}
	
	delay(500);
}
