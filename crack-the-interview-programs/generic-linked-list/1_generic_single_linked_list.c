/* program to implement generic linked list using single linked list 
   For more details read README.md in current folder.

*/
#include <stdio.h>
#include <stdlib.h> //for calloc()
#include <stdint.h>//for uint8_t, uint32_t
#include <string.h>

typedef enum
{
	INT=1,
	FLOAT,
	STRING,
	CHAR,
	STRUCT,
	ARRAY,
}dataType;


/* structure that is shared between user and linked list */
typedef struct
{
	int bytesNum; //used when storing data 
	void* pData;  //used when printing data
	dataType dType; //tells datatype because different data type may occupy same bytes
}dataInfo;




typedef struct Test
{
	char c ;          //1 bytes + 3 bytes padded 
	int i;            //4 bytes 
	uint32_t array[10];  //10 bytes 
	                 //2bytes padded 
}test;



// single linked list element. 
typedef struct single_linked_list_node
{
	dataInfo data;
	struct single_linked_list_node* link;
}Single_List_Node;


static void print_bytes_test(void)
{
	uint32_t num = 0x12345678;
	
	uint8_t bytesNum = sizeof(num);
	
	void* pData = &num;
	
	void* pResult = 0;
	pResult = calloc(bytesNum, sizeof(uint8_t));
	
	for(int i=0; i < bytesNum ; i++)
	{
		
		//((uint8_t*)pResult)[i] = ((uint8_t*)pData)[i];
		*((uint8_t*)(pResult+i)) = *((uint8_t*)(pData+i));
		
	}
	printf("%#x\n",*(uint32_t*)pResult); 
}


void printStructBytes(void* pStructData)
{
	printf("\n\n\n");
	for(int i=0; i < sizeof(struct Test) ;i++)
	{
		if ( ((i >> 2) & 0x1) ==1)
				printf("\n");
		printf("%x",  ((uint8_t*)pStructData)[i] );
	}
	printf("\n\n\n");
}

void create_single_list(Single_List_Node** pHead, Single_List_Node** pLast, const dataInfo* pDataInfo)
{
	Single_List_Node* pNewNode = NULL;
	
	
    //Step1: Create a node 
	pNewNode = calloc(1, sizeof(Single_List_Node) );

    if(pNewNode )
	{
		
		//fill data into new node

		
		if (pDataInfo -> dType == ARRAY)
		{
			//allocate memory for each integer value 
			pNewNode -> data.pData = calloc(pDataInfo -> bytesNum, sizeof(uint32_t) );
		
			for(int i=0; i < pDataInfo -> bytesNum; i++)
				((uint32_t*)(pNewNode ->data.pData ))[i] = ((uint32_t*)(pDataInfo -> pData))[i] ; //fill with 4 bytes 
		}
		else 
		{
			//create memory for no of bytes used by data 
			pNewNode -> data.pData = calloc(pDataInfo -> bytesNum, sizeof(uint8_t) );
		
			for(int i=0; i < pDataInfo -> bytesNum; i++)
				((uint8_t*)(pNewNode ->data.pData ))[i] = ((uint8_t*)(pDataInfo -> pData))[i] ;
		}
		pNewNode ->data.dType = pDataInfo -> dType;
		pNewNode ->data.bytesNum = pDataInfo ->bytesNum;
		
		
		pNewNode -> link = NULL;
		
		//link head pointer 
		if(*pHead == NULL)
			*pHead = pNewNode;
		else
			(*pLast) -> link = pNewNode;
		
		//update last with last node inserted
		*pLast = pNewNode;
	}		
}


static void printChar(void* pCharData)
{
	printf("printing char data \n");
	printf("%c", *((uint8_t*)pCharData) );
	printf("\n");
}

static void printInt(void* pIntData)
{
	printf("printing integer data \n");
	printf("%d", *((uint32_t*)pIntData) );
	printf("\n");
}

static void printString(void* pStringData)
{
	printf("printing string data \n");
	printf("%s", ((char*)pStringData) );
	printf("\n");
}

static void printFloat(void* pFloatData)
{
	printf("printing float data \n");
	printf("%f", *((float*)pFloatData) );
	printf("\n");
}

static void printArray(void* pArrayData, const int bytesNum)
{
	printf("printing array data \n");
	for(int i=0; i < bytesNum;i++)
		printf("%d, ", ((uint32_t*)pArrayData)[i] );
	printf("\n");
}


static void printStruct(void* pStructData)
{
	printf("printing struct  data \n");
	struct Test tData = *(struct Test*)pStructData;
	
	printf("%c %d \n",tData.c, tData.i)   ;
	
	//int arrayLength = sizeof(tData.array)/sizeof((tData.array)[0]);
	int arrayLength = 3;
	printArray(tData.array, arrayLength );
	
	printf("\n");
}



/** 
  * \brief         - function to display data using function pointer.
  * \param[in2]    - function name that tells data type pointer to be printed.
  * \param[in1]    - pointer to first node 
  */
void display_single_list(const Single_List_Node* pHead)
{
	//declaration of function pointer 
	void(*pFunc)(void* pData);
	
	while(pHead != NULL)
	{
		if(pHead -> data.dType == INT)
			pFunc  = printInt;
		else if (pHead -> data.dType == FLOAT)
			pFunc  = printFloat;
		else if (pHead -> data.dType == STRING)
			pFunc  = printString;
		else if (pHead -> data.dType == CHAR)
			pFunc  = printChar;
	
		else if (pHead -> data.dType == STRUCT)
			pFunc  = printStruct;
		
		 
		if (pHead -> data.dType == ARRAY)
		{
			printArray(pHead -> data.pData, pHead -> data.bytesNum);
			
			pHead = pHead -> link;

			continue;
			
        }
	

		
		//calling via function pointer 
      	(*pFunc)(pHead -> data.pData);
    	
		pHead = pHead -> link;
	    
	}
		
		
	
		
}



void free_list(Single_List_Node* pHead)
{
	Single_List_Node* pCurrentNode = NULL;
	while(pHead != NULL)
	{
		pCurrentNode = pHead;
		pHead = pHead -> link;
		
		//free memory used by data
		free(pCurrentNode -> data.pData);
			
		pCurrentNode -> data.pData = NULL; //prevent becoming dangling pointer 
		
		//free current node 	
		free(pCurrentNode);
		pCurrentNode = NULL;
	}
}


int main()
{
	(void)print_bytes_test;
	
	Single_List_Node* pHead = NULL;
	Single_List_Node* pLast = NULL;
	
	char dataChar = 'A';
	dataInfo data = {.pData = &dataChar, .bytesNum = sizeof(dataChar), .dType=CHAR };
	create_single_list(&pHead, &pLast, (&data));
	
	uint32_t dataInt = 9;
	data.pData = &dataInt;
	data.bytesNum = sizeof(dataInt);
	data.dType = INT;
	create_single_list(&pHead, &pLast, (&data) );
	
	
	
	float dataFloat = 3.14;
	data.pData = &dataFloat;
	data.dType = FLOAT;
	data.bytesNum = sizeof(dataFloat);
	create_single_list(&pHead, &pLast, (&data) );
	
	
	uint32_t dataArray[5] = { 1, 2, 3, 4, 5};
	data.pData = dataArray;
	data.bytesNum = sizeof(dataArray)/sizeof(dataArray[0]);
	data.dType = ARRAY;
	create_single_list(&pHead, &pLast, (&data) );
	
	
	char* dataString = "shobhit";
	data.pData = dataString;
	data.bytesNum = strlen(dataString)+1;
	data.dType = STRING;
	create_single_list(&pHead, &pLast, (&data) );
	
	
	test dataStruct = {.c = 'B', .i = 8, .array = {10, 20, 30} };
	
	data.pData = &dataStruct;
	data.bytesNum = sizeof(dataStruct);
	data.dType = STRUCT;
	create_single_list(&pHead, &pLast, (&data) );
	
	
	//display list 
	display_single_list(pHead);
	
	free_list(pHead);
}



