#ifndef SPRITES_H
#define SPRITES_H
#include "util.h"

typedef struct {
  Texture2D texture;
  Vector2 position;
  Rectangle frame_rec;
  int num_frames;
} Sprite;

typedef struct {
  Sprite *items;
  size_t count, capacity;
} Sprites;

Sprites initiate_heros_sprite();
Sprites initiate_villains_sprite();
Sprite set_current_sprite(int index);

void draw_sprite(Sprite *sprite);
void update_sprite(Sprite *sprite, int screenwidth, int screenheight,
                   Instruction instruction, Frame *frame);
void destroy_sprite(Sprites *sprite);
#endif
