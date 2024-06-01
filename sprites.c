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
Sprite *initiate_heros_sprite() {
  Sprite *sprites = malloc(sizeof(Sprite) * 2);
  // TODO: Loop sprites soon
  sprites[0] = create_sprite("Samurai/Idle.png", 6);
  sprites[1] = create_sprite("Samurai_Commander/Idle.png", 6);
  return sprites;
}

void draw_sprite(Sprite *sprite) {
  BeginDrawing();
  DrawTextureRec(sprite->texture, sprite->frame_rec, sprite->position, WHITE);
  EndDrawing();
}

void update_sprite(Sprite *sprite, int screenwidth, int screenheight) {
  sprite->position =
      (Vector2){(float)sprite->texture.width * .2f, screenheight * .6f};
}

void destroy_sprite(Sprite *sprite) { UnloadTexture(sprite->texture); }
