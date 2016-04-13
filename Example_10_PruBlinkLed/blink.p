//
//Filename: blink.p
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to blink an 
//		led connected to the PRU.
//
//Revision History
//	0.1: Wrote the program and tested \GS
//

//
//Copyright (C) 2013 Gavin Strunk
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

.origin 0
.entrypoint START

#define PRU0_ARM_INTERRUPT 19
#define AM33XX

#define GPIO1 0x4804C000
#define GPIO_CLEARDATAOUT 0x190
#define GPIO_SETDATAOUT 0x194

START:
//clear that bit
	LBCO	r0, C4, 4, 4
	CLR	r0, r0, 4
	SBCO	r0, C4, 4, 4

	MOV	r1, 10
BLINK:
	MOV	r2, 7<<2
	MOV	r3, GPIO1 | GPIO_SETDATAOUT
	SBBO	r2, r3, 0, 4

	MOV	r0, 0x00f00000
DELAY:
	SUB	r0, r0, 1
	QBNE	DELAY, r0, 0

	MOV	r2, 7<<22
	MOV	r3, GPIO1 | GPIO_CLEARDATAOUT
	SBBO	r2, r3, 0, 4
	
	MOV	r0, 0x00f00000
DELAY2:
	SUB	r0, r0, 1
	QBNE	DELAY2, r0, 0

	SUB	r1, r1, 1
	QBNE	BLINK, r1, 0

//#ifdef AM33XX
	//Send notification to the Host for program completion
	MOV	R31.b0, PRU0_ARM_INTERRUPT+16
//#else
//	MOV	R31.b0, PRU0_ARM_INTERRUPT
//#endif

HALT
