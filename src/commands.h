#ifndef __UXP_Shell__commands__
#define __UXP_Shell__commands__

#include <stdio.h>
#include <stdarg.h>

#define PRINT_COMMAND_OUTPUT(fmt, ...) cprintf(fmt, __VA_ARGS__)

void set_output_file(FILE *fp);
int cprintf(const char *fmt, ...);

#endif /* defined(__UXP_Shell__commands__) */
