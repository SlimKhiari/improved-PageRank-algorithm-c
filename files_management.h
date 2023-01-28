#ifndef FILES_MANAGEMENT_H_
#define FILES_MANAGEMENT_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TMP 1024

typedef struct
{
	float** coeffs;
	unsigned int size;
}t_matrix;

int matrixSize(char* str);
char* readFile(char* fichier);
t_matrix* atoMatrix(char* str,int r, int matrix_size); 
t_matrix* allocMatrix(int size);
void printMatrix(t_matrix* mat);
void printTab2D(float** tab, int size);
void deallocMatrix(t_matrix** mat);
float ** floatAlocDynamic_2D( int size );
void deallocFloatMatrix_2D(float** mat, int size);
void deallocFloatVector_1D(float* vect);
float* floatAlocDynamic_1D(int size);
void printFloatMatrix(int num_pages, float **transition_matrix, float transition[num_pages][num_pages], float mean_column[num_pages], float *initial_vector);

#endif
