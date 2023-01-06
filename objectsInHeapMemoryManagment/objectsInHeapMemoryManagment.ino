/*
 Name:		objectsInHeapMemoryManagment.ino
 Created:	1/6/2023 5:20:38 PM
 Author:	luigi.santagada
*/

#ifndef RAMSTART
extern int __data_start;
#endif

extern int __data_end;
extern int __bss_start;
extern int __bss_end;
extern int __heap_start;
extern int __brkval;
int temp;

#include "Person.h"

uint8_t numberOfPersons = 10;

Person* person;
// the setup function runs once when you press reset or power the board
void setup() {
	person = (Person*)calloc(numberOfPersons, sizeof(Person));
	int startAddress = (int)person;
	*person = Person("Luigi","Santagada");
	person++;
	*person = Person("Anna", "Bellino");
	person--;
	Serial.println(person->name);
	person++;
	Serial.println(person->name);
	person--;
	free((Person*)startAddress);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.print("memory now is : "); Serial.println(freeRam());
	Serial.println("insert number of persons : ");
	while (Serial.available() == 0){	
	}
	if (Serial.available() > 0)
	{
		person = (Person*)calloc(Serial.readString().toInt(), sizeof(Person));
		Serial.println("persons inserted : ");
	}
	Serial.print("memory now is: "); Serial.println(freeRam());

	Serial.println("press 1 to restart without free memory:");
	Serial.println("press 2 to restart with free memory:");
	while (Serial.available() == 0) {
	}
	if (Serial.available() > 0)
	{
		if (Serial.readString().indexOf("2") != -1)
		{
			Serial.println("pulizia");
			free(person);
		}
	}
}
		

int freeRam() {
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
