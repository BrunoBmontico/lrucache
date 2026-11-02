#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 10

typedef struct Node
{
  int data;
  struct Node *next;
  struct Node *prev;
}Node;

typedef struct Hash
{
  int index;
  Node *node;
  struct Hash *next;

}Hash;

typedef struct Cache
{
  Hash *nodes[CAPACITY];
}Cache;

Node *head = NULL;
Node *tail = NULL;

Hash* indexing(Node *node)
{
  Hash *indexed_node = malloc(sizeof(Hash));
  indexed_node->index=node->data%CAPACITY;
  indexed_node->node=node;
  return indexed_node;
}

void collision_handle(Cache *cache, Hash *indexed_node)
{
  indexed_node->next = cache->nodes[indexed_node->index];
  cache->nodes[indexed_node->index] = indexed_node;
}

Hash* put(Cache *cache, int data)
{
  Node *node = malloc(sizeof(Node));
  node->data=data;
  node->next=head;
  node->prev=NULL;

  if (head != NULL)
  {
    head->prev=node;
  }
  head=node;

  if (tail == NULL)
  {
    tail=node;
  }
  Hash *indexed_node = indexing(node);
  collision_handle(cache, indexed_node);
  return indexed_node;
}

int get(Cache *cache, int data)
{
  Hash *result = cache->nodes[data%CAPACITY];
  while (result->node->data != data)
  {
    result = cache->nodes[data%CAPACITY]->next;
  }
  return result->node->data;
}

int main (void)
{
  Cache *cache = malloc(sizeof(Cache));
  put(cache,10);
  put(cache,13); 
  put(cache,30);
  put(cache,40);
  put(cache,20);
  put(cache,323);

  int a = get(cache,20);
  printf("%d\n",a);

  return 0;
}
