#include "main.h"
#include "parser.h"
#include "commands/mkdir.h"
#include "commands/cd.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include "list.h"
#include "sharedDefines.h"

char *currentDirectory;
char *username;

int main () {
  intialize();
  showPrompt();
  return 0;
}

/**
 * Intialize required variables
 */
void intialize() {
  currentDirectory = getCurrentDirectory();
  register struct passwd *account;
  account = getpwuid(getuid());
  if (account) {
    username = account->pw_name;
  }
}

/**
 * Shows prompt and waits for a command to be entered. (Probably can be implemented in a better way :) )
 */
void showPrompt() {
  printf("%s@%s$ ", username, currentDirectory);
  char commandBuffer[MAX_LINE_SIZE];
  int size = MAX_LINE_SIZE;
  if (fgets(commandBuffer, size, stdin) != NULL)
    interpretCommand(commandBuffer);
}

/**
 * Interprets entered command, sends it to parser
 */
void interpretCommand(char *command) {
  listElement* commandsList = parseCommand(command);

  while (commandsList != NULL)
  {
    Command* current = commandsList->command;
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
      default:
        break;
    }
    listElement* temp = commandsList;
    commandsList = commandsList->next;
    free(temp);
  }
  showPrompt();
}

/**
 * Gets application directory
 */
char* getCurrentDirectory() {
  char *directoryBuffer = malloc(128);
  getcwd(directoryBuffer, 128);
  return directoryBuffer;
}
