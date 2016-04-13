/*
//Filename: pwm.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to turn on
//		the pwm module on pin P8_13 and change period
//		and duty cycle.
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
	FILE *pwm,*duty,*period,*run;

	pwm = fopen("/sys/devices/bone_capemgr.9/slots", "w");
	fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"am33xx_pwm");
	fflush(pwm);
	
	fprintf(pwm,"bone_pwm_P8_13");
	fflush(pwm);

	period = fopen("/sys/devices/ocp.2/pwm_test_P8_13.14/period", "w");
	fseek(period,0,SEEK_SET);
	fprintf(period,"%d",200000000);
	fflush(period);

	duty = fopen("/sys/devices/ocp.2/pwm_test_P8_13.14/duty", "w");
	fseek(duty,0,SEEK_SET);
	fprintf(duty,"%d",100000000);
	fflush(duty);

	run = fopen("/sys/devices/ocp.2/pwm_test_P8_13.14/run", "w");
	fseek(run,0,SEEK_SET);
	fprintf(run,"%d",0);
	fflush(run);

	fseek(run,0,SEEK_SET);
	fprintf(run,"%d",1);
	fflush(run);
	while(1);

	fclose(pwm);
	fclose(duty);
	fclose(period);
	fclose(run);
	return 0;
}
