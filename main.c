#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
  int data;
  Node *next;
  Node *prev;
};

Node *head = NULL;
Node *tail = NULL;

Node put(int data)
{
  Node *item = malloc(sizeof(Node));
  item->data=data;
  item->next=head;
  item->prev=NULL;

  if (head == NULL)
  {
    head->prev=item;
  }
  head=item;

  if (tail == NULL)
  {
    tail = item;
  }
}

int main (void)
{
  return 0;
}
