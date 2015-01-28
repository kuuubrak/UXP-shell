#include "redirectList.h"

#include <stdlib.h>
#include <stdio.h>

redirect* initRedirectList(int fd, char* filename)
{
  redirect* first = (redirect*) malloc(sizeof(redirect));
  first->next = NULL;
  first->filename = filename;
  first->fd = fd;
  return first;
}

void addToRedirectList(redirect* list, int fd, char* filename)
{
	while(list->next)
		list = list->next;
	list->next = (redirect*) malloc(sizeof(redirect));
	list->next->next = NULL;
	list->next->fd = fd;
	list->next->filename = filename;
}

char* getStdout(redirect* list)
{
	if(!list)
		return NULL;
	while (list)
	{
		if (list->fd == 1)
		{
			return list->filename;
		}

		list = list->next;
	}
	return NULL;
}

