/*
 Name:		memoryTests.ino
 Created:	8/29/2022 1:54:32 PM
 Author:	luigi.santagada
*/

//#include <SoftwareSerial.h>

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


struct Person
{
	int age;
	int year;
	char* name;
	char* surname;
};

Person* person2;
int numberOfObjects = 5;

int count = 0;

int startAddress = 0;
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.println(F(""));
	Serial.println(F("RESTART"));
	person2 = (Person*)calloc(numberOfObjects, sizeof(Person));
	startAddress = (int)person2;
}

int* t1 = new int(50);
int* t2 = new int(50);
int* t3 = new int(50);
int* t4 = new int(50);
int* t5 = new int(50);

// the loop function runs over and over again until power down or reset
void loop() {

	Serial.print(F("Object ....................................... : ")); Serial.println(count);

	if (person2 == NULL)
	{
		Serial.println("no memory ");
		delay(10000);
		return;
	}

	*person2 = Person();

	person2->age = 52 + count;

	person2->year = 1970;

	person2->name = "Luigi";

	person2->surname = "Santagada";

	Serial.print(F("person with age ")); Serial.print(person2->age); Serial.print(person2->surname); Serial.print(F(" address: ")); Serial.println((int)person2);

	if (count <= (numberOfObjects - 2)) { person2++; }

	//readMemoryAtRunTime();

	if (count == (numberOfObjects - 1))
	{
		count = 0;

		Serial.println(F("stop"));

		int tempRam = freeRam();

		Serial.print(F("Free memory at the moment: ")); Serial.println(tempRam);

		free((Person*)startAddress);

		numberOfObjects = 5;

		delay(5000);

		/*for (int i = 0; i < numberOfObjects; i++)
		{
			free((Person*)((int)person2 - (sizeof(Person) * i)));
			Serial.print(F("free address ")); Serial.println((int)person2 - (sizeof(Person) * i));
		}*/

		//realloc(person2, 10);

		person2 = (Person*)calloc(numberOfObjects, sizeof(Person));

		startAddress = (int)person2;

	//https://www.geeksforgeeks.org/g-fact-66/

		delay(1000);
	}
	else
	{
		count++;
	}

	
	
}




//Person* person1;

//void createPerson()
//{
//
//	person2 = new Person();
//
//	person2->name = F("Luigi....................................................................");
//
//	Serial.println((int)person2);
//
//	//person2 = (Person*)malloc(sizeof(Person));
//
//	//person2 = new Person();
//
//	//person2->name = F("Luigi....................................................................");
//
//	//Serial.println((int)person2);
//
//	/*delete((Person*)460);
//	delete((Person*)558);*/
//}


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
	Serial.println(F("----------------------------------------------"));
}

void serialPrint(String tempString, int tempData) {
	Serial.print(tempString);
	Serial.print(tempData, DEC);
	Serial.print(" $");
	Serial.println(tempData, HEX);
}


