#include "files_management.h"

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

t_matrix* atoMatrix(char* str) //ASCII TO MATRICE (like atof/atoi)
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

char* readFile(char* fichier)
{
	FILE* fichier_lu = NULL;
	char* phrase = NULL;
	char tmp[TAILLE_TAMPON]="";

	fichier_lu = fopen(fichier,"r");

	if(fichier_lu == NULL)
	{
		fprintf(stderr,"Failed to open file to read\"%s\".\n",fichier);
		phrase = NULL;
	}
	else
	{
		phrase = (char*)malloc(1*sizeof(char));
		phrase[0]='\0';

		while( fgets(tmp,TAILLE_TAMPON,fichier_lu) )
		{
			phrase = (char*)realloc(phrase,(strlen(phrase)+strlen(tmp)+1)*sizeof(char));
			strcpy(phrase+strlen(phrase),tmp);
		}
	}

	fclose(fichier_lu);

	return phrase;
}

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

void desallocMatrix(t_matrix** mat)
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

