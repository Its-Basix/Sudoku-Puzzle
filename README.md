**C Sudoku Game**

**Description**

This project is a console-based Sudoku game written in C.
It generates a valid, fully solved Sudoku puzzle, removes numbers to create a playable board, and allows the user to input numbers to solve it.

The game checks for correctness and gives feedback on inputs, making it interactive and educational.

**Features**

Generates a fully solved Sudoku board automatically.

Creates a playable puzzle by removing a set number of numbers.

Validates user inputs and gives feedback: correct or incorrect.

Allows users to give up or reveal the solution.

Displays time played in minutes.

Console-based, no external libraries required.

**How it Works**

Matrix Creation: Initializes a 9x9 matrix for the Sudoku board.

Diagonal Filling: Fills the diagonal 3x3 boxes with random numbers (ensuring no repeats).

Solver: Recursively fills the remaining cells to complete the board.

Playable Board: Copies the solved board and removes a set number of numbers for the player to solve.

User Input: Prompts the player to enter a row, column, and number.

Validation: Checks if the input matches the solved board and updates the playboard.

Completion Check: Ends the game when the board is fully completed.

**Files**

sudoku.c – Main C program implementing the Sudoku game.

**Requirements**

C compiler (e.g., gcc, clang)

Terminal or console to run the program

**Compilation and Running**
Compile:
gcc sudoku.c -o sudoku -lm


-lm is optional if math.h functions are used.

Run:
./sudoku


The game will display the Sudoku board with empty cells as _.

Follow the prompts to input numbers.

**Controls**

Input a row (1–9), column (1–9), and number (1–9) to fill a cell.

Input -1 as the number to give up.

Input -2 as the number to reveal the solution.

**Notes**

The puzzle is always solvable since the board is generated from a complete solution.

The program tracks the time taken to solve the puzzle.

Currently runs in a console environment, suitable for learning C, arrays, recursion, and backtracking.

**Author**

Ben Taylor (Basix)
