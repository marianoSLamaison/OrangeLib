FLAGS := -Wall
SRC := src



compile : sllist.o testsllist.o
	gcc sllist.o testsllist.o -o sllisttest.exe	

testsllist.o : $(SRC)/sllist/testsllist.c
	gcc -c $<

sllist.o : $(SRC)/sllist/sllist.c
	gcc -c $<

