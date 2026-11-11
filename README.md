# LRU Cache in C

An implementation of an **LRU Cache** (Least Recently Used Cache) written in pure C, with no external libraries.

## About the project

This project was born out of a **personal challenge**: to write an LRU Cache system in C **without copying code**, **without watching tutorials**, and **without using AI**. The only source of knowledge was **reading the theory behind the LRU algorithm** and applying those concepts directly in C.

The goal was to test my ability to:

- Understand an algorithm from theory alone;
- Translate abstract concepts into concrete data structures;
- Handle manual memory management (malloc/free);
- Implement doubly linked lists and hash tables from scratch;
- Write readable, well-organized code without outside help.

## How it works

The cache is made up of two main structures that work together:

- **Doubly linked list** — keeps track of the order in which elements are used. The most recently used node sits at the `head` and the least recently used at the `tail`. When the cache reaches its maximum capacity, the `tail` node is evicted.
- **Hash table with chaining** — provides fast access (O(1) on average) to the list nodes by mapping each stored value to its corresponding node.

### Main structures

```c
typedef struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct Hash {
  int index;
  Node *node;
  struct Hash *next;
} Hash;

typedef struct Cache {
  Hash *nodes[CAPACITY];
} Cache;
```

### Implemented operations

| Function           | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| `put`              | Inserts a new element into the cache, evicting the least recently used one if needed. |
| `get`              | Looks up an element and moves it to the `head` (most recently used).        |
| `update`           | Replaces the value of an existing element and reorders it.                  |
| `search`           | Internal lookup in the hash table.                                          |
| `reordenation`     | Moves a node to the `head` of the list.                                     |
| `collision_handle` | Handles hash table collisions via chaining.                                 |

## Project status

**This project is NOT finished yet.** This is only the **first part** completed.

### Future plans

- **Print function** to display the cache as an ordered list (a view of the cache's current state).
- **Generalize the `data` field** to accept **any data type** (currently limited to `int`).
- **Turn it into an API** using **FastAPI** (via C bindings or a rewrite of the core).
- **Make it a generic LRU Cache service**, able to handle any data sent to the API.

The end goal is to turn this C core into a **reusable cache service**, accessible over HTTP, that can be integrated into any system.

## Usage example

```c
int main(void) {
  Cache *cache = malloc(sizeof(Cache));

  put(cache, 1);
  put(cache, 2);
  put(cache, 3);

  int a = update(cache, 1, 5);  // replaces 1 with 5
  printf("%d\n", a);            // 5

  int b = get(cache, 1);        // 1 no longer exists
  printf("%d\n", b);            // -1

  int c = get(cache, 5);        // 5 exists
  printf("%d\n", c);            // 5

  return 0;
}
```

## Building

```bash
gcc main.c -o lru_cache
./lru_cache
```

## Notes
- Default capacity is set by the `CAPACITY` macro (currently 3).
- The code is intentionally didactic, favoring clarity over extreme optimization.
- Developed as a personal learning challenge, from theory to implementation, with no shortcuts.

## Author
Bruno Bonassi Montico (@BrunoBmontico)

⭐ If this project helped you in any way, consider giving the repository a star!
