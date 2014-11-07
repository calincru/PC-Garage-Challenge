#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

/* Boolean support */
#ifndef __bool_true_false_are_defined
 #define bool int
 #define false 0
 #define true 1
 #define __bool_true_false_are_defined
#endif

int **readSudokuFromFile(FILE *);
int **solveSudoku(int **);
bool checkSudoku(int **, int, int);
void output(int **, FILE *);
int* getNext(int **, int **, int *, int *);
int* getPrev(int **, int **, int *, int *);

int main()
{
    FILE *in=fopen("Input11.txt", "r");
    FILE *out=fopen("Output11.txt", "w");
    int i, j;           /* Auxiliary loop counters */
    int **original;     /* Sudoku read from infile */
    int **solved;       /* Sudoku printed to outfile */

    original = readSudokuFromFile(in);
    solved = solveSudoku(original);
    output(solved, out);

    for (i = 0; i < 9; i++) {
        free(original[i]);
        free(solved[i]);
    }
    free(original);
    free(solved);
    fclose(in);
    fclose(out);

    return 0;
}

/* Parses the string read from the infile and returns a 9x9 grid */
int **readSudokuFromFile(FILE *in) {
    int **square;   /* Returned 9x9 grid */
    char *str;      /* Input string */
    int i, j;       /* Loop counters */
    int c = 0;      /* String position */

    str = malloc(256);
    fgets(str, 255, in);

    square = malloc(9 * sizeof *square);
    for (i = 0; i < 9; i++) {
        square[i] = malloc(9 * sizeof *square[i]);
        while ( !isdigit(str[c]) ) {
            c++;
        }
        for (j = 0; j < 9; j++) {
            square[i][j] = str[c] - '0';
            c += 2;
        }
    }
    free(str);
    return square;
}

/* Solve a sudoku square through the use of backtracking */
int **solveSudoku(int **original)
{
    int **solved;   /* Solved 9x9 grid */
    int i, j;       /* Line and column of sudoku grid */
    int *x;         /* Pointer to the modified sudoku element */
    bool valid;     /* Checks if an element contributes to a valid sudoku */

    /* Allocate memory for the returned grid */
    solved = malloc(9 * sizeof *solved);
    for (i = 0; i < 9; i++) {
        solved[i] = malloc(9 * sizeof *solved[i]);
        for (j = 0; j < 9; j++) {
            solved[i][j] = original[i][j];
        }
    }

    /* Get first 0 (uncompleted) element */
    i=0;
    j=-1;
    x=getNext(original, solved, &i, &j);

    while (x)
    {
        valid=false;
        while (!valid && *x < 9)
        {
            (*x)++;
            valid=checkSudoku(solved, i, j);
        }
        if (!valid)
        {
            *x=0;
            x=getPrev(original, solved, &i, &j);
        }
        else x=getNext(original, solved, &i, &j);
    }
    return solved;
}

/* Checks if a sudoku square is currently valid */
bool checkSudoku(int **solved, int x, int y) {
    int i, j;
    /* Line check */
    for (i=0; i<9; i++) {
        if (solved[x][i]==solved[x][y] && i!=y) {
            return false;
        }
    }
    /* Column check */
    for (i=0; i<9; i++) {
        if (solved[i][y]==solved[x][y] && i!=x) {
            return false;
        }
    }
    /* 3x3 square check */
    for(i=x/3*3; i<=x/3*3+2; i++) {
        for(j=y/3*3; j<=y/3*3+2; j++) {
            if(solved[i][j]==solved[x][y] && (i!=x || j!=y)) {
                return false;
            }
        }
    }
    return true;
}

/* Converts a 9x9 grid into a string printed in out */
void output(int **solved, FILE *out) {
    int i, j;
    fprintf(out, "[ ");
    for (i=0; i<9; i++) {
        fprintf(out, "[");
        for (j=0; j<8; j++) {
            fprintf(out, "%d,", solved[i][j]);
        }
        if (i != 8) {
            fprintf(out, "%d], ", solved[i][8]);
        } else {
            fprintf(out, "%d] ].", solved[8][8]);
        }
    }
}

/* Get the next 0 (uncompleted elemnt in sudoku. Horizontal search */
int* getNext(int **original, int **solved, int *i, int *j)
{
    bool done=false;
    (*j)++;
    while (!done && *i<9)
    {
        while (*j<9 && !done)
        {
            if (!original[*i][*j]) done=true;
            else (*j)++;
        }
        if (!done)
        {
            (*i)++;
            *j=0;
        }
    }
    if (done) return (&solved[*i][*j]);
    else return NULL;
}

/* Get the previous 0 (uncompleted) sudoku element. Horizontal search */
int *getPrev(int **original, int **solved, int *i, int *j)
{
    bool done=false;
    (*j)--;
    while (!done && *i>=0)
    {
        while (*j>=0 && !done)
        {
            if (!original[*i][*j]) done=true;
            else (*j)--;
        }
        if (!done)
        {
            (*i)--;
            *j=8;
        }
    }
    if (done) return (&solved[*i][*j]);
    else return NULL;
}
