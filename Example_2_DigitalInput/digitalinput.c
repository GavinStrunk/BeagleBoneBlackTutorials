/*
//Filename: digin.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to read a
//		digital input on P8_15. 
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

int main()
{
	FILE *in,*indir,*inval;
	int value,i;

	in = fopen("/sys/class/gpio/export", "w");
	fseek(in,0,SEEK_SET);
	fprintf(in,"%d",47);
	fflush(in);

	indir = fopen("/sys/class/gpio/gpio47/direction", "w");
	fseek(indir,0,SEEK_SET);
	fprintf(indir,"in");
	fflush(indir);

	while(1)
	{
		inval = fopen("/sys/class/gpio/gpio47/value", "r");
		fseek(inval,0,SEEK_SET);
		fscanf(inval,"%d",&value);
		fclose(inval);

		printf("value: %d\n",value);
		for(i=0; i < 100000; i++);
	}

	fclose(in);
	fclose(indir);
	return 0;
}
