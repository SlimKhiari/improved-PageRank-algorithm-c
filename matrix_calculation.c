#include <stdio.h>
#include <math.h>
#include "matrix_calculation.h"

/*
 Function to build the transition matrix from the matrix in the .txt file
 @param num_pages : number of nodes in the graph
 @param link_matrix : the transition matrix
 @param web_matrix : web graph
*/
void initLinkMatrix(int num_pages, float link_matrix[][num_pages], t_matrix *web_matrix)
{
	for (int i = 0; i < num_pages; i++)
	{
		for (int j = 0; j < num_pages; j++)
		{
			link_matrix[i][j] = 0;
		}
	}
	
	int num_links=0;
	for(int i=0; i < web_matrix->size; i++)
	{	
		num_links=0;
		for(int j=1; j < web_matrix->size; j++)
		{
			if(web_matrix->coeffs[i][j] > 0)
			{
				num_links ++;
			}
		}
		for (int j = 1; j < web_matrix->size; j++) 
			{
				int page_num;
				if(web_matrix->coeffs[i][j] > 0)
				{
					page_num = (int) web_matrix->coeffs[i][j];
					link_matrix[page_num - 1][i] = 1 / (float) num_links;
				}
			}
	}

}

/*
 Function to multiply a matrix by a scalar
 @param matrix : the matrix
 @param num_rows : number of rows
 @param num_cols :number of columns
 @param scalar : the scalar
*/
void scalarMultiplication(float *matrix, int num_rows, int num_cols, float scalar) 
{
	int num_entries = num_rows * num_cols;
	for (int i = 0; i < num_entries; i++)
	{
		*matrix++ *= scalar;
	}
}

/*
 Function to multiply a matrix by vector
 @param matrix : the matrix
 @param num_rows : number of rows
 @param num_cols :number of columns
 @param column : the vector
*/
void columnMultiplication(float *matrix, int num_rows, int num_cols, float *column) 
{
	float product[num_cols];
	for (int i = 0; i < num_rows; i++) 
	{
		float sum = 0;
		float *temp = column;
		for (int j = 0; j < num_cols; j++)
		{
			sum += *matrix++ * *temp++;
		}
		product[i] = sum;
	}

	for (int i = 0; i < num_cols; i++)
	{
		*column++ = product[i];
	}
}

/*
 Function to add 2 matrices
 @param matrix1 : first matrix
 @param matrix2 : second matrix
 @param num_rows : number of rows
 @param num_cols :number of columns
*/
void addition(float *matrix1, float *matrix2, int num_rows, int num_cols) 
{
	int num_entries = num_rows * num_cols;
	for (int i = 0; i < num_entries; i++)
	{
		*matrix1++ += *matrix2++;
	}
}

/*
 Function to calculate the norm
 @param column : the vector in question
 @param num_rows : number of lines
*/
float norm(float *column, int num_rows) 
{
	float sum = 0;
	for (int i = 0; i < num_rows; i++)
	{
		sum += pow(*column++, 2);
	}
	return sqrt(sum);
}

