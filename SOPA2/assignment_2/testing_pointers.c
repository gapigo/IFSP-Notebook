#include <stdio.h>

//function prototype
void printString(void *ptr);

int main()
{
	char *str="Hi, there!";
	
	printString(str);
	
	return 0;
}

//function definition
void printString(void *ptr)
{
	printf("str: %s\n",ptr);
}

