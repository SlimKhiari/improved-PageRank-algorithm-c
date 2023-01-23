#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_calculation.h"
#include "files_management.h"

int main() 
{

	int num_pages = matrixSize(readFile(M));
	float link_matrix[num_pages][num_pages];
	float score_diff[num_pages], mean_column[num_pages], score_column[num_pages];
	float entry, max_score;
	int i,j,page_num;
	t_matrix *web_matrix = NULL;
	
	
	web_matrix = atoMatrix(readFile(M)); //ASCII TO MATRIX
		
		
	initLinkMatrix(num_pages, link_matrix, web_matrix);
	
	
	printf("The web graph:\n");
	printMatrix(web_matrix);
	
	printf("\nThe transition matrix:\n");
	for(int i=0; i<num_pages; i++)
	{
		for(int j=0; j<num_pages; j++)
		{
			printf("%f ",link_matrix[i][j]);
		}
		printf("\n");
	}
	
	
	entry = 1 / (float) num_pages;
	for (i = 0; i < num_pages; i++) 
	{
		mean_column[i] = entry; score_column[i] = entry; // (1/n, 1/n, ... , 1/n)T
	}
	
	
	scalarMultiplication(link_matrix[0], num_pages, num_pages, DAMPING_FACTOR); //alpha * P
	scalarMultiplication(mean_column, num_pages, 1, 1-DAMPING_FACTOR); // (1-alpha) * (1/n, 1/n, ... , 1/n)T
	
	//pageRank convergence
	do 
	{
		for (i = 0; i < num_pages; i++)
		{
			score_diff[i] = score_column[i];
		}
		columnMultiplication(link_matrix[0], num_pages, num_pages, score_column); 
		addition(score_column, mean_column, num_pages, 1); 
		scalarMultiplication(score_diff, num_pages, 1, -1);
		addition(score_diff, score_column, num_pages, 1);
	} while (norm(score_diff, num_pages) > TOLERANCE);


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
	
	
	deallocMatrix(&web_matrix);
	return 0;
}

