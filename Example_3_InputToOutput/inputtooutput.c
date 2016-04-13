/*
//Filename: in2out.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to read in
//		a digital input and send it to an led.
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
	FILE *in,*indir,*inval,*outdir,*outval;
	int value;

	in = fopen("/sys/class/gpio/export", "w");
	fseek(in,0,SEEK_SET);
	fprintf(in,"%d",45);
	fflush(in);
	fseek(in,0,SEEK_SET);
	fprintf(in,"%d",47);
	fflush(in);

	indir = fopen("/sys/class/gpio/gpio47/direction", "w");
	fseek(indir,0,SEEK_SET);
	fprintf(indir,"in");
	fflush(indir);

	outdir = fopen("/sys/class/gpio/gpio45/direction", "w");
	fseek(outdir,0,SEEK_SET);
	fprintf(outdir,"out");
	fflush(outdir);

	inval = fopen("/sys/class/gpio/gpio47/value", "r");
	outval = fopen("/sys/class/gpio/gpio45/value", "w");

	while(1)
	{
		fseek(inval,0,SEEK_SET);
		fscanf(inval,"%d",&value);
		fflush(inval);
		fseek(outval,0,SEEK_SET);
		fprintf(outval,"%d",value);
		fflush(outval);
	}

	fclose(in);
	fclose(indir);
	fclose(inval);
	fclose(outdir);
	fclose(outval);

	return 0;
}
