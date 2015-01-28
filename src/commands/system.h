#ifndef __UXP_Shell__system__
#define __UXP_Shell__system__

int handleSystemCall(char* comm, char* args[], int numargs, int flags, char* writerPipeName, char* readerPipeName);

#endif /* defined(__UXP_Shell__system__) */
