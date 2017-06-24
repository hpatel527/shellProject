#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void forkIt(char ** argv);
void forkItBackground(char ** argv,int argc);
void forkItRedirect(char ** argv, int argc , int which , char * fileStr);
#endif
