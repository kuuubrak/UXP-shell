#ifndef __UXP_Shell__system__
#define __UXP_Shell__system__

#include "../redirectList.h"

int handleSystemCall(char* comm, char* args[], int numargs, int flags, redirect* redirectList);

#endif /* defined(__UXP_Shell__system__) */
