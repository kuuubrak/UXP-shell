//
//  pwd.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 13.01.2015.
//
//

#include "pwd.h"
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

void handleCommandPwd(char* args[], int numargs)
{
  printCurrentDirectory();
}

//pwd doesn't take any arguments at the moment
/**
 * Prints current directory
 */
void printCurrentDirectory()
{
  char *directoryBuffer = (char*) malloc(PATH_MAX+1);
  getcwd(directoryBuffer, PATH_MAX+1);
  PRINT_COMMAND_OUTPUT("%s\n", directoryBuffer);
  free(directoryBuffer);
}
