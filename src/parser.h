//
//  parser.h
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 11.01.2015.
//
//

#ifndef __UXP_Shell__parser__
#define __UXP_Shell__parser__

#include <stdio.h>

#define MAX_ARGS 10

enum commands
{
  COMMAND_NONE      = 0,
  COMMAND_EXIT      = 1,
  COMMAND_MKDIR     = 2,
  COMMAND_CD        = 3
};

int parseCommand(char *command, char* args[], int* numargs);

#endif /* defined(__UXP_Shell__parser__) */
