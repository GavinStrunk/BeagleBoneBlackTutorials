/*
//Filename: lcd.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to interface
//		to a 2X16 lcd in 4-bit mode.  This program
//		also uses the libBBB library.
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

#define RS	65
#define E	27
#define D4	46
#define D5	47
#define D6	26
#define D7	44

void configLCD();
void initLCD();
void initCMD(unsigned char cmd);
void writeChar(unsigned char data);
void writeCMD(unsigned char cmd);
void writeString(char* str, int len);

int main()
{
	unsigned char c = 0x30;
	unsigned char buf[] = "This is the terapan";
	int i = 0;

	//configure the pins for the lcd
	configLCD();
	//pauseSec(1);
	printf("lcd configured\n");
	
	//setPinValue(E,OFF);

	//initialize screen and settings
	initLCD();
	printf("LCD init\n");

	pauseSec(2);
	//write hello
	writeChar('H');
	printf("write char H\n");

	/*
	for(i = 0; i < strlen(buf); i++)
		writeChar(buf[i]);
	*/

	//write the string hello to the screen
	writeString(buf, strlen(buf));

	while(1);
	{

	}

	return 0;
}

void configLCD()
{
	//first we need to apply the overlay so the pins are
	//configured to be gpio
	
	FILE *cfg;

	cfg = fopen("/sys/devices/bone_capemgr.9/slots", "w");
	if(cfg == NULL) printf("Slots failed to open\n");
	fseek(cfg,0,SEEK_SET);
	fprintf(cfg, "BBB-LCD");
	fflush(cfg);
	fclose(cfg);

	//now they are gpio so we need to export the pins
	initPin(RS);
	initPin(E);
	initPin(D4);
	initPin(D5);
	initPin(D6);
	initPin(D7);

	//now they are exported so we set the direction to out
	setPinDirection(RS,OUT);
	setPinDirection(E,OUT);
	setPinDirection(D4,OUT);
	setPinDirection(D5,OUT);
	setPinDirection(D6,OUT);
	setPinDirection(D7,OUT);

	//finally set pins to initial state
	setPinValue(E,OFF);
}

void initLCD()
{
	//setup 4-bit mode
	pauseNanoSec(1500000);
	initCMD(0x30);
	pauseNanoSec(5000000);
	initCMD(0x30);
	pauseNanoSec(5000000);
	initCMD(0x30);
	pauseNanoSec(5000000);
	initCMD(0x20);
	
	pauseNanoSec(5000000);
	writeCMD(0x2C);		//Function Set Command
	pauseNanoSec(5000000);
	writeCMD(0x08);		//Display Clear
	pauseNanoSec(2000000);
	writeCMD(0x01);		//Entry Mode Set
	pauseNanoSec(5000000);
	writeCMD(0x06);
	pauseNanoSec(5000000);
	writeCMD(0x0E);
	pauseNanoSec(5000000);

}

void initCMD(unsigned char cmd)
{
	//bring rs low for command
	//pauseNanoSec(500000);
	setPinValue(RS,OFF);
	pauseNanoSec(500000);

	//send highest nibble first
	setPinValue(E,ON);
	setPinValue(D7,((cmd >> 7) & 1));
	setPinValue(D6,((cmd >> 6) & 1));
	setPinValue(D5,((cmd >> 5) & 1));
	setPinValue(D4,((cmd >> 4) & 1));
	pauseNanoSec(500000);
	setPinValue(E,OFF);
	pauseNanoSec(500000);
}

void writeChar(unsigned char data)
{
	//bring rs high for character
	pauseNanoSec(500000);
	setPinValue(RS,ON);
	pauseNanoSec(500000);

	//send highest nibble first
	//setPinValue(E,ON);
	setPinValue(D7,((data >> 7) & 1));
	setPinValue(D6,((data >> 6) & 1));
	setPinValue(D5,((data >> 5) & 1));
	setPinValue(D4,((data >> 4) & 1));
	setPinValue(E,ON);
	pauseNanoSec(500000);
	setPinValue(E,OFF);
	pauseNanoSec(500000);

	//set low nibble
	//setPinValue(E,ON);
	setPinValue(D7,((data >> 3) & 1));
	setPinValue(D6,((data >> 2) & 1));
	setPinValue(D5,((data >> 1) & 1));
	setPinValue(D4,(data & 1));
	setPinValue(E,ON);
	pauseNanoSec(500000);
	setPinValue(E, OFF);

	pauseNanoSec(500000);

}

void writeCMD(unsigned char cmd)
{
	//bring rs low for command
	pauseNanoSec(500000);
	setPinValue(RS,OFF);
	pauseNanoSec(500000);

	//send highest nibble first
	setPinValue(E,ON);
	setPinValue(D7,((cmd >> 7) & 1));
	setPinValue(D6,((cmd >> 6) & 1));
	setPinValue(D5,((cmd >> 5) & 1));
	setPinValue(D4,((cmd >> 4) & 1));
	//setPinValue(E,ON);
	pauseNanoSec(500000);
	setPinValue(E,OFF);
	pauseNanoSec(500000);

	//set low nibble
	setPinValue(E,ON);
	setPinValue(D7,((cmd >> 3) & 1));
	setPinValue(D6,((cmd >> 2) & 1));
	setPinValue(D5,((cmd >> 1) & 1));
	setPinValue(D4,(cmd & 1));
	//setPinValue(E,ON);
	pauseNanoSec(500000);
	setPinValue(E, OFF);

	pauseNanoSec(500000);
}

void writeString(char* str, int len)
{
	int i;

	for(i=0; i < len; i++)
		writeChar(str[i]);
}
