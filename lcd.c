#include <wiringPiI2C.h>
#include <stdio.h>

#define CLEAR 0x51



int main(void)
{
	int i, fd, result;
	char id[] = "Michael";
	fd = wiringPiI2CSetup(0x28);
	printf("Init result: %d \n", fd);
	wiringPiI2CWriteReg8(fd, 0xFE, CLEAR);
	delay(5);
//	for(i = 0; i < sizeof(id); i++)
//	{
//		wiringPiI2CWriteReg16(fd, 0xFE, id[i]);
//		delay(5);
//		wiringPiI2CWriteReg8(fd, 0xFE, 0x4A);
//		delay(5);
//	}
	return 0;
}

