/*
//Filename: blinkusrwithlib.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 August 2013
//
//Description - This is an example program that demonstrates
//	how to blink one of the user leds on the beaglebone
//	black using the libBBB library.
//
//Revision History
//	0.1: Wrote the pauseSec function and the basic program to 
//		blink the led at 0.5 Hz.  6/28 \GS
*/

/*Copyright (C) 2013 Gavin Strunk

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//Includes
#include "libBBB.h"

int main()
{

	while(1)
	{
		setUsrLedValue(USR3, ON);
		pauseSec(1);
		setUsrLedValue(USR3, OFF);
		pauseSec(1);
	}

	return 0;
}

