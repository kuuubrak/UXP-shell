#include "main.h"
#include "parser.h"
#include "commands/mkdir.h"
#include "commands/cd.h"
#include "commands/pwd.h"
#include "commands/touch.h"
#include "commands/kill.h"
#include "commands/rm.h"
#include "commands/ls.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include "list.h"
#include "sharedDefines.h"

char *currentDirectory;
char *username;

int main ()
{
  intialize();
  showPrompt();
  return 0;
}

/**
 * Intialize required variables
 */
void intialize()
{
  currentDirectory = getCurrentDirectory();
  register struct passwd *account;
  account = getpwuid(getuid());
  if (account)
    username = account->pw_name;
}

/**
 * Shows prompt and waits for a command to be entered. (Probably can be implemented in a better way :) )
 */
void showPrompt()
{
  printf("%s@%s$ ", username, currentDirectory);
  char commandBuffer[MAX_LINE_SIZE];
  int size = MAX_LINE_SIZE;
  if (fgets(commandBuffer, size, stdin) != NULL)
  {
    size_t len = strlen(commandBuffer) - 1;
    if (commandBuffer[len] == '\n')
      commandBuffer[len] = '\0'; // remove trailing newline character
    interpretCommand(commandBuffer);
  }
}

/**
 * Interprets entered command, sends it to parser
 */
void interpretCommand(char *command)
{
  listElement* commandsList = parseCommand(command);

  Command* current;
  while (commandsList != NULL)
  {
    current = commandsList->command;
    switch (current->type)
    {
      case COMMAND_EXIT:
        exit(0);
        break;
      case COMMAND_MKDIR:
        handleCommandMkdir(current->args, current->argsNum);
        break;
      case COMMAND_CD:
        handleCommandCd(current->args, current->argsNum);
        break;
      case COMMAND_PWD:
        handleCommandPwd(current->args, current->argsNum);
        break;
      case COMMAND_TOUCH:
        handleCommandTouch(current->args, current->argsNum);
        break;
      case COMMAND_KILL:
        handleCommandKill(current->args, current->argsNum);
        break;
      case COMMAND_RM:
        handleCommandRm(current->args, current->argsNum);
        break;
      case COMMAND_LS:
        handleCommandLs(current->args, current->argsNum);
        break;
      default:
        fprintf(stderr, "Unknown command: %s\n", current->stringCommand);
        break;
    }
    listElement* temp = commandsList;
    commandsList = commandsList->next;
    free(current->stringCommand);
    free(current);
    free(temp);
  }
  showPrompt();
}

/**
 * Gets application directory
 */
char* getCurrentDirectory()
{
  char *directoryBuffer = malloc(128);
  getcwd(directoryBuffer, 128);
  return directoryBuffer;
}
