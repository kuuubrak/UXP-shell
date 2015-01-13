#ifndef __UXP_Shell__sharedDefines__
#define __UXP_Shell__sharedDefines__

#define MAX_ARGS 10
#define MAX_LINE_SIZE 100

typedef enum CommandType
{
  COMMAND_NONE      = 0,
  COMMAND_EXIT      = 1,
  COMMAND_MKDIR     = 2,
  COMMAND_CD        = 3
} CommandType;

typedef struct Command
{
  CommandType type;
  char** args;
  int argsNum;
} Command;

#endif /* defined(__UXP_Shell__sharedDefines__) */
