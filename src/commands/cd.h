//
//  cd.h
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 11.01.2015.
//
//

#ifndef __UXP_Shell__cd__
#define __UXP_Shell__cd__

#include <stdio.h>
#include <unistd.h>
#include "../sharedDefines.h"

void handleCommandCd(char* args[], int numargs);
void changeDirectory(char *path);

#endif /* defined(__UXP_Shell__cd__) */
