/*
 * wiringPiSPI.c:
 *	Simplified SPI access routines
 *	Copyright (c) 2012 Gordon Henderson
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as
 *    published by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with wiringPi.
 *    If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
//#include <linux/spi/spi.h>
#include <errno.h>
#include <getopt.h>

#include "wiringPiSPI.h"


// The SPI bus parameters
//	Variables as they need to be passed as pointers later on

static char       *spiDev0 = "/dev/spidev0.0" ;
static char       *spiDev1 = "/dev/spidev0.1" ;

static uint8_t     spiMode = 0 ;
static uint8_t     spiBPW  = 8 ;
static uint16_t    spiDelay= 0;
static uint8_t     spiLSB  = 0x08;//SPI_LSB_FIRST;

static uint32_t    spiSpeeds [2] ;
static int         spiFds [2] ;

static int kkk[1]={0xff};
int *mesg;
//unsigned long long  	test[1]={0xaaaaaaaaaaaaaaaa};
//unsigned long		test[1]={0x0000000000000000};
unsigned char		test[1]={0xaa};
__u64 		   	*ppp;
//static __u64   *po = &test;
/*
 * wiringPiSPIGetFd:
 *	Return the file-descriptor for the given channel
 *********************************************************************************
 */

int wiringPiSPIGetFd (int channel)
{
  return spiFds [channel & 1] ;
}


/*
 * wiringPiSPIDataRW:
 *	Write and Read a block of data over the SPI bus.
 *	Note the data ia being read into the transmit buffer, so will
 *	overwrite it!
 *	This is also a full-duplex operation.
 *********************************************************************************
 */

int wiringPiSPIDataRW (int channel, unsigned long long  *wdata, unsigned long long *rdata,int len)
{
  struct spi_ioc_transfer spi ;

  channel &= 1 ;

  spi.tx_buf        = (unsigned long)wdata ;
  spi.rx_buf        = (unsigned long)rdata ;
  spi.len           = len ;
  spi.delay_usecs   = spiDelay ;
  spi.speed_hz      = spiSpeeds [channel] ;
  spi.bits_per_word = spiBPW ;

  return ioctl (spiFds [channel], SPI_IOC_MESSAGE(1), &spi) ;
}


/*
 * wiringPiSPISetup:
 *	Open the SPI device, and set it up, etc.
 *********************************************************************************
 */

int wiringPiSPISetup (int channel, int speed)
{
  int fd ;
  int i;
  channel &= 1 ;

  if ((fd = open (channel == 0 ? spiDev0 : spiDev1, O_RDWR)) < 0)
    return -1 ;

  spiSpeeds [channel] = speed ;
  spiFds    [channel] = fd ;
	printf("the fd is %d\n",fd);
// Set SPI parameters.
//	Why are we reading it afterwriting it? I've no idea, but for now I'm blindly
//	copying example code I've seen online...

  if (ioctl (fd, SPI_IOC_WR_MODE, &spiMode)         < 0) return -1 ;
  if (ioctl (fd, SPI_IOC_RD_MODE, &spiMode)         < 0) return -1 ;

  if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0) return -1 ;
  if (ioctl (fd, SPI_IOC_RD_BITS_PER_WORD, &spiBPW) < 0) return -1 ;

  if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)   < 0) return -1 ;
  if (ioctl (fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)   < 0) return -1 ;

//  i = ioctl(fd, SPI_IOC_RD_LSB_FIRST,&spiLSB);
//  i = ioctl(fd, SPI_IOC_WR_LSB_FIRST,&spiLSB);

  printf("ioctl LSB set is %d\n",i);
//  printf("errno = %d\n",errno);
//  mesg = strerror(errno);
//  printf("Mesg:%s\n",mesg);

  return fd ;
}

