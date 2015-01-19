//
//  ls.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 15.01.2015.
//
//

#include "ls.h"
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "../commands.h"

void handleCommandLs(char* args[], int numargs)
{
  listFiles();
}

//ls doesn't take any arguments at the moment
/**
 * Prints contents of the current directory
 */
void listFiles()
{
  DIR * currentDirectory;
  char * directoryName = ".";

  currentDirectory = opendir(directoryName);

  if (!currentDirectory)
  {
    fprintf (stderr, "Cannot open current directory for listing.\n");
  }

  while (1) {
    struct dirent *entry;
    entry = readdir (currentDirectory);
    if (!entry) {
      break;
    }
    PRINT_COMMAND_OUTPUT("%s\n", entry->d_name);
  }

  if (closedir (currentDirectory)) {
    fprintf (stderr, "Could not close current directory.");
  }
}
