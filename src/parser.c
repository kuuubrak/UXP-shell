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
listElement* parseCommand(char *command)
{
  int argsNum = 0;
  char* args[MAX_ARGS];
  listElement* result;
  int type = COMMAND_NONE;
  char* strCommand;

  strCommand = strtok(command, " ");
  if (strcmp(strCommand, "exit") == 0)
    type = COMMAND_EXIT;
  else if (strcmp(strCommand, "mkdir") == 0)
    type = COMMAND_MKDIR;
  else if (strcmp(strCommand, "cd") == 0)
    type = COMMAND_CD;
  else if (strcmp(strCommand, "pwd") == 0)
    type = COMMAND_PWD;
  else if (strcmp(strCommand, "touch") == 0)
    type = COMMAND_TOUCH;
  else if (strcmp(strCommand, "kill") == 0)
    type = COMMAND_KILL;
  else if (strcmp(strCommand, "rm") == 0)
    type = COMMAND_RM;
  else if (strcmp(strCommand, "ls") == 0)
    type = COMMAND_LS;

  char* token;
  while ((token = strtok(NULL, " ")) && strcmp(token, "|") != 0)
    args[(argsNum)++] = token;

  Command* comm = (Command*) malloc(sizeof(Command));
  comm->type = type;
  comm->args = args;
  comm->argsNum = argsNum;
  comm->stringCommand = (char*) malloc(sizeof(strCommand));
  strcpy(comm->stringCommand, strCommand);
  result = initList(comm);
  return result;
}
