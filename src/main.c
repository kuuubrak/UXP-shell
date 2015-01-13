#include "main.h"
#include "parser.h"
#include "commands/mkdir.h"
#include "commands/cd.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>\

#define MAX_LINE_SIZE 100

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
  char* args[MAX_ARGS];
  int numargs;
  int commandType = parseCommand(command, args, &numargs);

  switch (commandType)
  {
    case COMMAND_EXIT:
      exit(0);
      break;
    case COMMAND_MKDIR:
      handleCommandMkdir(args, numargs);
      break;
    case COMMAND_CD:
      handleCommandCd(args, numargs);
      break;
    default:
      break;
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
