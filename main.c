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
  indexed_node->index = node->data%CAPACITY;
  indexed_node->node = node;
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
  node->data = data;
  node->next = head;
  node->prev = NULL;

  if (head != NULL)
  {
    head->prev = node;
  }
  head = node;

  if (tail == NULL)
  {
    tail = node;
  }
  Hash *indexed_node = indexing(node);
  collision_handle(cache, indexed_node);
  return indexed_node;
}


void reordenation(Hash *result)
{
  if(result->node != head)
  {
    Node *result_next_node = result->node->next;
    Node *result_prev_node = result->node->prev;   

    if (result_next_node != NULL)
    {
      result_next_node->prev = result_prev_node;
    }
    if (result_prev_node != NULL)
    {
      result_prev_node->next = result_next_node;
    }

    if (result->node == tail)
    {
      tail = result->node->prev;
    }
    result->node->prev = NULL;
    result->node->next = head;
    head->prev = result->node;
    head = result->node;
  }  
}


Hash* search(Cache *cache, int data)
{
  Hash *result = cache->nodes[data%CAPACITY];
  if(result != NULL)
  { 
    while (result->node->data != data)
    {
      result = result->next;
    }
  }
  return result;
}


int get(Cache *cache, int data)
{
  Hash *result = search(cache, data);
  reordenation(result);
  return result->node->data;
}

// TODO: SIGEGV bug if user try to get the old value
int update(Cache *cache, int old_data, int new_data)
{
  Hash *data = search(cache, old_data);
  reordenation(data);
  free(data->node);
  free(data);
  data = put(cache, new_data);
  return data->node->data;
}


int main (void)
{
  Cache *cache = malloc(sizeof(Cache));
  put(cache,10);
  update(cache,10,66);
  int a = get(cache,10);
  printf("%d", a);

  return 0;
}
