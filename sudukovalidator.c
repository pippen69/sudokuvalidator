#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_THREADS 11
int sudoku[9][9] = { 
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
};

struct subgridParam {
    int startRow;
    int startCol;
};

// Thread function to check all rows
void* checkRow(void* param) {
   int (*sudoku)[9] = param;
   int (*sudoku)[9] = param;
    bool check = true;
    // Logic to check each row for numbers 1 through 9
    for (int i = 0; i < 9; i++) {
        bool rowCheck[9] = {false};
        for(int x = 0; x < 9; x++) {
            rowCheck[sudoku[i][x] - 1] = true;
        }
            for(int x = 0; x < 9; x++) {
                if (rowCheck[x] == false) {
                    check = false;
                    break;
                }
            }
            if(!check)
                break;
        }
        if(check)
            printf("All rows are correct.\n");
        else
            printf("Error in row.\n");

   return NULL; 
}

// Thread function to check all columns
void* checkColumn(void* param) {
    int (*sudoku)[9] = param;
    bool check = true;
    // Logic to check each row for numbers 1 through 9
    for (int i = 0; i < 9; i++) {
        bool checkColumn[9] = {false};
        for(int j = 0; j < 9; j++) {
            checkColumn[sudoku[i][j] - 1] = true;
        }
            for(int  k= 0; k < 9; k++) {
                if (checkColumn[k] == false) {
                    check = false;
                    break;
                }
            }
            if(!check)
                break;
        }
        if(check)
            printf("All Coloumns are correct.\n");
        else
            printf("Error in Coloumn.\n");
    
   return NULL;
}

// Thread function to check all 3x3 subgrids
void* checkSubGrid(void* param) {
     struct subgridParam* params = (struct subgridParam*)param;
    int i;
    int (*sudoku)[9] = param;
    bool rowCheck[9] = {false};
    int startRow = params->startRow;/* Calculate based on passed param */;
    int startCol = params->startCol;/* Calculate based on passed param */;
    bool check = true;
    // Logic to check 3x3 subgrid for numbers 1 through 9
    for(i = 0; i < 3; i++)
        for(int x = 0; x < 3; x++)
            rowCheck[sudoku[startRow + i][startCol + x] - 1] = true;
    for(i = 0; i < 9; i++)
        if(rowCheck[i] == false) {
            check = false;
            break;
        }
    if (check)
        printf("All subgrids are correct.\n");
    else
        printf("Error in subgrid.\n"); 
    return NULL;
}

bool check = true; 
int main() {
    pthread_t threads[NUM_THREADS];
    int threadIndex = 0;

    // Row & column checks
    pthread_create(&threads[threadIndex++], NULL, checkRow, NULL);
    pthread_create(&threads[threadIndex++], NULL, checkColumn, NULL);

    // Creating nine threads for each 3x3 subgrid validation (Subgrid checks)
    for(int i = 0; i < 9; i++) {
        pthread_create(&threads[threadIndex++], NULL, checkSubGrid, (void*)(size_t)i);
    }

    // Waiting for all threads to complete
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    if (check){
        printf("Valid Sudoku");
    }
    else {
        printf("Invalid");
    }
    return 0;
}
