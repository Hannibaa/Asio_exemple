#include <stdio.h>



int main()
{
	volatile unsigned char* ptr = (unsigned char*)(0x40'00'00'00);

	printf("get one char at [%p] = [%d]", ptr, *ptr);





	return 0;
}