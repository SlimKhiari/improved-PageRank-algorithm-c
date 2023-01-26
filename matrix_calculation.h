#ifndef MATRIX_CALCULATION_H_
#define MATRIX_CALCULATION_H_

#include "files_management.h"
#define MAX_PAGES 100 
#define MIN_PAGES 2 
#define DAMPING_FACTOR 0.85
#define TOLERANCE 0.0000000000000001

void initLinkMatrix(int num_pages, float link_matrix[][num_pages], t_matrix *web_matrix);
void scalarMultiplication(float *matrix, int num_rows, int num_cols, float scalar);
void columnMultiplication(float *matrix, int num_rows, int num_cols, float *column);
void addition(float *matrix1, float *matrix2, int num_rows, int num_cols);
float norm(float *column, int num_rows);

#endif
