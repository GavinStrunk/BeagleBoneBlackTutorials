/*
//Filename: blink.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to blink an 
//		led using the PRU.
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

#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#define PRU_NUM	0
#define AM33XX

int main()
{
	unsigned int ret;
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

	printf("INFO: Starting blink example\n");

	//initialize pru
	prussdrv_init();

	//open pru interrupt
	ret = prussdrv_open(PRU_EVTOUT_0);
	if(ret)
	{
		printf("prussdrv_open failed\n");
		return ret;
	}

	//get the interrupt initialized
	prussdrv_pruintc_init(&pruss_intc_initdata);

	//execute the example
	printf("Executing the example\n");
	prussdrv_exec_program(PRU_NUM, "./blink.bin");

	//wait until PRU0 has finished
	printf("waiting for PRU to complete\n");
	prussdrv_pru_wait_event(PRU_EVTOUT_0);
	printf("PRU completed\n");
	prussdrv_pru_clear_event(PRU0_ARM_INTERRUPT);

	//disable pru and close memory mapping
	prussdrv_pru_disable(PRU_NUM);
	prussdrv_exit();

	return 0;
}
