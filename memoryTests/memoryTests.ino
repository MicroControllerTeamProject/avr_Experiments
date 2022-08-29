/*
 Name:		memoryTests.ino
 Created:	8/29/2022 1:54:32 PM
 Author:	luigi.santagada
*/

#include <SoftwareSerial.h>

//for some MCUs (i.e. the ATmega2560) there's no definition for RAMSTART
#ifndef RAMSTART
extern int __data_start;
#endif

extern int __data_end;
extern int __bss_start;
extern int __bss_end;
extern int __heap_start;
extern int __brkval;
int temp;

SoftwareSerial sf(99, 0);

// the setup function runs once when you press reset or power the board
void setup() {
	sf.begin(9600);
	sf.println(F(""));
	sf.println(F("RESTART"));
}

int* s;
// the loop function runs over and over again until power down or reset
void loop() {
	/*k[0] = 0;*/
	/*s = (int*)malloc(sizeof(int));
	*s = 10;
	sf.print(F("malloc : ")); sf.println((int)s);
	free(s);*/
	readMemoryAtRunTime();
	test();
	readMemoryAtRunTime();
	delay(1000);
}

void test()
{
	int k[40] = {};
	k[0] = 0;
}

int freeRam() {
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void readMemoryAtRunTime()
{
	//this is necessary to wait for the Arduino Leonardo to get the serial interface up and running
#if defined(__ATmega32U4__)
	while (!Serial);
#else
	delay(2000);
#endif

#ifndef RAMSTART
	serialPrint(F("SRAM and .data space start: "), (int)&__data_start);
#else
	serialPrint(F("SRAM and .data space start: "), RAMSTART);
#endif
	serialPrint(F(".data space end/.bss start: "), (int)&__data_end); //same as "(int)&__bss_start)"
	serialPrint(F(".bss space end/HEAP start: "), (int)&__heap_start); //same as "(int)&__bss_end);"
	serialPrint(F("HEAP end: "), (int)__brkval);
	int tempRam = freeRam();
	serialPrint(F("STACK start: "), temp);
	serialPrint(F("STACK and SRAM end: "), RAMEND);
	serialPrint(F("Free memory at the moment: "), tempRam);
	sf.println(F("----------------------------------------------"));
}

void serialPrint(String tempString, int tempData) {
	sf.print(tempString);
	sf.print(tempData, DEC);
	sf.print(" $");
	sf.println(tempData, HEX);
}


