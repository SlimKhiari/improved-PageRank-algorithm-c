#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_calculation.h"
#include "files_management.h"
#include <time.h>

int main(int argc, char *argv[]) 
{
    t_matrix *web_matrix_from_file = NULL;
    
 
   // -------------------------------------------------------------------------------------------------------------------------------------
   //
   //    In this part, if the user has not specified the size of the web
   //    matrix and the file to store it, the execution of the pagerank algorithm will be
   //    based on an existing file (matrix.txt) in which the values ​​are specified and which can be changed manually directly on the file.
   //
   // -------------------------------------------------------------------------------------------------------------------------------------
   
    if(argc==1)
    {
	int num_pages = matrixSize(readFile(M));
	float link_matrix[num_pages][num_pages];
	float score_diff[num_pages], mean_column[num_pages], score_column[num_pages];
	float entry, max_score;
	int i,j,page_num;
	
	web_matrix_from_file = atoMatrix(readFile(M), 0, num_pages); 
		
	initLinkMatrix(num_pages, link_matrix, web_matrix_from_file);
	
	printf("The web graph:\n");
	printMatrix(web_matrix_from_file);
	
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

	
	//print the result
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
	
	deallocMatrix(&web_matrix_from_file);
   }
   
    // -------------------------------------------------------------------------------------------------------------------------------------
   //
   //    This part deals with the case if the user has specified the size of the web matrix and the file to store it.
   //    If the web matrix file does not exist, it will be created randomly with the size entered by the user. 
   //    The user will then have to relaunch the execution command with the same options and then choose 'n' to the question he will have.
   //    If the file already exists,
   //	 AND the number of nodes present in the file is the same as that entered during execution,
   //	 AND regardless of the answer to the question that will be asked,
   //	 then the execution of the pagerank algorithm will be done correctly.
   //
   // -------------------------------------------------------------------------------------------------------------------------------------
   
   //random graphs
   else if(argc>=2)
   {
        int num_pages = atoi(argv[1]);
        char *graph_file_name = argv[2];
        float link_matrix[num_pages][num_pages];
	   time_t t;    srand((unsigned) time(&t));
	   int web_matrix[num_pages][num_pages];
	   int j,i=0;
	   float score_diff[num_pages], mean_column[num_pages], score_column[num_pages];
	   float entry, max_score;
	   int page_num;
	   int pages_number_in_file = matrixSize(readFile(graph_file_name));
	   
	  printf("New random graph ? (press : y for yes, n for no) "); char response ='n'; scanf("%c",&response);
       if(response == 'y')
       {
	   //random web matrix
	   int web_graph[num_pages];
	   for (i = 0; i < num_pages; i++) 
	   {   
       		web_graph[i] = i+1;
	   }
        for (i = 0; i < num_pages; i++)
        {
			for (int j = 0; j < num_pages; j++) 
			{    // shuffle array
			    int temp = web_graph[i];
			    int randomIndex = rand() % num_pages;
			    web_graph[i] = web_graph[randomIndex];
			    web_graph[randomIndex] = temp;
			}
          	for (int k = 0; k < num_pages; k++) 
          	{ 
			    web_matrix[i][k]=web_graph[k];
			}
        }
              	
        //some treatments concerning web graph before pagerank algorithm
        for (i = 0; i < num_pages; i++)
        {
			for (int j = 0; j < num_pages; j++) 
			{    
			    if(web_matrix[i][j] == i+1)
			    {
			   	 web_matrix[i][j] = 0;
			    }
			}
        }
        	 for (i = 0; i < num_pages; i++)
        {
			web_matrix[i][0] = i+1;
        }	
       
       //write the new web graph to the file
	   FILE *fptr = fopen(graph_file_name,"w");
	   fprintf(fptr, "%d\n",num_pages);
        for (i = 0; i < num_pages; i++)
	   {
				for (int j = 0; j < num_pages; j++) 
				{    
				    fprintf(fptr, "%d", web_matrix[i][j]);
				    if(j < num_pages-1)
				    {
				    	  fprintf(fptr, " ");
				    }
				}
				if(i < num_pages-1)
				 {
					fprintf(fptr, "\n");
				 }
		}
		printf("Random graph generation completed. \nYou can now restart the program by choosing 'n' for the next execution by running the same command: ");
		printf("%s ",argv[0]); printf("%s ",argv[1]); printf("%s\n",argv[2]);
	    }
	    else //pageRank
	    {
	    		web_matrix_from_file = atoMatrix(readFile(graph_file_name), 1, num_pages); 	   
	    		printf("The web graph:\n");
	    		printMatrix(web_matrix_from_file);
	    		initLinkMatrix(num_pages, link_matrix, web_matrix_from_file);
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

			
			//print the result
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
			
			deallocMatrix(&web_matrix_from_file);
    	    }
    	}
   
   return 0;
}

