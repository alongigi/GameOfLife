gameOfLife: main.o defs.o gameIO.o twoPlayer.o ZeroPlayer.o 
	gcc main.o defs.o gameIO.o twoPlayer.o ZeroPlayer.o -o gameOfLife
main.o: main.c defs.h 
	gcc -c main.c
defs.o: defs.c defs.h
	gcc -c defs.c
gameIO.o: gameIO.c defs.h 
	gcc -c gameIO.c
twoPlayer.o: twoPlayer.c defs.h 
	gcc -c twoPlayer.c
ZeroPlayer.o: ZeroPlayer.c defs.h 
	gcc -c ZeroPlayer.c


clean: rm -f *.o    
