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
#include "pipe.h"

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
 * Updated the current working directory
 */

void updateCWD()
{
  if (currentDirectory)
    free(currentDirectory);

  long size = pathconf(".", _PC_PATH_MAX);

  if ((currentDirectory = (char*) malloc((size_t) size)) != NULL)
    currentDirectory = getcwd(currentDirectory, (size_t) size);
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

  listElement* commandsList = parseCommand(command);

  Command* current;
  FILE *fp = NULL;

  int i = 0; // number of process in the pipe;
  int pipeSize = getListSize(commandsList); // size of the pipe

  char *writerPipeName = NULL;
  char *readerPipeName = NULL;

  while (commandsList != NULL)
  {
    if (i != 0) // if we are reading from a pipe
    {
      printf("%s: czytam z pipe'a: %s\n", commandsList->command->stringCommand, readerPipeName);
    }
    if (i < pipeSize-1) // if we have at least one more command to execute in the pipe
    {
      writerPipeName = malloc(32 * sizeof(char)); // name of the pipe we are writing to
      createPipe(writerPipeName);
      printf("%s: pisze do pipe'a: %s\n", commandsList->command->stringCommand, writerPipeName);
    }
    else
      writerPipeName = NULL;

    current = commandsList->command;

    if (strcmp(current->fileName, "") != 0) // redirect command output to file
    {
      fp = fopen(current->fileName, "w");
      if (fp != NULL)
        set_output_file(fp);
      else fprintf(stderr, "Cannot create file: %s", current->fileName);
    }
    char* target = NULL;

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
        updateCWD();
        break;
      case COMMAND_PWD:
      if (writerPipeName && fork() == 0)
        {
          openCommandPipe(writerPipeName);
          handleCommandPwd(current->args, current->argsNum);
        }
        else if (!writerPipeName)
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
        if (writerPipeName && fork() == 0)
        {
          openCommandPipe(writerPipeName);
          handleCommandLs(current->args, current->argsNum);
          exit(0);
        }
        else if (!writerPipeName)
          handleCommandLs(current->args, current->argsNum);
        break;
      default:
        if (writerPipeName)
        {
          current->flags |= FLAG_IN_BACKGROUND; //fork away writer processes
          target = writerPipeName;
        }
        else if (strcmp(current->fileName, "") != 0)
        {
          target = current->fileName;
        }
        if (handleSystemCall(current->stringCommand, current->args, current->argsNum, current->flags, target, readerPipeName) != 0) // check if its program
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

    if (pipeSize > 1) // these operations are only necessary if we have a pipe
    {
      if (i > 0) //if we were reading from a pipe
      {
        destroyPipe(readerPipeName);
      }
    }

    if (readerPipeName)
    {
      free(readerPipeName);
      readerPipeName = NULL;
    }
    readerPipeName = writerPipeName;

    i++;
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
