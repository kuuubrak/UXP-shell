//
//  parser.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 11.01.2015.
//
//

#include "parser.h"
#include <string.h>

/**
Parse command, save arguments in args and number of arguments in numargs. Returns command code from enum Commands
*/
int parseCommand(char *command, char* args[], int* numargs) {
  *numargs = 0;
  int result = COMMAND_NONE;

  command = strtok(command, " ");
  if (strcmp(command, "exit") == 0)
    result = COMMAND_EXIT;
  else if (strcmp(command, "mkdir") == 0)
    result = COMMAND_MKDIR;
  else if (strcmp(command, "cd") == 0)
    result = COMMAND_CD;

  char* token;
  while ((token = strtok(NULL, " ")))
    args[(*numargs)++] = token;

  return result;
}
