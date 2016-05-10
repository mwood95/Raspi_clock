#include <wiringPiI2C.h>
#include <stdio.h>

#define CLEAR 0x51



int main(void)
{
	int i;	
	static int fd, result;
	char time[] = "Hello";

	
	fd = wiringPiI2CSetup(0x28);
	printf("Init result: %d \n", fd);
	
	wiringPiI2CWriteReg8(fd, 0xFE, CLEAR);
	delay(5);
	for(i = 0; i < sizeof(time); i++)
	{
	wiringPiI2CWriteReg8(fd, 0xFE, time[i]);
	delay(5);
	}
	return 0;
}

