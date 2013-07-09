#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>

#include "wiringPiSPI.h"
#include "wiringPi.h"

unsigned long long  	*a,*b;
unsigned long long 	i,j;
unsigned short 		m,n;

int kkk[1]={0x99};

void main()
{
	m = 0x00aa;
	n = 0x0000;
	i = (unsigned long long)m;
	j = (unsigned long long)n;
	a = &i;
	b = &j;
	wiringPiSPISetup(1,1000000);
	
	while(1)
	{
		wiringPiSPIDataRW(1,a,b,sizeof(m));
	}
}
