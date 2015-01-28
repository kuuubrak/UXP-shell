#ifndef __UXP_Shell__redirect__
#define __UXP_Shell__redirect__

typedef struct redirect
{
  int fd;
  char* filename;
  struct redirect* next;
} redirect;

redirect* initRedirectList(int fd, char* filename);
void addToRedirectList(redirect* list, int fd, char* filename);

char* getStdout(redirect* list);

#endif