#include "system.h"
#include <stdlib.h>
#include <stdio.h>

int handleSystemCall(char* command)
{
  int status;
  status = system(command);
  return status;
}
