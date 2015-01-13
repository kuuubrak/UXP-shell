//
//  mkdir.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 11.01.2015.
//
//

#include "mkdir.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void handleCommandMkdir(char* args[], int numargs)
{
  if (numargs == 0)
  {
    fprintf(stderr, "usage: mkdir directory_name\n");
  }
  else
  {
    int i;
    //Shell allows you to enter multiple directories separated by spaces
    for (i = 0; i < numargs; i++)
    {
      makeDirectory(args[i]);
    }
  }
}

/**
 * Creates a directory at given path
 */
void makeDirectory(char *directoryName)
{
  struct stat st = {0};
  if (stat(directoryName, &st) == -1)
  {
    if (mkdir(directoryName, 0700) != 0)
      fprintf(stderr, "Couldn't create directory\n");
  }
  else
    fprintf(stderr, "Directory %s already exists\n", directoryName);
}
