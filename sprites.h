#ifndef SPRITES_H
#define SPRITES_H
#include "util.h"

typedef struct {
  Texture2D texture;
  Vector2 position;
  Rectangle frame_rec;
  int num_frames;
} Sprite;

Sprite *initiate_heros_sprite();
Sprite *initiate_villains_sprite();
Sprite set_current_sprite(int index);
void draw_sprite(Sprite *sprite);
void update_sprite(Sprite *sprite, int screenwidth, int screenheight);
void destroy_sprite(Sprite *sprite);

void move_right_sprite(Sprite *sprite);
void move_left_sprite(Sprite *sprite);
void idle_sprite(Sprite *sprite);
void jump_sprite(Sprite *sprite);

#endif
