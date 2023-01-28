#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_calculation.h"
#include "files_management.h"
#include <time.h>

   // -------------------------------------------------------------------------------------------------------------------------------------
   //
   //    [ PAGERANK ALGORITHM ]
   //    a function accepting as inputs the transition matrix, the juming parameters as well as an initial vector
   //    and at output the vector representing the stationary state calculated by the PageRank  algorithm
   //
   // -------------------------------------------------------------------------------------------------------------------------------------

void cPageRank(float** transition_matrix, float dumping_factor, int number_of_pages, float* initial_vector, char* file)
{
	float transition[number_of_pages][number_of_pages];
	float score_diff[number_of_pages], score_column[number_of_pages], mean_column[number_of_pages];
	t_matrix *web_matrix_from_file = atoMatrix(readFile(file), 0, number_of_pages); 
	float max_score;
		
	initLinkMatrix(number_of_pages, transition_matrix, web_matrix_from_file);
	
	printf("The web graph:\n");
	printMatrix(web_matrix_from_file);
	printf("\nThe transition matrix:\n");
	printFloatMatrix(number_of_pages, transition_matrix, transition, mean_column, initial_vector);
	
	
	initial_vector_calculation(number_of_pages, score_column); // (1/n, 1/n, ... , 1/n)T
	scalarMultiplication(transition[0], number_of_pages, number_of_pages, dumping_factor); //alpha * P
	scalarMultiplication(mean_column, number_of_pages, 1, 1-dumping_factor); // (1-alpha) * (1/n, 1/n, ... , 1/n)T
	
	do //pagerank convergence 
	{
		for (int i = 0; i < number_of_pages; i++)
		{
			score_diff[i] = score_column[i];
		}
		columnMultiplication(transition[0], number_of_pages, number_of_pages, score_column); 
		addition(score_column, mean_column, number_of_pages, 1); 
		scalarMultiplication(score_diff, number_of_pages, 1, -1);
		addition(score_diff, score_column, number_of_pages, 1);
	} while (norm(score_diff, number_of_pages) > TOLERANCE);

	final_result_calculation(number_of_pages, max_score, score_column);
	
	deallocMatrix(&web_matrix_from_file);
}

int main(int argc, char *argv[]) 
{  
   // -------------------------------------------------------------------------------------------------------------------------------------
   //
   //    [ CUSTOMIZED GRAPHS ]
   //    In this part, if the user has not specified the size of the web
   //    matrix and the file to store it, the execution of the pagerank algorithm will be
   //    based on an existing file (matrix.txt) in which the values ​​are specified and which can be changed manually directly on the file.
   //
   // -------------------------------------------------------------------------------------------------------------------------------------
   
    if(argc==1)
    {
	
	int number_of_pages = matrixSize(readFile("matrix.txt")); 
	float entry = 1 / (float) number_of_pages;
	float** link_matrix = floatAlocDynamic_2D(number_of_pages); 
	float *initial_vector = floatAlocDynamic_1D(number_of_pages);

	for (int i = 0; i < number_of_pages; i++) 
	{
		initial_vector[i] = entry; 
	}
	
	cPageRank(link_matrix, 0.85, number_of_pages, initial_vector, "matrix.txt");
	
	deallocFloatMatrix_2D(link_matrix, number_of_pages);
	deallocFloatVector_1D(initial_vector);
	
   }
   
   // -------------------------------------------------------------------------------------------------------------------------------------
   //
   //    [ RANDOM GRAPHS ]
   //    This part deals with the case if the user has specified the size of the web matrix and the file to store it.
   //    If the web matrix file does not exist, it will be created randomly with the size entered by the user. 
   //    The user will then have to relaunch the execution command with the same options and then choose 'n' to the question he will have.
   //    If the file already exists,
   //	 AND the number of nodes present in the file is the same as that entered during execution,
   //	 AND regardless of the answer to the question that will be asked,
   //	 then the execution of the pagerank algorithm will be done correctly.
   //
   // -------------------------------------------------------------------------------------------------------------------------------------
  
   else if(argc>=2)
   {
    	  int number_of_pages; number_of_pages = atoi(argv[1]); 
       char *graph_file_name = argv[2];
	  int web_matrix[number_of_pages][number_of_pages];
	   
	  time_t t;    srand((unsigned) time(&t));
	   
	  printf("New random graph ? (press : y for yes, n for no) "); char response ='n'; scanf("%c",&response);
       if(response == 'y') //write a new graph in the file
       {
	   //generate a random web matrix & write it in the file
	   FILE *fptr = fopen(graph_file_name,"w");
	   fprintf(fptr, "%d\n",number_of_pages);
	   int web_graph[number_of_pages];
	   for (int i = 0; i < number_of_pages; i++) 
	   {   
       		web_graph[i] = i+1;
	   }
        for (int i = 0; i < number_of_pages; i++)
        {
			for (int j = 0; j < number_of_pages; j++)  // shuffle array
			{   
			    int temp = web_graph[i];
			    int randomIndex = rand() % number_of_pages;
			    web_graph[i] = web_graph[randomIndex];
			    web_graph[randomIndex] = temp;
			}
          	for (int j = 0; j < number_of_pages; j++) 
          	{ 
			    web_matrix[i][j]=web_graph[j];
			    if(web_matrix[i][j] == i+1)
			    {
			   	 web_matrix[i][j] = 0;
			    }
			}
			web_matrix[i][0] = i+1;
			for (int j = 0; j < number_of_pages; j++) 
			{    
				fprintf(fptr, "%d", web_matrix[i][j]);
				if(j < number_of_pages-1)
				{
				    	fprintf(fptr, " ");
				}
			}
			if(i < number_of_pages-1)
			{
				fprintf(fptr, "\n");
			}
         }
       
		    printf("Random graph generation completed. \nYou can now restart the program by choosing 'n' for the next execution by running the same command: ");
		    printf("%s ",argv[0]); printf("%s ",argv[1]); printf("%s\n",argv[2]);
	   }
	   else //pageRank
	   {		
			float entry = 1 / (float) number_of_pages;
			float** link_matrix = floatAlocDynamic_2D(number_of_pages); 
			float *initial_vector = floatAlocDynamic_1D(number_of_pages);

			for (int i = 0; i < number_of_pages; i++) 
			{
				initial_vector[i] = entry; 
			}
			
			cPageRank(link_matrix, 0.85, number_of_pages, initial_vector, graph_file_name);
			
			deallocFloatMatrix_2D(link_matrix, number_of_pages);
			deallocFloatVector_1D(initial_vector);
    	   }
    	}
    	    	      
   return 0;
}

