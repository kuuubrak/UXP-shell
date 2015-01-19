#include "commands.h"

FILE *output = 0;

void set_output_file(FILE *fp)
{
  output = fp;
}

int cprintf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  if (output == 0)
    output = stdout;

  int rv = vfprintf(output, fmt, args);

  va_end(args);
  return(rv);
 }
