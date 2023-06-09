/* program to dynamically allocate 1D, 2D and 3D arrays */


#include <stdio.h>
#include <stdlib.h> //calloc()
int main()
{
	
	int no_of_elements = 0;
	

	/***************** 1D array Operations *****************************************************************/
	//input no of elements for 1D array 
	printf ("Enter no of elements for 1D array :   " );
	scanf("%d",&no_of_elements);
	
	//allocate memory to 1D array 
	int* _1DArray = (int*)calloc(no_of_elements, sizeof(int));
 
	printf("Now enter elements \n");
	
	//fill data for 1D array 
	for(int i=0; i< no_of_elements; i++)
		scanf("%d", &_1DArray[i]);
	
	printf("elements are \n");
	//print data for 1D array 
	for(int i=0; i<no_of_elements; i++)
		printf("%d, ", _1DArray[i]);
	
	printf("\n\n");
	fflush(stdin);
	
	
	
    /*********************************************************************************************/ 
	
	
	/***************** 2D array Operations *****************************************************************/
	
	//input no of elements for 2D array 
	printf ("Enter no of elements for 2D array :   " );
	scanf("%d",&no_of_elements);
	
	int rows = 0;
	printf ("Enter no of rows for 2D array :   " );
	scanf("%d",&rows);
	
	//allocate memory for no of rows in 2D array
	//here each element is pointer to store address of element 
	int** _2DArray = (int**)calloc(rows, sizeof(int*));
 
	int cols = no_of_elements/rows;
	
	printf("Now enter elements \n");
	//fill data for 1D array 
	//for(int i=0; i<sizeof(2DArray)/sizeof(2DArray[0]); i++) //sizeof() gives sizeof pointer insted of no of elements x size of each element
	for(int i=0; i < rows;i++)
	{
		//allocate memory for each element 
		_2DArray[i] = (int*)calloc(cols, sizeof(int) );
		for(int j=0; j < cols; j++)
			scanf("%d", &_2DArray[i][j]);
	}
	
	printf("elements are \n");
	//print data for 2D array 
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j < cols; j++)
			printf("%d, ", _2DArray[i][j]);
		printf("\n");
	}
	
	/*********************************************************************************************/ 
	
}