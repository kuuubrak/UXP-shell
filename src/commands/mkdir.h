//
//  mkdir.h
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 11.01.2015.
//
//

#ifndef __UXP_Shell__mkdir__
#define __UXP_Shell__mkdir__

#include <stdio.h>
#include "../sharedDefines.h"

void handleCommandMkdir(char* args[], int numargs);
void makeDirectory(char *directoryName);

#endif /* defined(__UXP_Shell__mkdir__) */
