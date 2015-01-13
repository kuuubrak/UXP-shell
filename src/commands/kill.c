//
//  kill.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 13.01.2015.
//
//

#include "kill.h"
#include "signal.h"
#include <stdlib.h>

void handleCommandKill(char* args[], int numargs)
{
  if (numargs == 0)
  {
    fprintf(stderr, "usage: kill pid\n");
  }
  else
  {
    int i;
    //Shell allows you to enter multiple pid's separated by spaces
    for (i = 0; i < numargs; i++)
    {
      killProcess(atoi(args[i]));
    }
  }
}

/**
 * Kills process with given pid
 */
void killProcess(pid_t pid)
{
  if(kill(pid, SIGKILL) != 0)
  {
    fprintf(stderr, "Couldn't kill process with pid %i\n", pid);
  }
}