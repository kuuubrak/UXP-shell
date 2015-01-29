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
  listElement* result = NULL;
  short repeat = 0;

  do {
    int argsNum = 0;
    char* args[MAX_ARGS];
    int type = COMMAND_NONE;
    char* fileName = "";
    char* strCommand = "";
    int flags = 0;

    if (repeat)
      strCommand = strtok(NULL, " ");
    else
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

    redirect* list = NULL;


    char* token;
    while ((token = strtok(NULL, " ")) && strcmp(token, "|") != 0)
    {
      if (strcmp(token, ">") == 0)
      {
        fileName = strtok(NULL, " ");
        if (!list)
          list = initRedirectList(1, fileName);
        else
          addToRedirectList(list, 1, fileName);
        break;
      }
      else if (strcmp(token, "<") == 0)
      {
        fileName = strtok(NULL, " ");
        if (!list)
          list = initRedirectList(0, fileName);
        else
          addToRedirectList(list, 0, fileName);
      }
      else if (token[1] == '>')
      {
        int fd = token[0] - '0';
        fileName = strtok(NULL, " ");
        if (!list)
          list = initRedirectList(fd, fileName);
        else
          addToRedirectList(list, fd, fileName);
      }
      else if (strcmp(token, "&") == 0)
        flags |= FLAG_IN_BACKGROUND;
      else
        if (token[0] != '\'')
          args[(argsNum)++] = token;
        else
        {
          char* token2 = strtok(NULL, "'");
          char* result = (char*) malloc(strlen(token) + strlen(token2) + 1);
          strcpy(result, token+1);
          strcat(result, " ");
          strcat(result, token2);
          
          args[(argsNum)++] = token;
        }
    }

    Command* comm = (Command*) malloc(sizeof(Command));
    comm->type = type;
    memcpy(comm->args, args, sizeof(args));
    comm->argsNum = argsNum;
    setbuf(stdout, NULL);
    comm->stringCommand = (char*)malloc(strlen(strCommand)+1);
    strcpy(comm->stringCommand, strCommand);
    comm->redirect = list;
    comm->flags = flags;

    if (result == NULL)
      result = initList(comm);
    else
      addElementToList(result, comm);

    if (token != NULL && strcmp(token, "|") == 0)
      repeat = 1;
    else
      repeat = 0;

  } while (repeat);

  return result;
}
