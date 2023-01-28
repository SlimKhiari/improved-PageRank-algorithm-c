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
  @param r : r = 1 => random, r = 0 => not random 
  @param matrix_size : matrix_size
*/
t_matrix* atoMatrix(char* str,int r, int matrix_size)
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

	if(r == 0)
	{
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
	}
	else
	{
		sscanf(current_position,"%s", tmp);
		size=atoi(tmp);
		current_position += strlen(tmp)+1;
		mat = allocMatrix(size);
		
		if(size != matrix_size)
		{
			printf("The matrix size entered and the matrix size in the file selected are different!\n");
			exit(1);
		}
				
		for(i=0; i<mat->size ; i++)
		{
			for(j=0; j<mat->size ; j++)
			{
				sscanf(current_position,"%s", tmp);
				current_position += strlen(tmp)+1;
				mat->coeffs[i][j] = atof(tmp);
			}
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
  Function to allocate memory space for float matrix
  @param size : the size of the transition matrix
*/
float** floatAlocDynamic_2D( int size )
{
    float **mat = ( float ** )malloc( size * sizeof( float * ) );

    for ( int i = 0; i < size; i++ )
    {
        mat[i] = ( float * )malloc( size * sizeof( float ) );
        for(int j=0; j<size ; j++)
	   {
			mat[i][j] = -1;
	   }
    }

    return mat;
}

/*
  Function to allocate memory space for a ector
  @param size : the size of the vector
*/
float* floatAlocDynamic_1D(int size)
{
	float *vect = malloc(size * sizeof(float));
	for( int i = 0; i < size; i++)
	{
	   vect[i] = -1;
	}
	return vect;
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
  Function to print a t_matrix matrix
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
  Function to print a matrix (with some operations)
  @param num_pages : number of pages
  @transition_matrix : transition matrix to be printed
  @transition : transition matrix to be used in pagerank algorithm
  @mean_column : initial vector to be user in pagerank algorithm
  @initial_vector : initial vector entered by the user
*/
void printFloatMatrix(int num_pages, float **transition_matrix, float transition[num_pages][num_pages], float mean_column[num_pages], float *initial_vector)
{
	for(int i=0; i<num_pages; i++)
	{
		for(int j=0; j<num_pages; j++)
		{
			transition[i][j] = transition_matrix[i][j];
			printf("%f ",transition_matrix[i][j]);
		}
		mean_column[i] = initial_vector[i];
		printf("\n");
	}
}

/*
  Function to deallocate the allocated space for 2D t_matrix table
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

/*
  Function to deallocate the allocated space for 2D float table
  @param mat : the matrix to be deallocated
*/
void deallocFloatMatrix_2D(float** mat, int size)
{
    for(int i = 0; i < size; i++)
    {
        free(mat[i]);
    }
    free(mat);
	
	return;
}

/*
  Function to deallocate a vector
  @param mat : the matrix to be deallocated
*/
void deallocFloatVector_1D(float* vect)
{
    free(vect);
	
	return;
}
