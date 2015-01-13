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
Parse command, save type in type, arguments in args and number of arguments in argsNum. Returns list of commands.
*/
listElement* parseCommand(char *command) {
  int argsNum = 0;
  char* args[MAX_ARGS];
  listElement* result;
  int type = COMMAND_NONE;

  command = strtok(command, " ");
  if (strcmp(command, "exit") == 0)
    type = COMMAND_EXIT;
  else if (strcmp(command, "mkdir") == 0)
    type = COMMAND_MKDIR;
  else if (strcmp(command, "cd") == 0)
    type = COMMAND_CD;

  char* token;
  while ((token = strtok(NULL, " ")) && strcmp(token, "|") != 0)
    args[(argsNum)++] = token;

  Command* comm = (Command*) malloc(sizeof(Command));
  comm->type = type;
  comm->args = args;
  comm->argsNum = argsNum;
  result = initList(comm);
  return result;
}
