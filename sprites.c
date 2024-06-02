#include "sprites.h"

// Todo:
// - Get file from assets, load every sprites
// - Set Type Sprite [Hero | Villain]
// - Set Current Sprites
Sprite create_sprite(char *filename, int num_frames) {
  Sprite sprite;
  const char *path = TextFormat("%s/%s", GetWorkingDirectory(), filename);
  sprite.texture = LoadTexture(path);
  // On main loop we will update the position of the sprite
  sprite.position = (Vector2){0, 0};
  sprite.frame_rec =
      (Rectangle){0.0f, 0.0f, (float)sprite.texture.width / num_frames,
                  (float)sprite.texture.height};
  sprite.num_frames = num_frames;
  return sprite;
}

// For Menu
Sprites initiate_heros_sprite() {
  Sprites sprites = {};
  // TODO: Loop sprites soon
  append(sprites, create_sprite("Samurai/Idle.png", 6));
  append(sprites, create_sprite("Samurai/Run.png", 8));
  return sprites;
}

void draw_sprite(Sprite *sprite) {
  BeginDrawing();
  // Draw the condition of the sprite [Idle | Run | Jump | Attack | Hurt |
  // Defend]
  DrawTextureRec(sprite->texture, sprite->frame_rec, sprite->position, WHITE);
  EndDrawing();
}

void update_sprite(Sprite *sprite, int screenwidth, int screenheight,
                   Instruction instruction, Frame *frame) {
  switch (instruction) {
  case MOVE_LEFT:
    if (sprite->frame_rec.width > 0)
      sprite->frame_rec.width = -sprite->frame_rec.width;
    ++frame->frame_delay_counter;
    if (frame->frame_delay_counter >= frame->frame_delay) {
      frame->frame_delay_counter = 0;
      if (--frame->frame_index < 0)
        frame->frame_index = sprite->num_frames - 1;
      else
        --frame->frame_index;
      sprite->frame_rec.x = frame->frame_index * sprite->frame_rec.width;
    }
    break;
  case MOVE_RIGHT:
    if (sprite->frame_rec.width < 0)
      sprite->frame_rec.width = -sprite->frame_rec.width;
    ++frame->frame_delay_counter;
    if (frame->frame_delay_counter >= frame->frame_delay) {
      frame->frame_delay_counter = 0;
      ++frame->frame_index;
      frame->frame_index %= sprite->num_frames;
      sprite->frame_rec.x = frame->frame_index * sprite->frame_rec.width;
    }
    break;
  case JUMP:
    break;
  case ATTACK:
    break;
  case IDLE:
    ++frame->frame_delay_counter;
    if (frame->frame_delay_counter >= frame->frame_delay) {
      frame->frame_delay_counter = 0;
      ++frame->frame_index;
      frame->frame_index %= sprite->num_frames;
      sprite->frame_rec.x = frame->frame_index * sprite->frame_rec.width;
    }
    break;
  case HURT:
    break;
  case DEFEND:
    break;
  default:
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
