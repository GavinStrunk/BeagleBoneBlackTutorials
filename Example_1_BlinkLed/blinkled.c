/*
//Filename: blinkled.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to blink an 
//		led connected to pin P8_11.
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
	FILE *io,*iodir,*ioval;

	io = fopen("/sys/class/gpio/export", "w");
	fseek(io,0,SEEK_SET);
	fprintf(io,"%d",45);
	fflush(io);

	iodir = fopen("/sys/class/gpio/gpio45/direction", "w");
	fseek(iodir,0,SEEK_SET);
	fprintf(iodir,"out");
	fflush(iodir);

	ioval = fopen("/sys/class/gpio/gpio45/value", "w");
	fseek(ioval,0,SEEK_SET);

	while(1)
	{
		fprintf(ioval,"%d",1);
		fflush(ioval);
		pauseSec(1);
		fprintf(ioval,"%d",0);
		fflush(ioval);
		pauseSec(1);
	}

	fclose(io);
	fclose(iodir);
	fclose(ioval);
	return 0;
}

void pauseSec(int sec)
{
	time_t now,later;

	now = time(NULL);
	later = time(NULL);

	while((later - now) < (double)sec)
		later = time(NULL);
}
