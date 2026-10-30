#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
  int data;
  Node *next;
  Node *prev;
};

typedef struct Hash
{
  int index;
  Node *item;
}Hash;

Node *head = NULL;
Node *tail = NULL;
int index = -1; 

Hash* indexing(int index, Node *item)
{
  Hash *indexed_node = malloc(sizeof(Hash));
  indexed_node->index=index;
  indexed_node->item=item;
  return indexed_node;
}

Hash* put(int data)
{
  Node *item = malloc(sizeof(Node));
  index++;
  item->data=data;
  item->next=head;
  item->prev=NULL;

  if (head != NULL)
  {
    head->prev=item;
  }
  head=item;

  if (tail == NULL)
  {
    tail=item;
  }
  Hash *indexed_node = indexing(index, item);
  return indexed_node;
}

// Node get(int data)
// {
  
// }

int main (void)
{
  Hash *a = put(10);
  Hash *b = put(20);
  Hash *c = put(30);

  printf("key:%d\ndata:%d\n", a->index, a->item->data);
  printf("key:%d\ndata:%d\n", b->index, b->item->data);
  printf("key:%d\ndata:%d\n", c->index, c->item->data);
  return 0;
}
