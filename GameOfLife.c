#include <stdio.h>
#include <stdlib.h>
#define TAM 3
#define ROUNDS 7

/* Fills a Matrix with a given element x */
void fillBoard (int M[TAM][TAM], int m, int n, int x)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			M[i][j] = x;
}

/* Scan from keyboard elements to the Matrix */
void readBoard (int M[TAM][TAM], int m, int n)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf ("%d", &M[i][j]);
}

/* Prints out a Matrix */
void printBoard (int M[TAM][TAM], int m, int n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf ("%d   ", M[i][j]);
		}
		printf ("\n");
	}
}

/* Both following functions are called to make *
 * sutre not to iterate out of Matrix bounds   */
int defStart (int x)
{
	if (!x) return 0;
	else return x-1;
}

int defEnd (int x, int max)
{
	if (x == max-1) return x;
	else return x+1;
}

/* Receives the Board, a position [i,j] and the matrix size (mxn) *
 * Returns the sum of the neighbours of the position 			  */
int n_around (int Board[TAM][TAM], int i, int j, int m, int n)
{
	int startLine, startCol, endLine, endCol, around = 0;
	
	startLine = defStart (i);
	startCol = defStart (j);
	endLine = defEnd (i, m);
	endCol = defEnd (j, n);
	
	for (int k = startLine; k <= endLine; k++)
		for (int l = startCol; l <= endCol; l++)
			if (!(k==i && l==j))
				around += Board[k][l];
	
	return around;
}

/* Fills the matrix Around with the      *
 * number of neighbours of each position */
void fillAround (int Around[TAM][TAM], int Board[TAM][TAM], int m, int n)
{
	for (int i = 0; i < m; i ++)
		for (int j = 0; j < n; j++)
			Around[i][j] = n_around (Board, i, j, m, n);
}

void fillNewBoard (int Board[TAM][TAM], int NewBoard[TAM][TAM], int Around [TAM][TAM], int m, int n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (Around[i][j] == 3) NewBoard[i][j] = 1;
			if (Around[i][j] == 2) NewBoard[i][j] = Board[i][j];
		}
	}
}

/* Refresh Board means swap  elements on Board with elements on NewBoard */
void refreshBoard (int Board[TAM][TAM], int NewBoard[TAM][TAM], int m, int n)
{
	int aux;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			aux = Board[i][j];
			Board[i][j] = NewBoard[i][j];
			NewBoard[i][j] = aux;
		}
	}
}

/* Cleans and Fills NewBoard, refreshes Board and repeat */
void playGame (int rounds, int Board[TAM][TAM], int NewBoard[TAM][TAM], int Around[TAM][TAM], int m, int n)
{
	for (int i = 2; i <= rounds+1; i++) {
		//Lock to better looking
		for (int k = 0; k < 1000000000; k++);
		fillBoard (NewBoard, m, n, 0);
		fillAround (Around, Board, m, n);
		fillNewBoard (Board, NewBoard, Around, m, n);
		printf ("\n=== GEN %d ===\n", i);
		printBoard (NewBoard, m, n);
		refreshBoard (Board, NewBoard, m, n);
	}
}

int main ()
{
	int Board [TAM][TAM];
	int Around [TAM][TAM];
	int NewBoard [TAM][TAM];
	
	readBoard (Board, TAM, TAM);
	printf ("=== INICIO ===\n");
	printBoard (Board, TAM, TAM);
	playGame (ROUNDS, Board, NewBoard, Around, TAM, TAM);
	
	return 0;
}
