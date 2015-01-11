//
//  main.h
//  UXP-Shell
//
//  Created by Tomasz Kubrak on 11.01.2015.
//
//

#ifndef __UXP_Shell__main__
#define __UXP_Shell__main__

void intialize();
void showPrompt();
char* getCurrentDirectory();
void interpretCommand(char *command);

#endif /* defined(__UXP_Shell__main__) */
