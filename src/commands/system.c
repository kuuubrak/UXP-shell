#include "system.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "../sharedDefines.h"

int handleSystemCall(char* comm, char* args[], int numargs, int flags)
{
  int status;
  char command[MAX_LINE_SIZE];
  memset(command, 0, MAX_LINE_SIZE);

  strcat(command, comm);
  strcat(command, " ");

  for (int i = 0; i < numargs; ++i)
  {

    strcat(command, args[i]);
    strcat(command, " ");
  }

  if (flags & FLAG_IN_BACKGROUND)
  {
    if (fork() == 0)
    {
      status = system(command);
      exit(0);
    }
    else status = 0; // @todo wait for child result?
  }
  else
    status = system(command);

  return status;
}
