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
Hash *cache_head = NULL;

Hash* indexing(Node *node)
{
  Hash *indexed_node = malloc(sizeof(Hash));
  indexed_node->index=node->data%CAPACITY;
  indexed_node->node=node;
  return indexed_node;
}

void collision_handle(Cache *cache, Hash *indexed_node)
{
  cache->nodes[indexed_node->index]=cache_head;
  if (cache_head != NULL)
  { 
    cache->nodes[indexed_node->index]->next=cache_head;
  }
  cache_head=indexed_node;
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

int main (void)
{
  Cache *cache = malloc(sizeof(Cache));
  Hash *a = put(cache,10);
  // put(cache,13);
  Hash *c = put(cache,30); 
  printf(
      "index: %d data: %d\n",
      cache->nodes[a->index]->index,
      cache->nodes[a->index]->node->data
  );

  return 0;
}
