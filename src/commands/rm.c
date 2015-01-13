//
//  rm.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 13.01.2015.
//
//

#include "rm.h"
#include <unistd.h>
#include <fcntl.h>


void handleCommandRm(char* args[], int numargs)
{
  if (numargs == 0)
  {
    fprintf(stderr, "usage: rm path\n");
  }
  else
  {
    int i;
    //Shell allows you to enter multiple file names separated by spaces
    for (i = 0; i < numargs; i++)
    {
      removePath(args[i]);
    }
  }
}

/**
 * Removes file or directory at the given path
 */
void removePath(char *path)
{
  if(access(path, F_OK ) != -1 )
  {
    if (remove(path) != 0)
    {
      fprintf(stderr, "Couldn't remove file %s\n", path);
    }
  }
  else
  {
      fprintf(stderr, "File %s doesn't exists\n", path);
  }
}
