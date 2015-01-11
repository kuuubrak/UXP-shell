#include "main.h"
#include "parser.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>

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
  char commandBuffer[96];
  printf("%s@%s$ ", username, currentDirectory);
  scanf("%s", commandBuffer);
  interpretCommand(commandBuffer);
}

/**
 * Interprets entered command, sends it to parser
 */
void interpretCommand(char *command) {
  if (strcmp(command, "exit") == 0) {
    exit(0);
  } else {
    showPrompt();
  }
}

/**
 * Gets application directory
 */
char* getCurrentDirectory() {
  char *directoryBuffer = malloc(128);
  if (getcwd(directoryBuffer, 128) != NULL) {
    return directoryBuffer;
  } else {
    return 0;
  }
}
