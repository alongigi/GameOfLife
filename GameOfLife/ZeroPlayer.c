/*
 * ZeroPlayer.c
 *
 *  Created on: Dec 12, 2016
 *      Author: alex
 */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void updateNeighbor(Array board, Cell cell, int x, int y){
	int counter=0;
	for(int i=x-1;i<=x+1;i=i+1){
		for(int j=y-1;j<=y+1;j=j+1){
			if(i==x&&j==y)
				continue;
			if(i<0||j<0||i>=board->size||j>=board->size){

				(cell)->neighbors[counter]=BLANK;
				counter=counter+1;
			}
			else{
				Cell nei=(Cell)getBoard(board,i,j);
				(cell)->neighbors[counter]=nei->cellState;
				counter=counter+1;
				FreeCell(nei);
			}
		}
	}
}
void updateBoard(Array board){
	for (int i=0;i<board->size;i=i+1){
		for(int j=0;j<board->size;j=j+1){
			Cell cell=(Cell)getBoard(board,i,j);
			updateNeighbor(board,cell,i,j);
			set(board->elements[i],j,cell);
			FreeCell(cell);

		}
	}
}

Array generations (Array newBoard, int n,int gameType){
	Array board=newBoard;
	for (int i=0;i<n;i=i+1){
		updateBoard(board);
	    newBoard=createBoard(board->size,gameType);
		for(int j=0;j<board->size;j=j+1){
			for(int k=0; k<board->size;k=k+1){
				Cell cell=getBoard(board,j,k);
				if(gameType==1)
					evolveCellZero(cell);
				else
					evolveCellTwo(cell);
				set(newBoard->elements[j],k,cell);
				FreeCell(cell);
			}
		}
		freeBoard(board);
		board=newBoard;
	}
	return board;
}


