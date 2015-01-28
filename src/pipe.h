#ifndef __UXP_Shell__pipe__
#define __UXP_Shell__pipe__

#include <stdio.h>

void createPipe(char* pipeName);
int openPipeWriter(char* pipeName);
int openPipeReader(char* pipeName);
void closePipe(int fd);
void destroyPipe(char* pipeName);
FILE* openCommandPipe(char* pipeName);

#endif