//
//  pwd.c
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 13.01.2015.
//
//

#include "pwd.h"

void handleCommandPwd(char* args[], int numargs)
{
  printCurrentDirectory();
}

//pwd doesn't take any arguments at the moment
/**
 * Prints current directory
 */
void printCurrentDirectory()
{
  printf("%s\n", getCurrentDirectory());
}
