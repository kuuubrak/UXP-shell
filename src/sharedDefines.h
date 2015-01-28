#ifndef __UXP_Shell__sharedDefines__
#define __UXP_Shell__sharedDefines__

#include "redirectList.h"

#define MAX_ARGS 10
#define MAX_LINE_SIZE 100

typedef enum CommandType
{
  COMMAND_NONE      = 0,
  COMMAND_EXIT      = 1,
  COMMAND_MKDIR     = 2,
  COMMAND_CD        = 3,
  COMMAND_PWD       = 4,
  COMMAND_TOUCH     = 5,
  COMMAND_KILL      = 6,
  COMMAND_RM        = 7,
  COMMAND_LS        = 8,
  COMMAND_MAX_ENUM  = 9
} CommandType;

enum flags
{
  FLAG_IN_BACKGROUND     = 1
};

typedef struct Command
{
  CommandType type;
  char* args[MAX_ARGS];
  int argsNum;
  char* stringCommand;
  int flags;
  redirect* redirect;
} Command;

#endif /* defined(__UXP_Shell__sharedDefines__) */
