/*
 * twoPlayer.c
 *
 *  Created on: Dec 13, 2016
 *      Author: alex
 */
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
int check(Array board){
	int counterX=0;
	int counterY=0;
	for(int o=0;o<board->size;o=o+1){
				for(int j=0;j<board->size;j=j+1){

					Cell check=getBoard(board,o,j);
					if(check->cellState==P1)
						counterX=counterX+1;
					if(check->cellState==P2)
						counterY=counterY+1;
				}
			}
			if(counterX==0){
				printf("Player Y won");
				printf("\n");

				return 1;
			}
			else{
				if(counterY==0){
					printf("Player X won");
					printf("\n");

					return 1;
				}

			}
			return 0;
}
void generationsTwo(Array boardq, int gen,int gameType){
	int x,y,z;
	Array board;
	if(gen==0){
		board=generations(boardq,0,2);
		if (check(board)==1){
			return;}
	}
	else{
		board=generations(boardq,1,2);
		if (check(board)==1){
					return;}
	}
	printBoard(board);
	printf("\n");

	for (int i=1;i<gen;i=i+1){


			if (i%2!=0){
				printf("Player 1 Enter (x,y) to Die");
				printf("\n");
				scanf("%d", &x);
				scanf("%d", &y);
					z=0;
					while(z!=1){
						if(x>=board->size||y>=board->size||x<0||y<0){
							printf("invalid input, try again");
							printf("\n");

							scanf("%d", &x);
							scanf("%d", &y);}
						else
							z=1;
					}
					set((Array)*(board->elements+x),y,createCell(DEAD));
				printf("Player 1 Enter (x,y) to live");
				printf("\n");
				scanf("%d", &x);
				scanf("%d", &y);
				z=0;
				while(z!=1){
					if(x>=board->size||y>=board->size||x<0||y<0){
						printf("invalid input, try again");
						printf("\n");

						scanf("%d", &x);
						scanf("%d", &y);}
					else
						z=1;
				}
					set((Array)*(board->elements+x),y,createCell(P1));
			}
			else{
				printf("Player 2 Enter (x,y) to Die");
				printf("\n");
				scanf("%d", &x);
				scanf("%d", &y);
				z=0;
				while(z!=1){
					if(x>=board->size||y>=board->size||x<0||y<0){
						printf("invalid input, try again");
						printf("\n");
						scanf("%d", &x);
						scanf("%d", &y);}
					else
						z=1;
				}
					set(*(board->elements+x),y,createCell(DEAD));
					printf("Player 2 Enter (x,y) to live");
					printf("\n");

				scanf("%d", &x);
				scanf("%d", &y);
				z=0;
				while(z!=1){
					if(x>=board->size||y>=board->size||x<0||y<0){
						printf("invalid input, try again");
						printf("\n");
						scanf("%d", &x);
						scanf("%d", &y);}
					else
						z=1;
				}
					set(*(board->elements+x),y,createCell(P2));
			}
				updateBoard(board);
				board=generations(board,1,gameType);
				printBoard(board);
				printf("\n");
				if (check(board)==1){
							return;}
			}

	freeBoard(board);
}

