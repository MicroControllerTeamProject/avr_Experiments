/*
 Name:		function_pointer.ino
 Created:	8/8/2022 12:40:38 AM
 Author:	luigi.santagada
*/
#include <SoftwareSerial.h>

SoftwareSerial sf(99, 0);

int f(int a, int b,int (*mathOperations)(int a,int b))
{
	return (*mathOperations)(a, b);
}

int sum(int a, int b)
{
	return a + b;
}

int  multi(int a, int b)
{
	return a * b;
}

// the setup function runs once when you press reset or power the board
void setup() {
	sf.begin(9600);
	sf.print("sum :"); sf.println(f(1,2,sum));
	sf.print("multi :"); sf.println(f(1, 2, multi));
	
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
