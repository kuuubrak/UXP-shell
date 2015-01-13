//
//  cd.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 11.01.2015.
//
//

#include "cd.h"
#include "string.h"
#include "pwd.h"
#include <unistd.h>
#include <pwd.h>


void handleCommandCd(char* args[], int numargs) {
  if (numargs == 0)
  {
    changeDirectory("");
  } else
  {
    //As in shell: if there are more than 1 argument, command won't return any warning
    //and interpret only this first argument
    changeDirectory(args[0]);
  }
}

/**
 * Changes directory to given path. No arguments means changing to home directory.
 */
void changeDirectory(char *path)
{
  if (strcmp(path, "") == 0)
  {
    struct passwd *account = getpwuid(getuid());
    const char *home = account->pw_dir;
    if (chdir(home) != 0)
      fprintf(stderr, "Couldn't change directory");
  }
  else if (chdir(path) != 0)
    fprintf(stderr, "Directory %s doesn't exist\n", path);
}
