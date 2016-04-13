/*
//Filename: analogin.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to read
//		the onboard ADC channel 1 and display
//		the value to terminal.
//
//Revision History
//	0.1: Wrote the program and tested \GS
*/

/*
Copyright (C) 2013 Gavin Strunk

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <time.h>

void pauseSec(int sec);

int main()
{
	FILE *ain,*aval,*aval1;
	int value,value1,i;

	ain = fopen("/sys/devices/bone_capemgr.8/slots", "w");
	fseek(ain,0,SEEK_SET);
	fprintf(ain,"cape-bone-iio");
	fflush(ain);

	while(1)
	{
		aval = fopen("/sys/devices/ocp.2/helper.14/AIN0", "r");
		fseek(aval,0,SEEK_SET);
		fscanf(aval,"%d",&value);
		fclose(aval);

		for(i = 0; i<1000000;i++);
		
		aval1 = fopen("/sys/devices/ocp.2/helper.14/AIN1","r");
		fseek(aval1,0,SEEK_SET);
		fscanf(aval1,"%d",&value1);
		fclose(aval1);
		printf("value: %d  value1: %d\n",value,value1);
		for(i = 0; i<1000000;i++);
	}

	fclose(ain);
	return 0;
}

void pauseSec(int sec)
{
	time_t now,later;

	now = time(NULL);
	later = time(NULL);

	while((later - now) < (double) sec)
		later = time(NULL);
}
