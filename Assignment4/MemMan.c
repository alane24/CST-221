//Audrey Lane 10/22/2020
//This assignment will have a user input a decimal number between 0 and 4095. It will display the number as a 32-bit binary number and show hte number as a 32-bit hexidecimal number. The input will shift the number 16 bits to the left then mask out and the hex number 0x07FF to produce the final number. The final result will show in binary, hex and decimal. 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char* decimal_to_binary(int n)
{
	char* returning = malloc(32 +1); //31 bits 
	int count = 0;
	if (returning == NULL)
		exit(EXIT_FAILURE);
	for (int idx = 32; idx >=0; idx--) {
		int current = (n >> idx) & 1; 
		if (current == 1) {
			*(returning + count) = '1';
		} 
		else 
		{
			*(returning + count) = '0';
		}
		count++;
	}
	return returning;
}

char* decimal_to_hex(int n)
{
	char* accum = malloc(sizeof(char) * 10);
	if (accum == NULL) {
		exit(EXIT_FAILURE); //if number is not base-10 it will end program
	}
	
}

int main()
{ 
	int input;
	printf("Input a base-10 number. Has to be between 0 and 4095: \n"); //has user input number
	scanf("%i", &input);
	printf("\nNumber entered: %i\n", input);
	
	if (input < 0 || input > 4096) {
		printf("Number entered is not in range. EXITING OUT!\n"); //number needs to be in range
		return 1;
	}
	
	printf("Binary: %s\n", decimal_to_binary(input)); 
	
	printf("Hexidecimal: 0x%X\n", input);
	
	input = input << 16;
	printf("Enter shifted 16 bits left: %s\n", decimal_to_binary(input));
	// shifts to the left
	
	input &= 0x00001111;
	printf("Enter last 16 bits masked out: %s\n", decimal_to_binary(input));
	//masks out
	
	input |= 0x07FF;
	printf("Enter after 0x07FF: %i\n", input);
	//hex number
	
	printf("Result for decimal: %i\n", input);
	printf("Result for binary: %d\n", input);
	printf("Result for hexidecimal: %X\n", input);
	return 0;
	// prints all outputs
} 
