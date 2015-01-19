#ifndef __UXP_Shell__sharedDefines__
#define __UXP_Shell__sharedDefines__

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

typedef struct Command
{
  CommandType type;
  char** args;
  int argsNum;
  char* stringCommand;
  int flags;
  char* fileName;
} Command;

#endif /* defined(__UXP_Shell__sharedDefines__) */
