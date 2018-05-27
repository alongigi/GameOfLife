#ifndef DEFS_H_
#define DEFS_H_

/*
 * Basic definitions
 */
typedef void * Element;
typedef Element (*CopyFunction)(Element);
typedef void (*FreeFunction)(Element);
typedef void (*PrintFunction)(Element);
typedef Element (*EvolveFunction)(Element);

/*
 * Structs and enums
 */
typedef enum e_state{
	DEAD, P1, P2, BLANK
}State;

struct t_cell{
	State cellState;
	State neighbors[8];
};
typedef struct t_cell * Cell;

struct t_array{
	int size;
	Element* elements;
	CopyFunction copyElement;
	FreeFunction freeElement;
	PrintFunction printElement;
	EvolveFunction evolveElement;
};
typedef struct t_array * Array;


/*
 * Function Decleration
 */
Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve);
void destroyArray(Element array);
void set(Array array, int i, Element element);		//assigns array[i]=element;
Element get(Array array, int i);					//returns array[i]
Element CopyCell(Element cellg);
void FreeCell(Element cell);
void printCell(Element cellg);
Element evolveCellZero(Element cell);
Element evolveCellTwo(Element cell);
void printArray(Element array);
Cell createCell(State cellState);
Element evolveArray(Element array);
void freeBoard(Array array);
Element copyArray(Element array);
Array createBoard(int size,int gameType);
Array buildBoard(int n,char address[],int gameType);
void printBoard(Array array);
void updateNeighbor(Array board, Cell cell, int x, int y);
Element getBoard(Array array, int i, int j);
void updateBoard(Array board);
Array generations (Array board, int generations,int gameType);
void generationsTwo(Array boardq, int gen,int gameType);
Array buildArray(int n, char game[],int gameType);
void freeInBoard(Array array,int i, int j);
int check(Array board);
#endif /* DEFS_H_ */
