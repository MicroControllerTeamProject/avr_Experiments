/*
 Name:		pointerAsArray.ino
 Created:	8/12/2022 2:46:09 PM
 Author:	luigi.santagada
*/

#include <SoftwareSerial.h>

//for some MCUs (i.e. the ATmega2560) there's no definition for RAMSTART
#ifndef RAMSTART
extern int __data_start;
#endif

extern int __data_end;
//extern int __bss_start;
//extern int __bss_end;
extern int __heap_start;
extern int __brkval;
int temp;


//SoftwareSerial Serial(99, 0);
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.println(F("---------------------------------RESTART"));
	readMemoryAtRunTime();
}

int test(char* &i)
{
	String h = "x-------------------------------------------------------------------------------------------------x";
	i = (char*)calloc(h.length(), sizeof(char));	
	Serial.print("Primo : "); Serial.println((int)i);
	int y = (int)i;
	h.toCharArray(i, h.length() + 1, 0);
	Serial.print("Secondo : "); Serial.println((int)i);
	Serial.println("---------------------------------In function");
	readMemoryAtRunTime();
	/*x = i;*/
	/*free((char*)y);*/
	return y;
}



int freeRam() {

	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
// the loop function runs over and over again until power down or reset

int* s;
int* g;

int ciclo = 0;
void loop() {
	char* i;
	int u = test(i);
	Serial.println(i);
	/*free((char*)u);*/
	free(i);
	Serial.println("----------------------------------------In cicle");
	readMemoryAtRunTime();
	return;
	//Serial.println(F("giro"));
	//
	//if (freeRam() >= 150)
	//	/*if (!exit1)*/
	//{
	//	Serial.print(F("mem before :------------ ")); //sf.println(freeRam());
	//	readMemoryAtRunTime();
	//	int k[80];
	//	for (int i = 0; i < 80; i++)
	//	{
	//		k[i] = i;
	//	}
	//	
	//	Serial.print(F("mem after :-------------- "));// sf.println(freeRam());
	//	readMemoryAtRunTime();

	//	delay(10000);

	//	s = (int*)malloc(sizeof(int));
	//	Serial.print(F("mem : ")); Serial.println((int)s, HEX);
	//	if (s != NULL)
	//	{
	//		*s = ciclo;
	//		Serial.print(F("add : ")); Serial.println(*s);
	//		ciclo++;

	//	/*	g = (int*)malloc(1 * sizeof(int));
	//		if (g != NULL)
	//		{
	//			*g = 19;
	//		}*/
	//		
	//	}
	//}
	//else
	//{
	///*	int k[80];
	//	for (int i = 0; i < 80; i++)
	//	{
	//		k[i] = i;
	//		sf.println(k[i]);
	//	}*/
	//	
	//	Serial.print(F("p: ")); Serial.println(*(s - 0));
	//	free(s);
	//	for (int i = 70; i >= 0; i-=2)
	//	{
	//		Serial.println((int)(s-i),HEX);
	//		free(s - i);
	//	}
	//	ciclo = 0;
	//	delay(2000);
	//}

	//delay(100);
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
	serialPrint("SRAM and .data space start: ", (int)&__data_start);
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

}

//print function
void serialPrint(String tempString, int tempData) {
	Serial.print(tempString);
	Serial.print(tempData, DEC);
	Serial.print(" $");
	Serial.println(tempData, HEX);
}
