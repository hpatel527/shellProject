#include "Lab8Helper.h"
// PURPOSE OF THIS C FILE IS TO CONTAIN HELPER METHODS FOR MYSHELL(cscd340Lab8.c)
// HELPER METHODS INCLUDE CHECKING COMMANDS FOR SPECIFIC PROMPTS ( &, < , >>, >, PATH)
// AND PROPAGATING FLAGS BACK TO THE MAIN C  FILE TO PASS INTO THE NECESSARY FUNCTIONS LIKE PIPEIT



int checkPrompt(char ** argv, int argc) // THIS METHOD SEARCHES ARGV FOR SPECIFIC PROMPTS(PATH, &, !!) AND RETURNS AN APPRORIATE INTEGER FLAG
{
	char * s;
	int prompt = 0; // 0 MEANS NO SPECIAL PROMPT, 1 - MEANS PATH , 2 - MEANS & , 3 - MEANS cd
	
	//strcpy (s,argv[0]);
	
	
	
	for(int i=0;i<argc ; ++i)
	{
		
		if (strstr(argv[i], "PATH") != NULL)// contains PATH
		{
			prompt = 1;
		}
		
		else if(strstr(argv[i],"&") != NULL)
		{
			prompt = 2;
		}
		
		else if(strstr(argv[i],"cd") != NULL)
		{
			prompt = 3;
		}
		else if(strstr(argv[i],"history") != NULL)
		{
			prompt = 4;
		}
		
		else if(strstr(argv[i],"!!") != NULL)
		{
			prompt = 6;
		}
		
		else if(strstr(argv[i],"!") != NULL)
		{
			prompt = 5;
		}
		else if(strstr(argv[i],"<") != NULL)
		{
			prompt = 7;
		}
		
		else if(strstr(argv[i],">>") != NULL)
		{
			prompt = 9;
		}
		
		else if(strstr(argv[i],">") != NULL)
		{
			prompt = 8;
		}
		
		
		
		
	}
	
	
	return prompt;
}

int findKey(char * s) // SEARCHES STRING FOR INTEGER(ID) AND RETURNS THAT ID
{
	char * r = s + 1;
	int key = atoi(r);
	return key;
	
}



int setPath(char ** argv) // SETS PATH VARIABLE TO WHATEVER WAS PASSED IN ARGV(COMMAND)
{
	char * path;
	char strAfter[200];
	char *strJunk = "PATH=$PATH:";
	strcpy(strAfter,argv[0]);
	path = strstr(strAfter,strJunk);
	strcpy(path,path + strlen(strJunk));
	
	
	
	
	
	if(setenv("PATH", path, 1) < 0) // NEED TO CREATE STRING THAT CONTAINS ONLY THE PATH AND NOT THE EXTRA ChARACTERS
	{
	   printf("Error setting PATH. \n");
	   return 1;
	}
	
	//printf("PATH: %s\n",getenv("PATH"));
	return 0;
	
}

int changeDirectory(char ** argv, int argc) // CHANGES WORKING DIRECTORY TO PATH PASSED IN ARGV(COMMAND)
{
	
	
	if(chdir(argv[1]) < 0) // NEED TO CREATE STRING THAT CONTAINS ONLY THE PATH AND NOT THE EXTRA ChARACTERS
	{
	   printf("Error changing working directory. \n");
	   return 1;
	}
	
	return 0;
	
}

int readShrc() // reads input from .myshrc and executes each line as a command. 
{				// EMULATES SAME STRUCTURE OF EXECUTING COMMANDS FROM MAIN.C
				// MIGHT MOVE TO MAIN.C SO GLOBAL HISTCOUNT AND HISTFILECOUNT CAN BE CHANGED
	char s[1024]; //file line
	char *cmd = "";
	int argc, pipeCount,promptId = 0;	
     char **argv = NULL;
	 int HISTCOUNT = 1000;
	 int HISTFILECOUNT = 2000;
	 FILE * fin = NULL;
	
	if((fin = fopen(".myshrc","r")) != NULL)
	{
		
		while((fgets(s, 1024, fin)) != NULL)
		{
			strip(s);
			
			 if(strstr(s, "HISTCOUNT"))
			{
				char *p = s;
				while(*p)
				{
					if(isdigit(*p))
					{
						long val = strtol(p,&p,10);
						HISTCOUNT = val;
						//printf("HISTCOUNT is %d\n", HISTCOUNT);
					}
					else
					{
						p++;
					}
				}
				
			}
			
			else if(strstr(s,"HISTFILECOUNT"))
			{
				char *r = s;
				while(*r)
				{
					if(isdigit(*r))
					{
						long vall = strtol(r,&r,10);
						HISTFILECOUNT = vall;
						//printf("HISTFILECOUNT is %d\n", HISTFILECOUNT);
					}
					else
					{
						r++;
					}
				}
				
			}
			
			else if ((s != NULL) && (s[0] == '\0')) 
			{
				//printf("c is empty\n");
			}
			else
			{
				
				argc = makeargs(s, &argv);
			 
				if(argc != -1)
				{
					// INSERT METHOD TO CHECK ARGV FOR A SPECIFIC PROMPT THAT RETURNS AN INTEGER that is passed into promptId
					// IF ELSE STRUCTURE THAT CHECKS WHAT PROMPTID IS AND EXECUTES NECESSARY METHOD
					
					promptId = checkPrompt(argv,argc);
					if(promptId == 0) // no special prompt
					{
						forkIt(argv);
					}
					else if(promptId == 1) // IF PATH WAS FOUND
					{
						int pathSuccess = setPath(argv);		
					}
					else if(promptId == 2) // IF & WAS FOUND
					{
						forkItBackground(argv,argc);
					}
					else if(promptId == 3) // If CD WAS FOUND
					{
						int changeSuccess = changeDirectory(argv,argc);
					}
				 
				
				clean(argc, argv);
				argv = NULL;
				}
			}
		
		
		
		}
		fclose(fin);
		return 0;
	}		
	
	return 1; // FAILURE TO OPEN/FIND .myshrc
	
}

void fillOutput(LinkedList * theList) // Fills ./mysh_history file with commands stored in LinkedList
{
	FILE * fout = NULL;
	
	fout = fopen(".mysh_history","w");
	
	if (fout == NULL)
	{
		printf("Can't open output file!");
	}
	else
	{
		Node * temp;
		if(theList->head->next != NULL)
		{
			temp = theList->head->next;
			while(temp != NULL)
			{
				fprintf(fout,"%d ", temp->data);
				fprintf(fout," %s \n",temp->name);
				temp = temp->next;
			}
		}
			
			
			
	}
	
	fclose(fout);
	
}


