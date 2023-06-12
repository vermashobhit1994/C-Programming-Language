Please check README.md in edit/code/blame view to check actual diagram.

This directory contains files that implements generic linked list .
This is implemented using 
1. Single linked list
2. Double linked list 
3. Circular Single linked list 
4. Circular double linked list 




1. Single linked list 
    Here outer box denotes full node address. 
    
	Step1: Allocate memory dynamically as required by data type 
	       and that depends on number of bytes required by datatype.
	Step2: Fill the data in that memory using pointer used to allocate memory. 
	Step3: Point the data pointer to that memory location.
   
   1. filling character data - i.e. 'a'  
   
       Here pChar is pointer to character that stores data.         
       Here the node data contains address where actual data gets stored.
   
   |-----------------|
   |  +------------+ |     
   |  |0x10 | NULL | |        
   |  +--^---------+ |    
   |-----|-----------|              
     ^   |   0x100       
     |   |     |
     |   |     |---> address of 1st node
     |   |
     |   |----|
     |        |
head = 0x100  |    +-----+ 
              |    |  a  |
              |    +-----+
              |     0x10 
              |      ^ ^  
              |      | |
              |------| |
                       |
                       |
                     pChar									 
	
   2. filling integer data - i.e. 9  
      Here four byts of memory is allocated and then data gets filled. 
	  assume system is little endian.
	  
   Adding 1 more node 
   
   |-----------------|      |-----------------|
   |  +------------+ |      |  +------------+ |     
   |  |0x10 | NULL |=======>|  |0x20 | NULL | |        
   |  +--^---------+ |      |  +--^---------+ |    
   |-----|-----------|      |-----|-----------|              
     ^   |   0x100                |    0x200 ---> address of 2nd node   
     |   |     |                  |
     |   |  address of 1st node   |
     |   |                        |---|
     |   |----|                       |     +-----+-----+-----+-----+
     |        |                       |     | 09  |  00 | 00  | 00  |
    head      |    +-----+            |     +-----+-----+-----+-----+
    0x100     |    |  a  |            |      0x20   0x21  0x22  0x23
              |    +-----+            |       ^ ^  
              |      0x10             |       | |
              |       ^ ^             |-------| |
              |       | |                       |
              |-------| |                       |
                        |                      pInt 
                        |
                       pChar									 

   
   
                                                             
     
   3. filling float data - i.e. 3.00 
      Here four byts of memory is allocated and then data gets filled. 
	  assume system is little endian.
	  
   Adding 1 more node 
   
   |-----------------|       |-----------------|       |-----------------|   
   |  +------------+ |       |  +------------+ |       |  +------------+ |     
   |  |0x10 | NULL |========>|  |0x20 | 0x300|========>|  |0x30 | NULL | |       
   |  +--^---------+ |       |  +--^---------+ |       |  +--^---------+ |    
   |-----|-----------|       |-----|-----------|       |-----|-----------|              
     ^   |   0x100                 |    0x200                |    0x300 --> address of 3rd node 
     |   |     |                   |      |                  |
     |   |  address of 1st node    |   address of 2nd node   |
     |   |                         |                         |-------------|
     |   |                         |----|                                  |
     |   |-------|                      |     +-----+-----+-----+-----+    |
     |           |                      |     | 09  |  00 | 00  | 00  |    |
head = 0x100     |   +-----+            |     +-----+-----+-----+-----+    |
                 |   |  a  |            |      0x20   0x21  0x22  0x23     |
                 |   +-----+            |       ^ ^                        |
                 |     0x10             |       | |                        | 
                 |      ^ ^             |-------| |                        | 
                 |      | |                       |                        |    +-----+-----+-----+-----+
                 |------| |                       |                        |    | 03  |  00 | 00  | 00  |
                          |                      pInt                      |    +-----+-----+-----+-----+
                          |                                                |      0x30  0x31  0x32  0x33     
                          pChar                                            |     ^ ^
                                                                           |     | |       
                                                                           |-----| |
                                                                                   |
                                                                                pFloat 

	 	
		
	4. filling struct data  
    Here four byts of memory is allocated and then data gets filled. 
	  
       struct test
       {char a, int b};	   //4+4=8bytes
        struct test t = {.a = 7, .b = 8}; 
	
    Adding 1 more node 
      Here four byts of memory is allocated and then data gets filled. 
	  assume system is little endian.
	  
                                                             
     
   
   |-----------------|       |-----------------|       |-----------------|         |-----------------|   
   |  +------------+ |       |  +------------+ |       |  +------------+ |         |  +------------+ |     
   |  |0x10 | NULL |========>|  |0x20 | 0x300|========>|  |0x30 | 0x400| |========>|  |0x40 | NULL | |       
   |  +--^---------+ |       |  +--^---------+ |       |  +--^---------+ |         |  +--^---------+ |    
   |-----|-----------|       |-----|-----------|       |-----|-----------|         |-----|-----------|              
     ^   |   0x100                 |    0x200                |    0x300                  |   0x400
     |   |     |                   |      |                  |     |                     |    |
     |   |  address of 1st node    |   address of 2nd node   |    address of 3rd node    |   address of 4th node
     |   |                         |                         |-------------|             |
     |   |                         |----|                                  |  |----------|     
     |   |-------|                      |     +-----+-----+-----+-----+    |  |  
     |           |                      |     | 09  |  00 | 00  | 00  |    |  |  +-----+-----+-----+-----+-----+-----+-----+-----+
head = 0x100     |   +-----+            |     +-----+-----+-----+-----+    |  |  | 07  |  00 | 00  | 00  | 08  |  00 | 00  | 00  |
                 |   |  a  |            |      0x20   0x21  0x22  0x23     |  |  +-----+-----+-----+-----+-----+-----+-----+-----+ 
                 |   +-----+            |       ^ ^                        |  |    0x40  0x41  0x42  0x43  0x44  0x45  0x46  0x47
                 |     0x10             |       | |                        |  |    ^ ^   
                 |      ^ ^             |-------| |                        |  |    | |
                 |      | |                       |                        |  |----| | 
                 |------| |                       |                        |         |
                          |                      pInt                      |         |
                          |                                                |         |   
                          pChar                                            |       pStruct
                                                                           |            
                                 +-----+-----+-----+-----+                 |
                                 | 03  | 00  | 00  | 00  |                 |
                                 +-----+-----+-----+-----+                 |                                  
                                  0x30  0x31  0x32  0x33                   |
                                  ^ ^                                      |
                                  | |                                      |
                                  | |--------------------------------------| 
                                  |                     
                                pFloat
