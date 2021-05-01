
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	int pipePtoC[2];
	int pipeCtoP[2];
	char* CommandBc;	
	int size;			
	if(argc !=2)
	{
		printf("Not enoght input arguments");
		exit(EXIT_FAILURE);
	}

	//Check the size of the input argument from the consle, and add a newline charcter
	size=strlen(argv[1]);
	CommandBc=(char *) malloc((size+1));
	if(CommandBc==NULL)
	{
		printf("Error allocation");
		exit(EXIT_FAILURE);
	}
	strcpy(CommandBc,argv[1]);
	*(CommandBc+size)='\n';


	if(pipe(pipePtoC)<0 || pipe(pipeCtoP)<0)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
			switch(fork())
			{
				case -1:
				{
					printf("Error on fork");
					exit(EXIT_FAILURE);
					break;
				}
				case 0://child
				{	
					close(pipePtoC[1]);//close the output of the pipe at the child for pipe1
					close(pipeCtoP[0]);//close the input of the pipe at the child for pipe2
					if(pipePtoC[1]!= STDOUT_FILENO)
					{
						dup2(pipeCtoP[1],STDOUT_FILENO);//set the output of pipe 2 as standart output
						close(pipeCtoP[1]);
					}   
					if(pipeCtoP[0] != STDIN_FILENO)
					{
						dup2(pipePtoC[0],STDIN_FILENO);//set input pipe 1 as standard input
						close(pipePtoC[0]);
					}
					execlp("bc","bc",(char*) NULL);
					exit(EXIT_SUCCESS);
					break;
				}
				default: //parent
				{	
					char buf[25];//This is the number of bytes read at once from the pipe. It should be smaller tha 4k
					int numRead;
					close(pipePtoC[0]);//close the input of the pipe from the parent to child
					close(pipeCtoP[1]);//close the output of the pipe from child to parent
					if(write(pipePtoC[1],CommandBc,strlen(CommandBc))!=strlen(CommandBc))
					{
						printf("Error on Write");
						exit(EXIT_FAILURE);
					}
					close(pipePtoC[1]);
					for(;;)
					{
						numRead=read(pipeCtoP[0], buf,sizeof(buf));
						if(numRead==-1)
						{
							printf("Error Read");
							exit(EXIT_FAILURE);
						}
						if (numRead==0)
						{
							break;//Child closed its pipe, so exit the for
						}						
						if(write(STDOUT_FILENO,buf,numRead)!=numRead)
						{
							printf("Error on read from child");
							exit(EXIT_FAILURE);
						}
					}
					free(CommandBc);//realocate the memmory
					close(pipeCtoP[0]);
					wait(NULL);
					exit(EXIT_SUCCESS);
					break;
				}
			}
	}
}
