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
  Node *node;

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
  cache->nodes[indexed_node->index]=indexed_node;
  return indexed_node;
}

int main (void)
{
  Cache *cache = malloc(sizeof(Cache));
  Hash *a = put(cache,10);
  Hash *b = put(cache,13);
  Hash *c = put(cache,30); 
  printf(
      "index: %d data: %d\n",
      cache->nodes[a->index]->index,
      cache->nodes[a->index]->node->data
  );
  printf(
      "index: %d data: %d\n",
      cache->nodes[b->index]->index,
      cache->nodes[b->index]->node->data
  );
  printf(
      "index: %d data: %d\n",
      cache->nodes[c->index]->index, 
      cache->nodes[c->index]->node->data
  );

  return 0;
}
