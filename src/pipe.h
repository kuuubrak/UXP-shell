#include <stdio.h>

void createPipe(char* pipeName);
int openPipeWriter(char* pipeName);
int openPipeReader(char* pipeName);
void closePipe(int fd);
void destroyPipe(char* pipeName);
FILE* openCommandPipe(char* pipeName);