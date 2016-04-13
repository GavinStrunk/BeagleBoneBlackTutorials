/*
//Filename: pwmwithlib.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 August 2013
//
//Description - This program demonstrates how to turn on
//		the pwm module on pin P8_13 and change period
//		and duty cycle with libBBB.
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

#include "libBBB.h"

#define MGRNUM	8
#define HELPER	14

int main()
{
	initPWM(MGRNUM, P8_13);
	setPWMPeriod(HELPER, P8_13, 200000000);
	setPWMDuty(HELPER, P8_13, 100000000);
	setPWMOnOff(HELPER, P8_13, ON);
	while(1);

	return 0;
}
