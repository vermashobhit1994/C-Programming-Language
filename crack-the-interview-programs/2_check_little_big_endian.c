/* program to check whether system is little or big endian */

#include <stdio.h>
#include <stdint.h>


/*
    
    
	example: 
	
    ----------------------------------------
	AAAA AAAA BBBB BBBB CCCC CCCC DDDD DDDD 
	----------------------------------------
                    
	----------------------------------------				
					              AAAA AAAA
						BBBB BBBB 
			  CCCC CCCC			
	DDDD DDDD
	----------------------------------------
	
    ----------------------------------------
    DDDD DDDD CCCC CCCC BBBB BBBB AAAA AAAA
	-----------------------------------------
	

*/

/* function to convert from little to big and big to little endian */
uint32_t convertToEndian(uint32_t data)
{
	uint32_t result = 0;
	result = ((data & 0xFF000000U) >> 24)   | 
	         ((data & 0x00FF0000U) >> 8)   |
             ((data & 0x0000FF00U) << 8)    |
			 ((data & 0x000000FFU) << 24)    ;
	
	return result;
					   
}


void checkMachineLittleOrBigEndian(void)
{
	uint32_t data = 0x1U;
	
	
	if( (uint32_t)(((uint8_t*)&data)[0]) != 0x1U)
		printf("big endian\n");        //higher bytes is at higher address   	 
    else
		printf("little endian\n");   //lower byte is at lowest address
		
}

void checkMachineLittleOrBigEndian_ViaUnion(void)
{
	union
	{
		uint32_t data_u32;
		uint8_t data_u8[0];
	} u = {0x01000000};
	
	if (u.data_u8[0] == 0x01U)
		printf("big endian\n");
	else if (u.data_u8[0] == 0x00U)
		printf("little endian \n");
}

int main(void)
{
	uint32_t var = 0xAABBCCDD;
	
	/* 0x76543210 is written in little endian as 
	   0111 0110 0101 0100 0011 0010 0001 0000
	   
	   0x76543210 is written in big endian as 
	   
    */
    
	checkMachineLittleOrBigEndian();
	checkMachineLittleOrBigEndian_ViaUnion();
	//convert into big endian
	var = convertToEndian (var);
	printf("%#x\n", var);
	
	var = convertToEndian (var);
	printf("%#x\n", var);
	
	
}