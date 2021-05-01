#include "user.h"
#include <pthread.h>
void *calc_sum(void* Message)
{
	((msg*) Message)->result=((msg*) Message)->Num1+((msg*) Message)-> Num2;
	pthread_exit((void *) Message);
}
