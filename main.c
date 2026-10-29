#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
  int data;
  Node *next;
  Node *prev;
};

int main (void)
{
  Node *head = NULL;
  Node *tail = NULL;

  for (int i; i < 3; i++)
  {
    Node *item = malloc(sizeof(Node));
    item->data=i;

    item->next=head;
    item->prev=NULL;

    if (head != NULL)
    {
      head->prev=item;
    }
    
    head=item;

    if (tail == NULL)
    {
      tail = item;
    }
    printf("head: %d\n", head->data);
    printf("tail: %d\n", tail->data);
  }

  return 0;
}
