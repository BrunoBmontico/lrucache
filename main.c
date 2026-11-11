#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 3


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
int cached_nodes = 0;


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


Hash** search(Cache *cache, int data)
{
  Hash **result = &cache->nodes[data%CAPACITY];
  while (*result != NULL && (*result)->node->data != data)
  {
    result = &(*result)->next;  
    
  }
  return result;
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
  
  if (cached_nodes >= CAPACITY)
  {
    tail->prev->next = NULL;
    Hash **indexed_tail = search(cache, tail->data);
    Hash *trash = *indexed_tail;
    *indexed_tail = trash->next;
    free(trash);
    free(tail);
    cached_nodes--;
  }

  Hash *indexed_node = indexing(node);
  collision_handle(cache, indexed_node);
  cached_nodes++;
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


int get(Cache *cache, int data)
{
  Hash **result = search(cache, data);
  if (*result == NULL) return -1;
  reordenation(*result);
  return (*result)->node->data;
}


int update(Cache *cache, int old_data, int new_data)
{
  Hash **result = search(cache, old_data);
  reordenation(*result);
  free((*result)->node);
  free(*result);
  *result = put(cache, new_data);
  return (*result)->node->data;
}

// TODO: print function of the cache in a ordered list
// feature for the data field and the rest of the code 
// accept any type of data.

int main (void)
{
  Cache *cache = malloc(sizeof(Cache));
  put(cache,1);
  put(cache,2);
  put(cache,3);

  int a = update(cache,1,5);
  printf("%d\n",a);
  int b = get(cache,1);
  printf("%d\n",b);
  int c = get(cache,5);
  printf("%d\n",c);
  return 0;
}
