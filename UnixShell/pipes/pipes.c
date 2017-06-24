#include "pipes.h"
#include "../tokenize/makeArgs.h"


int containsPipe(char *s)
{
	
	
    int i, len = strlen(s);
    int count = 0;
    for(i=0;i<len;i++)
    {
        if(s[i] == '|') count++; //increment count only if c found
    }
         
    
    return count; 
	
	
}




char ** parsePrePipe(char *s, int * preCount) // GET FIRST HALF OF STRING AND THEN PASS IT INTO MAKEARGS
{
	char ** prePipe = NULL;
	
	int tokens = 0;
	int len= strlen(s);
	
	
	char firstHalf[9999];
	
	strcpy(firstHalf,s);
	

	char *str = firstHalf;

	char *str1 = strsep(&str, "|");// pipe 1

	tokens = makeargs(str1, &prePipe);
	
	//printargs(tokens-1,prePipe);
	
	*preCount = tokens;
	
	return prePipe;
	
}


char ** parsePostPipe(char *s, int * postCount)
{
	char ** postPipe = NULL;
	
	int tokens = 0;
	int len= strlen(s);
	
	
	char secondHalf[9999];
	
	strcpy(secondHalf,s);
	

	char *str = secondHalf;

	char *str1 = strsep(&str, "|");// pipe 1
	char *str2 = strsep(&str, "\n"); // pipe 2 - THIS WILL BE PASSED INTO MAKEARGS

	tokens = makeargs(str2, &postPipe);
	
	//printargs(tokens-1,postPipe);
	
	*postCount = tokens;
	
	return postPipe;
	
	
	
}
void pipeIt(char ** prePipe, char ** postPipe)
{
	int fd[2];
	int status = 0;
	
	pid_t pid,pid1;

    pid = fork();
	
	if(pid != 0) // A.OUT
	{
		waitpid(pid,&status,NULL);
	}
	else
	{
	  int res = pipe(fd);
      pid1 = fork();
	  
	 if(pid1 != 0) // PARENT 
		 {		
			close(fd[1]);
			dup2(fd[0],0);
			close(fd[0]);
			int stat =execvp(postPipe[0],postPipe);
			
			exit(-1);
			
		 }
	
	else // CHILD
		{
			close(fd[0]);
			dup2(fd[1],1);
			close(fd[1]);
			int stat = execvp(prePipe[0],prePipe);
		
			exit(-1);
		}
	
	}	
	
	
} // end PipeIt






void multiPipe (int argc, char ** args, int pipes) 
{
	
    const int commands = pipes + 1;
    int i = 0;

    int pipefds[2*pipes];

    for(i = 0; i < pipes; i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("Couldn't Pipe");
            exit(EXIT_FAILURE);
        }
    }

    int pid;
    int status;

    int j = 0;
    int k = 0;
    int s = 1;
    int place;
    int commandStarts[10];
    commandStarts[0] = 0;

    // This loop sets all of the pipes to NULL
    // And creates an array of where the next
    // Command starts

    while (args[k] != NULL){
        if(!strcmp(args[k], "|")){
            args[k] = NULL;
            // printf("args[%d] is now NULL", k);
            commandStarts[s] = k+1;
            s++;
        }
        k++;
    }



    for (i = 0; i < commands; ++i) {
        // place is where in args the program should
        // start running when it gets to the execution
        // command
        place = commandStarts[i];

        pid = fork();
        if(pid == 0) {
            //if not last command
            if(i < pipes){
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*pipes
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            int q;
            for(q = 0; q < 2*pipes; q++){
                    close(pipefds[q]);
            }

            // The commands are executed here, 
            // but it must be doing it a bit wrong          
            if( execvp(args[place], args+place) < 0 ){
                    perror(*args);
                    exit(EXIT_FAILURE);
            }
        }
        else if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }

        j+=2;
    }

    for(i = 0; i < 2 * pipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < pipes + 1; i++){
        wait(&status);
    }
}
	
	
	
	
	
	



