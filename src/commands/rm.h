//
//  rm.h
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 13.01.2015.
//
//

#ifndef __UXP_Shell__rm__
#define __UXP_Shell__rm__

#include <stdio.h>

void handleCommandRm(char* args[], int numargs);
void removePath(char *path);

#endif /* defined(__UXP_Shell__rm__) */
