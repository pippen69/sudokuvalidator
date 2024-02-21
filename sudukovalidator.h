#ifndef SUDOKU_VALIDATOR_H
#define SUDOKU_VALIDATOR_H
#define NUM_THREADS 11

#include <pthread.h>
#include <stdbool.h>


// Structure for passing parameters to checkSubGrid function
struct subgridParam {
    int startRow;
    int startCol;
};

// Thread function to check all rows
extern void* checkRow(void* param);

// Thread function to check all columns
extern void* checkColumn(void* param);

// Thread function to check all 3x3 subgrids
extern void* checkSubGrid(void* param);

#endif /* SUDOKU_VALIDATOR_H */
