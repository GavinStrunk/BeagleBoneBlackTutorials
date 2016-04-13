/*
//Filename: i2c.c
//Version : 0.1
//
//Project : Argonne National Lab - Forest
//Author  : Gavin Strunk
//Contact : gavin.strunk@gmail.com
//Date    : 14 June 2013
//
//Description - This program demonstrates how to use
//		the i2c bus and was verified with a
//		sparkfun capacitive keypad.
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
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

void pauseSec(int sec);

int main()
{
	int fd,i;
	int addr = 0x68;
	unsigned char buf[2] = {0x00, 0b00001000};
	char buf2[10] = {0};

	for(i=0;i<10;i++)
		printf("%x\n",buf2[i]);

	fd = open("/dev/i2c-1", O_RDWR);
	if(fd < 0) printf("i2c failed to open\n");

	if(ioctl(fd, I2C_SLAVE, addr) < 0)
		printf("failed to acquire bus\n");

	if(write(fd,buf,1) != 1)
	{
		printf("i2c write failed\n");
	//	if(write(fd,buf,2) != 2)
	//		printf("i2c write failed again\n");
	}

	buf[0] = 0x06; 	
	buf[1] = 0x2C;
	if(write(fd,buf,2) != 2)	
		printf("i2c write failed\n");

	buf[0] = 0x00;
	if(write(fd,buf,1) != 1)
		printf("i2c write failed\n");

	//while(1)
	//{
		//if(write(fd,&buf,1) != 1)
		//	printf("i2c write failed\n");
		
		if(read(fd,&buf2,8) != 8)
			printf("i2c read failed\n");
		
		for(i=0;i<8;i++)
			printf("Register %i: %x\n",i, buf2[i]);

		buf[0] = 0x08;
		if(write(fd,buf,1) != 1)
			printf("i2c write failed\n");
		if(read(fd,&buf2, 1) != 1)
			printf("i2c read failed\n");
		printf("Register 8: %x\n",buf2[0]);

		buf[0] = 0x09;
		if(write(fd,buf,1) != 1)
			printf("i2c write failed\n");
		if(read(fd,&buf2,1) != 1)
			printf("i2c read failed\n");
		printf("Register 9: %x\n",buf2[0]);


	//	if(buf2[0] > 0)
	//		printf("value: %i\n",buf2[0]);
		//for(i=0; i<9; i++)
		//       	printf(" %d\n",buf2[i]);
		//pauseSec(1);
	//}


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
