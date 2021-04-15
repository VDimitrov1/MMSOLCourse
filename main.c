#include <stdio.h>
#include <stdlib.h>
#include "user.h"
int main(int argc, char** argv)
{
	if(argc==3)
	{
  		printf("The first number is %ld, the second %ld and the sum is %d",strtol(argv[1],NULL,10),strtol(argv[2],NULL,10),calc_sum(strtol(argv[1],NULL,10),strtol(argv[2],NULL,10)));
		return 1;
	}
	else
	{
		printf("Invalid number of parameters");
	}
}
