#include "system.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <fcntl.h>
#include "../sharedDefines.h"
#include "../pipe.h"

int handleSystemCall(char* comm, char* args[], int numargs, int flags, redirect* redirectList)
{
  int status = 0;
  char command[MAX_LINE_SIZE];
  memset(command, 0, MAX_LINE_SIZE);

  char** execargs = (char**) malloc(sizeof(char*) * (numargs + 2)); // +1 for null-terminate, +1 for program name

  for (int i = 1; i <= numargs; ++i)
  {
    execargs[i] = (char*) malloc(strlen(args[i-1])+1);
    strcpy(execargs[i], args[i-1]);
  }

  execargs[numargs+1] = 0;
  execargs[0] = comm;

  pid_t pid;
  if ((pid = fork()) == 0)
  {
    while (redirectList)
    {
      if (redirectList->fd == 0)
      {
        int fd = open(redirectList->filename, O_RDONLY);
        dup2(fd, redirectList->fd);
      }
      else
      {
        int fd = open(redirectList->filename, O_WRONLY | O_CREAT);
        dup2(fd, redirectList->fd);
      }
      redirectList = redirectList->next;
    }
    status = execvp(comm, execargs);//system(command);
  }
  else
  {
    if (!(flags & FLAG_IN_BACKGROUND))
    {
      waitpid(pid, &status, 0);
      return WEXITSTATUS(status);
    }
  }
  return status;
}
