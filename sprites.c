#include "sprites.h"
#include <raylib.h>

// Todo:
// - Get file from assets, load every sprites
// - Set Type Sprite [Hero | Villain]
// - Set Current Sprites
Sprite create_sprite(char *filename, int num_frames, int screenwidth,
                     int screenheight) {
  Sprite sprite;
  const char *path = TextFormat("%s/%s", GetWorkingDirectory(), filename);
  sprite.texture = LoadTexture(path);
  // On main loop we will update the position of the sprite
  sprite.position = (Vector2){sprite.texture.width * .2f, screenheight * .6f};
  sprite.frame_rec =
      (Rectangle){0.0f, 0.0f, (float)sprite.texture.width / num_frames,
                  (float)sprite.texture.height};
  sprite.num_frames = num_frames;
  return sprite;
}
