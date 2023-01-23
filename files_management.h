#ifndef FILES_MANAGEMENT_H_
#define FILES_MANAGEMENT_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define M  "matrix.txt"
#define TMP 1024

typedef struct
{
	float** coeffs;
	unsigned int size;
}t_matrix;

int matrixSize(char* str);
char* readFile(char* fichier);
t_matrix* atoMatrix(char* str);
t_matrix* allocMatrix(int size);
void printMatrix(t_matrix* mat);
void printTab2D(float** tab, int size);
void deallocMatrix(t_matrix** mat);

#endif
