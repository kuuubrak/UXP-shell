#include "pipe.h"
#include "commands.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void createPipe(char* pipeName)
{
  char* baseName = "/tmp/uxpshell%02i";
  int i = 0;

  do
  {
    sprintf(pipeName, baseName, i);
    i++;
  } while (mkfifo(pipeName, 0666) != 0);
}

int openPipeWriter(char* pipeName)
{
  int fd = open(pipeName, O_WRONLY);
  
  return fd;
}

int openPipeReader(char* pipeName)
{
  int fd = open(pipeName, O_RDONLY);

  return fd;
}

void closePipe(int fd)
{
  close(fd);
}

void destroyPipe(char* pipeName)
{
  unlink(pipeName);
}

FILE* openCommandPipe(char* pipeName)
{
  FILE* fp = fopen(pipeName, "w");
  if (fp != NULL)
    set_output_file(fp);
  return fp;
}