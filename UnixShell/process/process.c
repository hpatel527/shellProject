#include "process.h"

void forkIt(char ** argv)
{
	int status;
	pid_t pid = fork(); // create child process
	
	if(pid != 0) // in parent process
	{
		waitpid(pid, &status, 0);	
		
	}

	else // in child process
	{
		int res = execvp(argv[0], argv);
		
		if(res)
		{
			printf("Command not found\n");
			exit(-1);
			
		}
		
	}



}

void forkItBackground(char ** argv, int argc ) // Pseudo-overloaded Method that forks but causes parent to work in background
{
	
	int status;
	
	
	//char *argvd[] = { "ls", "-l" , 0};

	argv[argc-1]= '\0';
	argc--;
	
	
	pid_t pid = fork(); // create child process
	
	
	
	
	if(pid != 0) // in parent process
	{			
		
	}

	else // in child process
	{
		int res = execvpe(argv[0], argv);
		
		if(res)
		{
			printf("INVALID COMMAND\n");
			exit(-1);
			
		}
		
	}

}

void forkItRedirect(char ** argv, int argc , int which , char * fileStr) // REDIRECTS INPUT/OUTPUT SPECFIED BY USER. WHICH = 0 INPUT WHICH = 1 OUTPUT
{
	int pid = fork();

	if (pid == -1)
		{
		printf("ERROR PIPING");
		} 
	else if (pid == 0) {   

		if (which == 1) { //if '<' char was found in string inputted by user
			int fd0 = open(fileStr, O_RDONLY, 0);
			dup2(fd0, STDIN_FILENO);
			close(fd0);
			which = 0;
		}

		if (which == 2) { //if '>' was found in string inputted by user
			int fd1 = creat(fileStr, 0644);
			dup2(fd1, STDOUT_FILENO);
			close(fd1);
			which = 0;
		}  

		if (which == 3) { // if >> was found in argv
			int fd1 = open(fileStr,O_WRONLY | O_APPEND,0666);
			dup2(fd1, STDOUT_FILENO);
			close(fd1);
			which = 0;
			
			
		}

		execvp(argv[0], argv);
		perror("execvp");
		_exit(1);
	} else {
		waitpid(pid, 0, 0);
		
	}
	
	
}
