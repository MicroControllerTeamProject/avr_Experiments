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
	/*float** f;
	f = (float**)malloc(sizeof(float));
	sf.println();
	sf.println((int)f);
	f[0] = new float(1.4);
	f[1] = new float(1.9);
	int* r, * g;
	r = (int*)malloc(sizeof(int));
	*r++;
	sf.println((int)r);
	f[2] = new float(1.7);
	f[3] = new float(1.3);
	sf.println();

	sf.println((int)f[0]);
	sf.println((int)f[1]);
	sf.println((int)f[2]);
	sf.println((int)f[3]);

	sf.println(*f[0]);
	sf.println(*f[1]);
	sf.println(*f[2]);
	sf.println(*f[3]);
	return;*/

	int a, b, c;
	sf.println();
	sf.println((int)&a);
	sf.println((int)&b);
	sf.println((int)&c);

	int *d, *e, *f;
	d = (int*)malloc(sizeof(int));
	e = (int*)malloc(sizeof(int));
	f = (int*)malloc(sizeof(int));
	*d = 1;
	*e = 2;
	*f = 3;
	sf.println();
	sf.println((int)d);
	sf.println((int)e);
	sf.println((int)f);

	free(d);
	free(e);
	free(f);

	sf.println(*d);
	sf.println(*(d + 2 * (sizeof(int))));
	sf.println(*f);

	

	/*int *i,*i1,*i2;
	i = (int*)malloc(sizeof(int));
	i1 = (int*)malloc(sizeof(int));
	i2 = (int*)malloc(sizeof(int));
	*i = 10;
	sf.println();
	sf.println((int)i);
	sf.println((int)i1);
	sf.println((int)i2);
	*i = *i + 1;
	sf.println(*i);
	return;


	int *a = new int(16);
	int *b = new int(15);
	int* c = new int(15);
	sf.println();
	sf.println(F("Stack address"));
	sf.println((int)&a);
	sf.println((int)&b);
	sf.println((int)&c);
	sf.println(F("Heap address"));
	sf.println((int)a);
	sf.println((int)b);
	sf.println((int)c);*/
	/*setInt(*a);
	sf.println(*a);*/
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}

void setInt(int &a)
{
	sf.println((int)&a);
	a++;
	sf.println(a);
	//int *b = new int();// = new int();
	//b = &a;
	//*b++;
}
