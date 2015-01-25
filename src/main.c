#include "main.h"
#include "parser.h"
#include "commands/mkdir.h"
#include "commands/cd.h"
#include "commands/pwd.h"
#include "commands/touch.h"
#include "commands/kill.h"
#include "commands/rm.h"
#include "commands/ls.h"
#include "commands/system.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include "list.h"
#include "sharedDefines.h"
#include "commands.h"
#include <linux/limits.h>

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
  struct passwd *account;
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
  // dont parse empty commands
  if (strlen(command) == 0)
  {
    showPrompt();
    return;
  }
  // save original command
  char originalCommand[MAX_LINE_SIZE];
  strcpy(originalCommand, command);

  //strcpy(originalCommand, command);
  listElement* commandsList = parseCommand(command);

  Command* current;
  FILE *fp;
  while (commandsList != NULL)
  {
    current = commandsList->command;
    // redirect command output to file
    if (strcmp(current->fileName, "") != 0)
    {
      fp = fopen(current->fileName, "w");
      if (fp != NULL)
        set_output_file(fp);
      else fprintf(stderr, "Cannot create file: %s", current->fileName);
    }
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
        if (handleSystemCall(originalCommand) != 0) // check if its program
          PRINT_COMMAND_OUTPUT("Unknown command: %s\n", current->stringCommand);
        break;
    }
    // set output back to stdout
    if (strcmp(current->fileName, "") != 0)
    {
      set_output_file(stdout);
      fclose(fp);
    }
    listElement* temp = commandsList;
    commandsList = commandsList->next;
    free(current->stringCommand);
    free(current->fileName);
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
  char *directoryBuffer = (char*) malloc(PATH_MAX+1);
  getcwd(directoryBuffer, PATH_MAX+1);
  return directoryBuffer;
}
