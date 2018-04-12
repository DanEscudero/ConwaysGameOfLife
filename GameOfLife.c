#include <stdio.h>
#include <stdlib.h>

#define NO_CHAR 46 //.
#define YES_CHAR 35 //#
#define TAM 20
#define DELAY 100000000

/* Starts a square matrix and returns its pointer */
int ** startMatrix (int size)
{
	int ** matrix = malloc (sizeof (int *) * size);
	for (int i = 0; i < size; i++)
		matrix [i] = malloc (sizeof (int) * size);
	return matrix;
}

/* Fills a Matrix with a given element x */
void fillBoard (int **M, int size, int x)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			M[i][j] = x;
}

/* Scan from keyboard elements to the Matrix */
void readBoard (int **M, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			scanf ("%c ", &M[i][j]);
}

/* Prints out a Matrix */
void printBoard (int **M, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			printf ("%c  ", M[i][j]);
		printf ("\n");
	}
}

/* Both following functions are called to make *
 * sure not to iterate out of Matrix bounds    */
int defStart (int x)
{
	if (!x) return x;
	else return x-1;
}

int defEnd (int x, int max)
{
	if (x == max-1) return x;
	else return x+1;
}

/* Receives the Board, a position [i,j] and the matrix size (m*n) *
 * Returns the sum of the neighbours of the position 			  */
int n_around (int **Board, int i, int j, int size)
{
	int startLine, startCol, endLine, endCol, around = 0;
	
	startLine = defStart(i);
	startCol = defStart(j);
	endLine = defEnd(i, size);
	endCol = defEnd(j, size);
	
	for (int k = startLine; k <= endLine; k++)
		for (int l = startCol; l <= endCol; l++)
			if (!(k==i && l==j)) { 
				//around += Board[k][l];
				if (Board[k][l] == '#') around++;
			}
	
	return around;
}

/* Fills the matrix Around with the      *
 * number of neighbours of each position */
void fillAround (int **Around, int **Board, int size)
{
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j++)
			Around[i][j] = n_around(Board, i, j, size);
}

void fillNewBoard (int **Board, int **NewBoard, int **Around, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (Around[i][j] == 3) NewBoard[i][j] = YES_CHAR;
			if (Around[i][j] == 2) NewBoard[i][j] = Board[i][j];
		}
	}
}

/* Refresh Board means swap elements on Board with elements on NewBoard */
void refreshBoard (int ***Board, int ***NewBoard, int size)
{
	//Working, even with warning
	int **aux;
	aux = *Board;
	*Board = *NewBoard;
	*NewBoard = aux;

}

int main ()
{
	int **Board = startMatrix(TAM);
	int **Around = startMatrix(TAM);
	int **NewBoard = startMatrix(TAM);
		
	readBoard (Board, TAM);
	
	printf ("\n=== GEN 1 ===\n");
	printBoard (Board, TAM);
	
	for (int i = 2; ; i++) {
		for (int pause = 0; pause < DELAY; pause++); //Lock to better view
		fillBoard(NewBoard, TAM, NO_CHAR);
		fillAround(Around, Board, TAM);
		fillNewBoard(Board, NewBoard, Around, TAM);
		system("clear");
		printf("\n=== GEN %d ===\n", i);
		printBoard(NewBoard, TAM);
		refreshBoard(&Board, &NewBoard, TAM);
	}
	
	return 0;
}
