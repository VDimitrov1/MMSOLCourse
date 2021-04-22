
#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include <pthread.h>

#include <errno.h>
#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
              do { perror(msg); exit(EXIT_FAILURE); } while (0)


int main(int argc, char** argv)
{
        int s;
	pthread_t thread;
	void* res;
           msg *Parameters = (msg *)malloc(sizeof(msg));	
	if(argc==3)
	{
 		Parameters->Num1=strtol(argv[1],NULL,10);
		Parameters->Num2=strtol(argv[2],NULL,10);
 		s=pthread_create(&thread,NULL,&calc_sum,(void *)Parameters);
 		if(s != 0)
		{
			handle_error_en(s,"pthread_create");
		}
	
		pthread_join(thread,&res);
		if (s != 0)
		{
                   handle_error_en(s, "pthread_join");
		}
 		
		printf("The first number is %ld, the second %ld and the sum is %d",strtol(argv[1],NULL,10),strtol(argv[2],NULL,10),((msg*)res)->result);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Invalid number of parameters");
	}
}
