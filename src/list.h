#ifndef __UXP_Shell__list__
#define __UXP_Shell__list__

#include <stdio.h>
#include <stdlib.h>
#include "sharedDefines.h"

typedef struct listElement
{
  struct listElement *next;
  struct Command *command;
} listElement;

listElement* initList(Command* comm);
void addElementToList(listElement *list, Command *comm);
unsigned int getListSize(listElement *list);

#endif /* defined(__UXP_Shell__list__) */
