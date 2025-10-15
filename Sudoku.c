#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// Creates 9x9 starting puzzle.
int** createpuzzle(int** matrix)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j =0; j < 9; j++)
    {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

// Creates the matrix 9x9 for the sudoku puzzle
int** createMatrix(int rows, int columns) 
{
    int** matrix = (int**)calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)calloc(columns, sizeof(int));
    }
    matrix = createpuzzle(matrix);
    return matrix;
}

// Check number for repeat in 3x3 box
bool isInBox(int **matrix, int startRow, int startCol, int num) {
  for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (matrix[startRow + i][startCol + j] == num) return true;
      }
  }
  return false;
}

//Check if repeat in Row
bool isinRow(int **matrix, int row, int num)
{
  for (int col = 0; col < 9; col++)
  {
    if (matrix[row][col] == num)
    {
      return true;
    }
  }
  return false;
}

// Check if repeat in the column
bool isinCol(int **matrix,int col, int num)
{
  for (int row = 0; row < 9; row++)
  {
    if (matrix[row][col] == num)
    {
      return true;
    }
  }
  return false;
}

// Fills Diagonal boxes from top left.
void fillBoxDia(int **matrix, int startRow, int startCol) {
  for (int i = 0; i < 3; i++) {         // Loop through 3 rows
      for (int j = 0; j < 3; j++) {     // Loop through 3 columns
          int num;
          do {
              num = (rand() % 9) + 1;   // Random number from 1 to 9
          } while (isInBox(matrix, startRow, startCol, num)); 
          matrix[startRow + i][startCol + j] = num;
      }
  }
}

bool iscorrect(int **matrix, int row, int col, int num)
{
  return !isinRow(matrix, row, num) && !isinCol(matrix, col, num) && !isInBox(matrix, row - row % 3, col - col % 3, num);
}

bool solveSudoku(int **matrix)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (matrix[row][col] == 0)
            {
                for (int num = 1; num <= 9; num++)
                {
                    if (iscorrect(matrix, row, col, num))
                    {
                        matrix[row][col] = num;
                        if (solveSudoku(matrix))
                            return true;
                        matrix[row][col] = 0; // backtrack
                    }
                }
                return false; // no valid number found
            }
        }
    }
    return true; // solved!
}

void complete(int **sudoku)
{
  // Fill the boxes diagonally to create the base of the board as diagonal cant have overlapping numbers.
  fillBoxDia(sudoku,0,0); 
  fillBoxDia(sudoku,3,3);
  fillBoxDia(sudoku,6,6);

  solveSudoku(sudoku);
  

}

// prints the Sudoku Table displaying solved portions and empty ones 
void printtable(int **matrix, int nr_rows, int nr_columns)
{
 printf("---------------------------\n");

 for(int i=0; i<nr_rows; i++)
 {
  int j=0;
  for(j=0; j<nr_columns; j++) {
    if (j % 3 == 0) printf("| ");
    if (matrix[i][j] == 0) printf("_ ");
    else printf("%d ", matrix[i][j]);
    if (j == 8) printf("| \n"); }
  if (i % 3 == 2 && i != 0) printf("---------------------------\n");
 }  

}

// Copies matrix answers to playboard.
void copymatrix(int **sudoku, int **playboard, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
          playboard[i][j] = sudoku[i][j];
      }
  }
}

// Remove Correct answers and leave a few for starter board
void removeNumbers(int **matrix, int count) {
  while (count > 0) {
      int row = rand() % 9;
      int col = rand() % 9;

      if (matrix[row][col] != 0) {
          matrix[row][col] = 0;
          count--;
      }
  }
}

bool input(int **sudoku, int **playboard)
{
  int row, col, num;
  printf ("What Row is your input:");
  scanf("%d", &row);
  printf ("What Column is your input:");
  scanf("%d", &col);
  printf ("What is your input (type -1 to give up):");
  scanf("%d", &num);
  if (num == -1) return false;
  if (num == -2) {
    printtable(sudoku, 9, 9);
    return false;}
  row--; // So row is counted via number for human not array.
  col--;
  if (row < 0 || row >= 9 || col < 0 || col >= 9 || num < 1 || num > 9) {
    printf("Invalid input! Try again.\n");
    return true; 
  }
  if (sudoku[row][col] == num)
  {
    playboard[row][col] = num;
    printf("Correct!\n");
  }
  else
  {
    printf("The number you have inputed is wrong. \n");
  }
  return true;

}

// Check Completion of board
bool isComplete(int **playboard) {
  for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
          if (playboard[i][j] == 0) return false;
      }
  }
  return true;
}

int main()
{
  srand(time(NULL));
  time_t start_time = time(NULL);
  
  int** sudoku = createMatrix(9,9);
  int** playboard = createMatrix(9,9);

  complete(sudoku);
  copymatrix(sudoku, playboard, 9, 9); // Make two different tables of sudoku
  removeNumbers(playboard, 40); // Removes 40 random elements of the 81 from the set making it 100% solvable.
  printtable(playboard,9,9);
  
  while (!isComplete(playboard))
  {
    if (!input(sudoku, playboard)) break;
    printtable(playboard,9,9);
  }

  if (isComplete(playboard))
  {
    printf("Congratulations! You completed the Sudoku!\n");
  }
  
  time_t end_time = time(NULL);
  double elapsed_seconds = end_time - start_time;
  printf("You played for %.2f minutes.\n", elapsed_seconds / 60.0);


}