#include "makeArgs.h"
 
void clean(int argc, char **argv)
{
    int x = 0;
    while (x < argc)
    {
        free(argv[x]);
        x++;
    }
    free(argv);
 
 
}// end clean
void printargs(int argc, char **argv)
{
    int x;
    for(x = 0; x < argc; x++)
        printf("%s\n", argv[x]);
 
}// end printargs
 
int makeargs(char *s, char *** argv)
{
    char sCopy[1024];
 
    strcpy(sCopy, s);
 
    int x = 0;
    int count = 0;
    while(sCopy[x] != '\0')
    {
        if(sCopy[x] == ' ')
        {
            count++;
        }
        x++;
    }//num of tokens
 
    *argv = (char**)calloc(count + 1, sizeof(char**));
    char * token = strtok(s, " ");
    x = 0;
    while(token != NULL)
    {
        (*argv)[x] = (char *)calloc(strlen(token) + 1, sizeof(char));
        strcpy((*argv)[x], token);
        token = strtok(NULL, " ");
        x++;
    }
    return count+1;
 
 
}// end makeArgs