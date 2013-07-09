#include "nfc.h"

/*Chip select pin can be connected to D10 or D9 which is hareware optional*/
/*if you the version of NFC Shield from SeeedStudio is v2.0.*/


#define 	PN532_CS 	10
#define  	NFC_DEMO_DEBUG

char DataOut[]="HELLO TARGET!!!"; //16bytes
char DataIn[16];//Should be 16bytes
uint32_t versiondata;

void main(void)
{

#ifdef NFC_DEMO_DEBUG
  printf("Hello!\n");
#endif

  begin();

  versiondata = getFirmwareVersion();

  if (! versiondata)
  {

#ifdef NFC_DEMO_DEBUG
    printf("Didn't find PN53x board\n");
#endif
    while (1); // halt
  }

#ifdef NFC_DEMO_DEBUG
  // Got ok data, print it out!
  printf("Found chip PN5");
  printf("%d\n",(versiondata>>24 & 0xFF));
  printf("Firmware ver. ");
  printf("%d\n",((versiondata>>16) & 0xFF));
  printf(".");
  printf("%d\n",((versiondata>>8) & 0xFF));
  printf("Supports ");
  printf("%d\n",(versiondata & 0xFF));
#endif
  // configure board to read RFID tags and cards
  SAMConfig();
  printf("init is ok\n");
  while(1)
  {
	// Configure PN532 as Peer to Peer Initiator in active mode
	if(configurePeerAsInitiator(PN532_BAUDRATE_424K)) //if connection is error-free
	{
		//trans-receive data
		if(initiatorTxRx(DataOut,DataIn))
		{
			#ifdef NFC_DEMO_DEBUG
			printf("Data Sent and Received: %d\n",DataIn);
			#endif
		}
	}
  }
}




