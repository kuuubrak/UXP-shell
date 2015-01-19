#include "list.h"

/**
Initialize new list.
*/
listElement* initList(Command* comm)
{
  listElement* first = (listElement*) malloc(sizeof(listElement)+sizeof(Command));
  first->next = NULL;
  first->command = comm;
  return first;
}

/**
Adds element at the end of the list.
*/
void addElementToList(listElement *list, Command *comm)
{
  listElement *temp = list;
  while (temp->next != NULL)
    temp = temp->next;
  listElement *newElement;
  newElement = (listElement*) malloc(sizeof(listElement));
  newElement->command = comm;
  newElement->next = NULL;
  temp->next = newElement;
}
