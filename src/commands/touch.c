//
//  touch.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 13.01.2015.
//
//

#include "touch.h"
#include <unistd.h>
#include <fcntl.h>

void handleCommandTouch(char* args[], int numargs)
{
  if (numargs == 0)
  {
    fprintf(stderr, "usage: touch file_name\n");
  }
  else
  {
    int i;
    //Shell allows you to enter multiple file names separated by spaces
    for (i = 0; i < numargs; i++)
    {
      createFile(args[i]);
    }
  }
}

/**
 * Creates file at given path
 */
void createFile(char *fileName)
{
  if(access(fileName, F_OK ) != -1 )
  {
    fprintf(stderr, "File %s already exists\n", fileName);
  }
  else
  {
    FILE *newFile = fopen(fileName, "w");
    if (newFile != NULL)
    {
      fclose(newFile);
    }
    else
    {
      fprintf(stderr, "Couldn't create file %s\n", fileName);
    }
  }
}
