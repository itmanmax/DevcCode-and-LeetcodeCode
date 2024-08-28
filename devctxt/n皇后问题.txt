#include <stdio.h>
#include <stdlib.h>
 
int n;              // Number of queens (and the size of the board)
int *x;             // x[i] is the column where queen i is placed
int solutionCount;  // Number of solutions found
 
// Function to check if a position is safe for a queen
int isSafe(int row, int col) {
    for (int prev = 0; prev < row; ++prev) {
        if (x[prev] == col || abs(row - prev) == abs(col - x[prev])) {
            return 0;
        }
    }
    return 1;
}
 
// Function to print a single solution
void printSolution() {
    for (int i = 0; i < n; ++i) {
        printf("%d ", x[i]);
    }
    printf("\n");
}
 
// Recursive function to solve the problem
void nQueens(int row) {
    for (int col = 0; col < n; ++col) {
        if (row == 0 && col >= (n + 1) / 2) {
            // Stop the loop for the first row when reaching the middle column
            break;
        }
        if (isSafe(row, col)) {
            x[row] = col;
            if (row == n - 1) {
                printSolution();
                solutionCount++;
            } else {
                nQueens(row + 1);
            }
        }
    }
}
 
int main() {
    scanf("%d", &n);
    x = (int *)malloc(n * sizeof(int));
    solutionCount = 0;
    nQueens(0);
    if (solutionCount == 0) {
        printf("No solutions found.\n");
    }
    free(x);
    return 0;
}
