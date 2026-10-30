#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 10

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

typedef struct Cache
{
  Node *next;
  Node *prev;
  Hash *cache[CAPACITY];
}Cache;

Node *head = NULL;
Node *tail = NULL;

Hash* indexing(Node *item)
{
  Hash *indexed_node = malloc(sizeof(Hash));
  indexed_node->index=item->data%CAPACITY;
  indexed_node->item=item;
  return indexed_node;
}

Hash* put(int data)
{
  Node *item = malloc(sizeof(Node));
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
  Hash *indexed_node = indexing(item);
  return indexed_node;
}

// Node get(int data)
// {
  
// }

int main (void)
{
  // Cache *cache = malloc(sizeof(Cache)); 
  Hash *a = put(10);
  Hash *b = put(13);
  Hash *c = put(30);

  printf("key:%d\ndata:%d\n", a->index, a->item->data);
  printf("key:%d\ndata:%d\n", b->index, b->item->data);
  printf("key:%d\ndata:%d\n", c->index, c->item->data);
  return 0;
}
