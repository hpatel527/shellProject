#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
//#include "./linkedlist/genericData.h"
#include "./linkedlist/linkedList.h"
//#include "./listUtils.h"
//#include "./requireIncludes.h"
#include "./helper/Lab8Helper.h"

int main()
{
  int HISTCOUNT = 1000;
  int HISTFILECOUNT = 2000;  
  int argc, pipeCount,promptId = 0;	
  int argcc, argccc;
  char **argv = NULL, s[MAX] , temp[MAX];
  char **argvv = NULL;
  char **argvvv = NULL;
  int preCount = 0, postCount = 0;
  char ** prePipe = NULL, ** postPipe = NULL;
  LinkedList * histList = linkedList(HISTCOUNT); // add PARAMETER THAT TAKES IN HISTCOUNT FOR LINKEDLIST SIZE
  int x =0;
  
  
  int found = readShrc(); // IF 0 - myshrc was found , IF 1 - myshrc wasn't found
  
  
  
  printf("command?: ");
  fgets(s, MAX, stdin);
  strip(s);

  while(strcmp(s, "exit") != 0)
  {
	strcpy(temp,s);
	
	
	if(strstr(s, "!!") == NULL)
	{
		insert(histList,x,s);
		x++;
	}
	
	
	
	
	pipeCount = containsPipe(s);
	
	if(pipeCount == 1)
	{
		prePipe = parsePrePipe(s, &preCount);
		postPipe = parsePostPipe(s, &postCount);
		pipeIt(prePipe, postPipe);
		clean(preCount, prePipe);
        clean(postCount, postPipe);
	
	}// end if pipeCount
	
	else if(pipeCount > 1)
	{
		int k =0;
		argc = makeargs(s,&argv);
		//int len = strlen(argv);
		argv[argc] = '\0';

		multiPipe (argc,argv,pipeCount);
		
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
			else if(promptId == 4) // IF "HISTORY" WAS FOUND
			{
				print(histList);
			}
			else if(promptId == 5)// IF "!INT" WAS FOUND
			{
				int key = findKey(temp);
				char * ss = find(histList,key);
				if(ss != NULL)
				{
					
					pipeCount = containsPipe(ss);
	
					if(pipeCount > 0)
					{
						prePipe = parsePrePipe(ss, &preCount);
						postPipe = parsePostPipe(ss, &postCount);
						pipeIt(prePipe, postPipe);
						clean(preCount, prePipe);
						clean(postCount, postPipe);
					
					}// end if pipeCount
					
					argcc = makeargs(ss,&argvv);
					int promptIdd = checkPrompt(argvv,argcc);
					
					if(promptIdd == 0) // no special prompt
					{
						forkIt(argvv);
					}
					else if(promptIdd == 1) // IF PATH WAS FOUND
					{
						int pathSuccess = setPath(argvv);		
					}
					else if(promptIdd == 2) // IF & WAS FOUND
					{
						forkItBackground(argvv,argcc);
					}
					else if(promptIdd == 3) // If CD WAS FOUND
					{
						int changeSuccesss = changeDirectory(argvv,argcc);
					}
					else if(promptIdd == 4) // IF "HISTORY" WAS FOUND
					{
						print(histList);
					}
					
					
					clean(argcc,argvv);
					argvv = NULL;
					strcpy(ss,"");
					strcpy(temp,"");
					
				}
				else
				{
					printf("%s : not found \n", temp);
				}
			}
		    else if(promptId == 6) // IF !! was found
			{
				int key = histList->size;
				char * sss = (char *) malloc(100);
				findLast(histList,sss);
				
				
				if(sss != NULL)
				{
					printf("%s \n", sss);
					
					pipeCount = containsPipe(sss);
	
					if(pipeCount > 0)
					{
						prePipe = parsePrePipe(sss, &preCount);
						postPipe = parsePostPipe(sss, &postCount);
						pipeIt(prePipe, postPipe);
						clean(preCount, prePipe);
						clean(postCount, postPipe);
					
					}// end if pipeCount
					
					argccc = makeargs(sss,&argvvv);
					int promptIddd = checkPrompt(argvvv,argccc);
					
					if(promptIddd == 0) // no special prompt
					{
						forkIt(argvvv);
					}
					else if(promptIddd == 1) // IF PATH WAS FOUND
					{
						int pathSuccess = setPath(argvvv);		
					}
					else if(promptIddd == 2) // IF & WAS FOUND
					{
						forkItBackground(argvvv,argccc);
					}
					else if(promptIddd == 3) // If CD WAS FOUND
					{
						int changeSuccesss = changeDirectory(argvvv,argccc);
					}
					else if(promptIddd == 4) // IF "HISTORY" WAS FOUND
					{
						print(histList);
					}
					clean(argccc,argvvv);
					argvvv = NULL;
					strcpy(sss,"");
					
				}
				else
				{
					printf("%s : not found \n", temp);
				}
				free(sss);
			}
			else if(promptId == 7) // IF < WAS FOUND . PULL LAST TOKEN FROM ARGV WHICH IS THE FILENAME AND PASS IT INTO FORKITREDIRECT
			{
				int which = 1;
				char * fileStr = (char *) malloc(100);;
				strcpy(fileStr,argv[argc-1]);
				argv[argc-1] = '\0';
				argv[argc-2] = '\0';
				forkItRedirect(argv,argc,which ,fileStr);
				free(fileStr);
			}
			
			else if(promptId == 9)// IF > WAS FOUND . PULL LAST TOKEN FROM ARGV WHICH IS THE FILENAME AND PASS IT INTO FORKITREDIRECT
			{
				int whichh = 3;
				char * fileStrr = (char *) malloc(100);;
				strcpy(fileStrr,argv[argc-1]);
				argv[argc-1] = '\0';
				argv[argc-2] = '\0';
				forkItRedirect(argv,argc,whichh ,fileStrr);
				free(fileStrr);
				
			}
			
			else if(promptId == 8)// IF > WAS FOUND . PULL LAST TOKEN FROM ARGV WHICH IS THE FILENAME AND PASS IT INTO FORKITREDIRECT
			{
				int whichh = 2;
				char * fileStrr = (char *) malloc(100);;
				strcpy(fileStrr,argv[argc-1]);
				argv[argc-1] = '\0';
				argv[argc-2] = '\0';
				forkItRedirect(argv,argc,whichh ,fileStrr);
				free(fileStrr);
				
			}
			
			
				
		
			
	  	clean(argc, argv);
	  	argv = NULL;
		}
		
		
	}
	
	
	printf("command?: ");
	fgets(s, MAX, stdin);
      	strip(s);
		
	
  }// end while

  fillOutput(histList);
  clearList(histList);
  free(histList);
  histList = NULL;
  return 0;

}// end main

