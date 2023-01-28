#include <stdio.h>
#include <math.h>
#include "matrix_calculation.h"

/*
 Function to build the transition matrix from the matrix in the .txt file
 @param num_pages : number of nodes in the graph
 @param link_matrix : the transition matrix
 @param web_matrix : web graph
*/
float** initLinkMatrix(int num_pages, float** link_matrix, t_matrix *web_matrix)
{
	for (int i = 0; i < num_pages; i++)
	{
		for (int j = 0; j < num_pages; j++)
		{
			link_matrix[i][j] = 0;
		}
	}
	
	int num_links=0;
	web_matrix->size = num_pages;

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
	return link_matrix;
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
		*matrix++ = *matrix * scalar;
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

/*
 Function to calculate the final result calculation
 @param column : the vector in question
 @param num_rows : number of lines
*/
void final_result_calculation(int num_pages, float *score_column)
{
	int i,j,page_num=0;
	float max_score;
	
	printf("\nThe stationary state of the walker: \n");
	for (i = 0; i < num_pages; i++) 
	{
		max_score = 0;
		for (j = 0; j < num_pages; j++)
		{
			if (score_column[j] > max_score) 
			{
				max_score = score_column[j];
				page_num = j;
			}
		}
		score_column[page_num] = 0;
		printf("%d) Page %d: %f\n", i + 1, page_num + 1, max_score);
	} 
}

/*
 Function to calculate the initial vector (1/n, 1/n, ... , 1/n)T
 @mean_column : initial vector in  question
 @score_column : score array
 @param num_pages : number of pages in the graph
*/
void initial_vector_calculation(int num_pages, float* score_column)
{
	float entry = 1 / (float) num_pages;
	for (int i = 0; i < num_pages; i++) 
	{
		score_column[i] = entry; 
	}
}

