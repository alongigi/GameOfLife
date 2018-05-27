/*
 * main.c
 *
 *  Created on: Dec 9, 2016
 *      Author: alex
 */
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]){
	int gameType=strtol(argv[1],NULL,10);
	int gameSize=strtol(argv[2],NULL,10);
	int gener=strtol(argv[4],NULL,10);
	char* setup=argv[3];
	Array alex=buildBoard(gameSize,setup,gameType);
	if(gameType==1){
		alex=generations(alex,gener,gameType);
		printBoard(alex);
		freeBoard(alex);

	}
	else
	{
		generationsTwo(alex,gener,gameType);
	}
}
