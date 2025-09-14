FLAGS := -Wall
D_FLAGS := -Wall -g
SRC := src


#Debug build 

debug: sllist_debug.o testllist_debug.o
	gcc $(D_FLAGS) $^ -o  sllist_debug.exe

run_debug:
	gdb -x .gdbinit ./sllist_debug.exe

sllist_debug.o: $(SRC)/sllist/sllist.c
	gcc -c $(D_FLAGS) $< -o $@

testllist_debug.o: $(SRC)/sllist/testsllist.c
	gcc -c $(D_FLAGS) $< -o $@

#Release build
compile : sllist.o testsllist.o
	gcc sllist.o testsllist.o -o sllisttest.exe	


testsllist.o : $(SRC)/sllist/testsllist.c
	gcc -c $(FLAGS) $<

sllist.o : $(SRC)/sllist/sllist.c
	gcc -c $(FLAGS) $<


