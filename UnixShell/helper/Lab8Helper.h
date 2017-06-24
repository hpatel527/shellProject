#ifndef LAB8HELPER_H
#define LAB8HELPER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../process/process.h"
#include "../pipes/pipes.h"
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"
#include "../linkedlist/linkedList.h"
extern int HISTCOUNT;
extern int HISTFILECOUNT; 



int checkPrompt(char ** argv, int argc);
int setPath(char ** argv);
int changeDirectory(char ** argv, int argc);
int readShrc();
int findKey(char * s);
void fillOutput(LinkedList* theList);

#endif 