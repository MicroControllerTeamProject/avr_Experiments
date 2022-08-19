/*
 Name:		function_pointer.ino
 Created:	8/8/2022 12:40:38 AM
 Author:	luigi.santagada
*/
#include <SoftwareSerial.h>
#include "mathOperations.h"

SoftwareSerial sf(99, 0);

int f(int a, int b,int (*mathOper)(int a,int b))
{
	int result = (*mathOper)(a, b);
	//execute other functions with result
	return result;
}

//int sum(int a, int b)
//{
//	return a + b;
//}
//
//int  multi(int a, int b)
//{
//	return a * b;
//}

// the setup function runs once when you press reset or power the board
void setup() {
	sf.begin(9600);
	mathOperations *mod = new mathOperations();
	sf.print("key istance :"); sf.println(mod->key());
	sf.print("sum istance :"); sf.println(mod->sum(1,2));
	sf.print("sum :"); sf.println(f(1,2, mathOperations::sum));
	sf.print("multi :"); sf.println(f(1, 2, mathOperations::add));
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
