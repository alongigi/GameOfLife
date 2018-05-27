/*
 * defs.c
 *
 *  Created on: Dec 8, 2016
 *      Author: alex
 */
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve){
	if( _size<=0){
		return NULL;
	}
	Array array=(Array) malloc(sizeof (struct t_array));
	if (array==NULL)
		return NULL;
	array->elements=(Element*) malloc(sizeof(Element)*_size);
	if(array->elements==NULL)
		return NULL;
	array->copyElement=_copy;
	array->evolveElement=_evolve;
	array->freeElement=_free;
	array->printElement=_print;
	array->size=_size;
	return array;
}
void destroyArray(Element arrayg){
	Array array=(Array)arrayg;
	int i=0;
	if (array->size>0){
		while(i!=array->size){
			array->freeElement(*(array->elements+i));
			i=i+1;
		}
	}
	if(array!=NULL){
		//free(array->elements);
		free(array);
	}
}
void set(Array array, int i, Element element){
	//assigns array[i]=element;
	if(element!=NULL&&array!=NULL&&i>=0&&i<array->size){
		Element copy=array->copyElement(element);
		array->elements[i]=copy;
		}
	}

Element get(Array array, int i){
	if(i>=array->size||i<0){
		return NULL;
	}
	if(array==NULL)
		return NULL;
	Element copy=array->copyElement(*(array->elements+i));
	return copy;
}
Element getBoard(Array array, int i, int j){
	if(i>=array->size||i<0||j>=array->size||j<0){
			return NULL;
		}
	if(array==NULL)
		return NULL;

	Element copy=get((Array)*(array->elements+i),j);
	return copy;
}



void printArray(Element arrayg){
	Array array=(Array)arrayg;
	if(array!=NULL){
		for(int i=0;i<array->size;i=i+1){
			array->printElement(*(array->elements+i));
			printf(" ");
		}
	}
}
Element copyArray(Element arrayg){
	Array array=(Array) arrayg;

	Array copy=createArray(array->size,array->copyElement,array->freeElement,array->printElement,array->evolveElement);
	if(copy!=NULL){
		for(int i=0;i<array->size;i=i+1){
			copy->elements[i]=array->copyElement(array->elements[i]);
		}
	}
	return (Element)copy;
}
void freeBoard(Array array){
	if(array!=NULL){
			for(int i=0;i<array->size;i=i+1){
				destroyArray(*(array->elements+i));
			}
		free(array);
	}
}
Element evolveArray(Element arrayg){
	Array array=(Array)arrayg;
	if(array!=NULL){
				for(int i=0;i<array->size;i=i+1){
					array->evolveElement(*(array->elements+i));
				}
	}
	return array;
}








Cell createCell(State cellState){
	if(cellState<0||cellState>3)
		return NULL;

	Cell cell=(Cell)malloc(sizeof(struct t_cell));
	cell->cellState=cellState;
	return cell;
}



Element evolveCellZero(Element cellg){
	Cell cell=(Cell)cellg;
	if(cell!=NULL){
		int counter=0;
		for(int i=0;i<8;i=i+1){
			if(*(cell->neighbors+i)==P1)
				counter=counter+1;
		}
		if(counter<=1||counter>3){
			cell->cellState=DEAD;
		}
		if(cell->cellState==DEAD&&counter==3){
			cell->cellState=P1;
		}
		return (Element)cell;
	}
	return NULL;
}
Element evolveCellTwo(Element cellg){
	Cell cell=(Cell)cellg;
	if(cell!=NULL){
		int counterX=0;
		int counterY=0;

		for(int i=0;i<8;i=i+1){
			if(*(cell->neighbors+i)==P1)
				counterX=counterX+1;
			if(*(cell->neighbors+i)==P2)
				counterY=counterY+1;
		}
		if(counterX+counterY<=1){
			cell->cellState=DEAD;
		}
		if(counterX>3||counterY>3||counterX+counterY>3){
				cell->cellState=DEAD;
		}
		else{
			if(cell->cellState==P2&&(counterX==2||counterX==3))
				cell->cellState=P1;
			else
				if(cell->cellState==P1&&(counterY==2||counterY==3))
				cell->cellState=P2;
		}
		if(cell->cellState==DEAD&&counterX+counterY==3){
			if(counterX>counterY){
				cell->cellState=P1;
			}
			else
				cell->cellState=P2;
		}
		return (Element)cell;
	}
	return NULL;
}
void printCell(Element cellg){
	Cell cell=(Cell)cellg;
	if(cell!=NULL){
		if(cell->cellState==DEAD)
			printf(".");
		if(cell->cellState==P1)
					printf("X");
		if(cell->cellState==P2)
					printf("Y");

	}
}
void FreeCell(Element cellg){
	Cell cell=(Cell)cellg;
	if(cell!=NULL){
		free(cell);
	}
}

Element CopyCell(Element cellg){
	Cell cell=(Cell)cellg;
	Cell copy=(Cell)malloc(sizeof(struct t_cell));
	if(copy==NULL)
		return NULL;
	copy->cellState=cell->cellState;

	for(int i=0;i<8;i=i+1){
		copy->neighbors[i]=cell->neighbors[i];
	}

	return copy;
}
Array createBoard(int size,int gameType){
	Array board=createArray(size,copyArray,destroyArray,printArray,evolveArray);
	for(int i=0;i<board->size;i=i+1){
		if(gameType==1){
			board->elements[i]=createArray(size,CopyCell,FreeCell,printCell,evolveCellZero);
		}
		else{
			board->elements[i]=createArray(size,CopyCell,FreeCell,printCell,evolveCellTwo);
		}
		for(int j=0;j<size;j=j+1){
			set(*(board->elements+i),j,NULL);
		}

	}
	return board;
}
void printBoard(Array array){
	for(int i=0;i<array->size;i=i+1){
			printArray(*(array->elements+i));
			printf("\n");
	}
}
void freeInBoard(Array array,int i, int j){
	Cell cell=(Cell)*(((Array)*(array->elements))->elements+j);
	if(cell!=NULL){
		FreeCell(cell);
	}
}
