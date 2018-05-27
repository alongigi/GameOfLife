/*
 * gameIO.c
 *
 *  Created on: Dec 11, 2016
 *      Author: alex
 */
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

Array buildBoard(int n,char game[],int gameType){

	FILE *file;
	char setup[2*n];
	Array board=createBoard(n,gameType);
	file=fopen(game,"r");
	for(int j=0;j<n;j=j+1){
		fscanf(file,"%[^\n]\n",setup);
		for(int i=0;i<2*n;i=i+2){
			if((setup[i]!='X'&&setup[i]!='Y'&&setup[i]!='.'&&setup[i]!='\n'&&setup[i]!=' ')||(setup[i]=='Y'&&gameType!=2)){
				printf("configuration is wrong");
				return NULL;
			}
			Cell cell;
			if(setup[i]=='X'){
				cell=(Cell)createCell(P1);
			}
			else{
				if(setup[i]=='Y'&&gameType==2){
					cell=(Cell)createCell(P2);
				}
				else{
					if(setup[i]=='.'){
						cell=(Cell)createCell(DEAD);
						}
				}
			}
			set(*(board->elements+j),i/2,cell);
			cell=NULL;
		}
	}
	fclose(file);
	return board;
}

