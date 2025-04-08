#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 9

// Function to check if placing 'num' in the given cell is safe
bool is_safe(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + start_row][j + start_col] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve the sudoku puzzle using backtracking
bool solve_sudoku(int board[N][N], int row, int col) {
    if (row == N - 1 && col == N) {
        return true;
    }

    if (col == N) {
        row++;
        col = 0;
    }

    if (board[row][col] != 0) {
        return solve_sudoku(board, row, col + 1);
    }

    for (int num = 1; num <= N; num++) {
        if (is_safe(board, row, col, num)) {
            board[row][col] = num;
            if (solve_sudoku(board, row, col + 1)) {
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

// Function to print the sudoku board with better formatting
void print_board(int board[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            // Print the number, ensuring it's aligned with a fixed width of 2 characters
            printf("%2d ", board[row][col]);

            // Print a vertical line between each 3x3 block
            if ((col + 1) % 3 == 0 && col != N - 1) {
                printf("| ");
            }
        }
        printf("\n");

        // Print a horizontal line between each 3x3 block after every 3rd row
        if ((row + 1) % 3 == 0 && row != N - 1) {
            printf("------|-------|------\n");
        }
    }
}

// Function to load sudoku from a file
bool load_sudoku_file(const char *filename, int board[N][N]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return false;
    }

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            fscanf(file, "%d", &board[row][col]);
        }
    }

    fclose(file);
    return true;
}

// Function to save sudoku to a file
void save_sudoku_to_file(const char *filename, int board[N][N]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error writing the sudoku puzzle to file:\n");
        return;
    }
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            fprintf(file, "%d", board[row][col]); // Write each number without spaces
        }
        fprintf(file, "\n"); // Newline after each row
    }
    fclose(file);
}

int main() {
    int board[N][N] = {0};
    char filename[100];

    // Load the sudoku puzzle from file
    printf("Enter the filename to load the sudoku puzzle:\n");
    scanf("%s", filename);
    if (!load_sudoku_file(filename, board)) {
        printf("Error loading the puzzle from the file. Ensure the file exists and is formatted correctly:\n");
        return 1;
    }

    // Print the initial sudoku puzzle
    printf("Initial sudoku puzzle:\n");
    print_board(board);

    // Solve the sudoku puzzle
    if (solve_sudoku(board, 0, 0)) {
        printf("Solved sudoku puzzle:\n");
        print_board(board);
    } else {
        printf("No solution exists for the given sudoku puzzle:\n");
    }

    // Save the solved sudoku to a file
    printf("Enter the filename to save the solved sudoku puzzle:\n");
    scanf("%s", filename);
    save_sudoku_to_file(filename, board);
    printf("Solved puzzle has been saved to %s\n", filename);

    return 0;
}
