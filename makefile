Pto : Pto.o nfc.o wiringPiSPI.o wiringPi.o piHiPri.o piThread.o
	@gcc Pto.o nfc.o wiringPiSPI.o wiringPi.o piHiPri.o piThread.o -o Pto -lpthread -g
Pto.o : Pto.c nfc.h wiringPiSPI.h
	@gcc -c Pto.c -g
nfc.o : nfc.c nfc.h wiringPiSPI.h
	@gcc -c nfc.c -g
wiringPiSPI.o : wiringPiSPI.c wiringPiSPI.h
	@gcc -c wiringPiSPI.c -g
wiringPi.o : wiringPi.c wiringPi.h
	@gcc -c wiringPi.c -g
piHiPri.o : piHiPri.c
	@gcc -c piHiPri.c -g
piThread.o : piThread.c
	@gcc -c piThread.c -g
clean :
	@rm *.o Pto
