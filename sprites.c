#include "sprites.h"
#include "util.h"
#include <raylib.h>
#include <string.h>

// Todo:
// - Get file from assets, load every sprites
// - Set Type Sprite [Hero | Villain]
// - Set Current Sprites
Sprite create_sprite(char *filename, int num_frames, Instruction condition) {
  Sprite sprite;
  const char *path = TextFormat("%s/%s", GetWorkingDirectory(), filename);
  sprite.texture = LoadTexture(path);
  // On main loop we will update the position of the sprite
  sprite.position = (Vector2){0, 0};
  sprite.frame_rec =
      (Rectangle){0.0f, 0.0f, (float)sprite.texture.width / num_frames,
                  (float)sprite.texture.height};
  sprite.num_frames = num_frames;
  sprite.condition = condition;
  return sprite;
}

// For Menu
Sprites initiate_heros_sprite() {
  Sprites sprites = {};
  // TODO: Loop sprites soon
  append(sprites, create_sprite("sprites/Samurai/Idle.png", 6, IDLE));
  append(sprites, create_sprite("sprites/Samurai/Run.png", 8, MOVE_RIGHT));
  append(sprites, create_sprite("sprites/Samurai/Jump.png", 9, JUMP));
  return sprites;
}

Sprites initiate_villains_sprite() {
  Sprites sprites = {};
  return sprites;
}

void set_current_sprite(Sprites *sprites, Sprite *current, int index) {
  memcpy(current, &sprites->items[index], sizeof(Sprites));
}

// NOTE: Don't use
void select_texture_sprite_by_condition(Sprites *sprites, Sprite *current,
                                        Instruction condition) {
  for (int i = 0; i < sprites->count; ++i) {
    if (sprites->items[i].condition == condition) {
      memcpy(current, &sprites->items[i], sizeof(Sprite));
      break;
    }
  }
}

void draw_sprite(Sprite *sprite) {

  DrawTextureRec(sprite->texture, sprite->frame_rec, sprite->position, WHITE);
}

void update_sprite(Sprite *sprite, int screenwidth, int screenheight,
                   Instruction instruction, Frame *frame) {
  sprite->position =
      (Vector2){sprite->texture.width * .2f, (float)screenheight * .6f};

  switch (GetKeyPressed()) {
  case KEY_RIGHT:
    if (sprite->frame_rec.width < 0)
      sprite->frame_rec.width = -sprite->frame_rec.width;

    ++frame->frame_delay_counter;
    if (frame->frame_delay_counter >= frame->frame_delay) {
      frame->frame_delay_counter = 0;
      ++frame->frame_index;
      frame->frame_index %= sprite->num_frames;
      sprite->frame_rec.x = (float)frame->frame_index * sprite->frame_rec.width;
    }
    break;
  case KEY_LEFT:
    if (sprite->frame_rec.width > 0)
      sprite->frame_rec.width = -sprite->frame_rec.width;

    ++frame->frame_delay_counter;
    if (frame->frame_delay_counter >= frame->frame_delay) {
      frame->frame_delay_counter = 0;
      if (frame->frame_index == 0)
        frame->frame_index = sprite->num_frames - 1;
      else
        --frame->frame_index;
      sprite->frame_rec.x = (float)frame->frame_index * sprite->frame_rec.width;
    }
    break;

  case KEY_SPACE:
    if (sprite->frame_rec.width < 0)
      sprite->frame_rec.width = -sprite->frame_rec.width;

    ++frame->frame_delay_counter;
    if (frame->frame_delay_counter >= frame->frame_delay) {
      frame->frame_delay_counter = 0;
      ++frame->frame_index;
      frame->frame_index %= sprite->num_frames;
      sprite->frame_rec.x = (float)frame->frame_index * sprite->frame_rec.width;
    }
    break;
  default:
    ++frame->frame_delay_counter;
    if (frame->frame_delay_counter >= frame->frame_delay) {
      frame->frame_delay_counter = 0;
      ++frame->frame_index;
      frame->frame_index %= sprite->num_frames;
      sprite->frame_rec.x = (float)frame->frame_index * sprite->frame_rec.width;
    }
    break;
  }
}

void destroy_sprite(Sprites *sprite) {
  for (int i = 0; i < sprite->count; ++i) {
    UnloadTexture(sprite->items[i].texture);
  }
  free(sprite->items);
  sprite->items = NULL;
  sprite->count = sprite->capacity = 0;
}
