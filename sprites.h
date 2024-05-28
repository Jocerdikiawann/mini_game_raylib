#ifndef SPRITES_H
#define SPRITES_H
#include <raylib.h>

typedef struct {
  Texture2D texture;
  Vector2 position;
  Rectangle frame_rec;
  int num_frames;
} Sprite;

Sprite create_sprite(char *filename, int num_frames, int screenwidth,
                     int screenheight);
void draw_sprite(Sprite sprite);
void update_sprite(Sprite *sprite, int num_frames, int frame_delay);
void destroy_sprite(Sprite sprite);

// utility
void update_condition_sprite(Sprite *sprite);
void incrise_sprite_position(Sprite *sprite);
void decriase_sprite_position(Sprite *sprite);
void idle_sprite(Sprite *sprite);

#endif
