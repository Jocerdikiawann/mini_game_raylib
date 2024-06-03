#ifndef UTIL_H
#define UTIL_H
#include <raylib.h>
#include <stdlib.h>

typedef enum {
  MOVE_LEFT,
  MOVE_RIGHT,
  JUMP,
  ATTACK,
  HURT,
  DEFEND,
  IDLE,
} Instruction;

typedef struct {
  unsigned int frame_delay, frame_delay_counter, frame_index;
} Frame;

#define append(v, d)                                                           \
  do {                                                                         \
    if (v.count >= v.capacity) {                                               \
      if (v.capacity == 0)                                                     \
        v.capacity = 256;                                                      \
      else                                                                     \
        v.capacity *= 2;                                                       \
      v.items = realloc(v.items, v.capacity * sizeof(*v.items));               \
    }                                                                          \
    v.items[v.count++] = d;                                                    \
  } while (0)

#endif // !UTIL_H
