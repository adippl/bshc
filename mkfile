
CC=gcc-9.1.0	

CFLAG= -std=c18 -lm -g -Wall -Werror -pedantic	-march=skylake -mtune=skylake -fplan9-extensions

output:	main.o state.o conf.o term.o ui.o mth.o ship.o
	$CC $CFLAG  -o bsh main.o state.o conf.o term.o ui.o mth.o ship.o

main.o:	main.c
	$CC $CFLAG  -c main.c

state.o: state.c
	$CC $CFLAG  -c state.c
conf.o:	conf.c
	$CC $CFLAG  -c conf.c
term.o:	term.c
	$CC $CFLAG  -c term.c
ui.o:	ui.c
	$CC $CFLAG  -c ui.c
mth.o:	mth.c
	$CC $CFLAG  -c mth.c
ship.o:	ship.c
	$CC $CFLAG  -c ship.c

cl:
	rm *.o
nk:	cl
	rm bsh
