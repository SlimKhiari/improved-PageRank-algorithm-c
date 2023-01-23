#include "files_management.h"

/*
 Function to retrieve the size of the matrix representing the graph from the .txt file
 @param str : the file read
*/
int matrixSize(char* str)
{
	int lig=0;char tmp[20] = {0};	char* current_position=str;
	
	if(str == NULL )
	{
		fprintf(stderr,"Empty input string failed\n");
		return 0;
	}
	
	sscanf(current_position,"%s", tmp);
	lig=atoi(tmp);
	current_position += strlen(tmp)+1;
	
	return lig;
}

/*
  Function to make the transition from ASCII TO MATRICE (like atof/atoi)
  @param str : the file read
*/
t_matrix* atoMatrix(char* str) 
{
	t_matrix* mat=NULL;
	char* current_position=str;
	char tmp[20] = {0};
	int i=0,j=0;
	int size=0;

	if(str == NULL )
	{
		fprintf(stderr,"Empty input string failed\n");
		return NULL;
	}

	sscanf(current_position,"%s", tmp);
	size=atoi(tmp);
	current_position += strlen(tmp)+1;

	mat = allocMatrix(size);

	for(i=0; i<mat->size ; i++)
	{
		for(j=0; j<mat->size ; j++)
		{
			sscanf(current_position,"%s", tmp);
			current_position += strlen(tmp)+1;
			mat->coeffs[i][j] = atof(tmp);
		}
	}

	return mat;
}

/*
  Function to make the transition from ASCII TO MATRICE (like atof/atoi)
  @param file : the file name
*/
char* readFile(char* file)
{
	FILE* read_file = NULL;
	char* phrase = NULL;
	char tmp[TMP]="";

	read_file = fopen(file,"r");

	if(read_file == NULL)
	{
		fprintf(stderr,"Failed to open file to read\"%s\".\n",file);
		phrase = NULL;
	}
	else
	{
		phrase = (char*)malloc(1*sizeof(char));
		phrase[0]='\0';

		while( fgets(tmp,TMP,read_file) )
		{
			phrase = (char*)realloc(phrase,(strlen(phrase)+strlen(tmp)+1)*sizeof(char));
			strcpy(phrase+strlen(phrase),tmp);
		}
	}

	fclose(read_file);

	return phrase;
}

/*
  Function to allocate memory space for matrix
  @param size : the size of the matrix
*/
t_matrix* allocMatrix(int size)
{
	t_matrix* mat = NULL;
	int i = 0,j=0;
	
	mat = (t_matrix*)malloc(sizeof(t_matrix));
	
	if(mat == NULL )
	{
		fprintf(stderr,"Failure alloc_matrice_1() not enough memory\n");
		return NULL;
	}
	
	mat->size = size;
	
	mat->coeffs = (float**)malloc(mat->size*sizeof(float*));
	for(i=0; i<mat->size ; i++)
	{
		mat->coeffs[i] = (float*)malloc(mat->size*sizeof(float));
		for(j=0; j<mat->size ; j++)
		{
			mat->coeffs[i][j] = -1;
		}
	}

	return mat;
}

/*
  Function to print a 2D table
  @param size : the size of the matrix
  @param tab: the 2D table to be printed
*/
void printTab2D(float** tab, int size)
{
	int i=0,j=0;
	
	if(tab == NULL)
	{
		printf("table does not exist...\n");
		return;
	}
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%3f ",tab[i][j]);
		}
		printf("\n");
	}

	return;
}

/*
  Function to print a matrix
  @param mat : the matrix to be printed
*/
void printMatrix(t_matrix* mat)
{
	if(mat == NULL )
	{
		fprintf(stderr,"Failed aff_matrix() not possible\n");
		return;
	}
	
	printTab2D(mat->coeffs,mat->size);

	return;
}

/*
  Function to deallocate the allocated space for 2D table
  @param mat : the matrix to be deallocated
*/
void deallocMatrix(t_matrix** mat)
{
	int i=0;

	if(*mat == NULL )
	{
		fprintf(stderr,"Nothing to dealloc_matrice()\n");
		return;
	}

	for(i=0; i<(*mat)->size ; i++)
	{
		free((*mat)->coeffs[i]);
	}
	free((*mat)->coeffs);
	free(*mat);
	
	*mat = NULL;
	
	return;
}

