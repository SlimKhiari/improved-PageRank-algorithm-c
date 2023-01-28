#ifndef MATRIX_CALCULATION_H_
#define MATRIX_CALCULATION_H_

#include "files_management.h"
#define TOLERANCE 0.0001

float** initLinkMatrix(int num_pages, float** link_matrix, t_matrix *web_matrix);
void scalarMultiplication(float *matrix, int num_rows, int num_cols, float scalar);
void columnMultiplication(float *matrix, int num_rows, int num_cols, float *column);
void addition(float *matrix1, float *matrix2, int num_rows, int num_cols);
float norm(float *column, int num_rows);
void final_result_calculation(int num_pages, float *score_column);
void initial_vector_calculation(int num_pages, float score_column[num_pages]);

#endif
