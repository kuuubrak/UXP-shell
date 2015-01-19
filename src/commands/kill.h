//
//  kill.h
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 13.01.2015.
//
//

#ifndef __UXP_Shell__kill__
#define __UXP_Shell__kill__

#include <stdio.h>
#include <sys/types.h>

void handleCommandKill(char* args[], int numargs);
void killProcess(pid_t pid);

#endif /* defined(__UXP_Shell__kill__) */
