#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "util.h"

typedef struct {
  Texture2D texture;
  Vector2 position;
  Rectangle source;
  Rectangle destination;
} Background;

Background *initiate_backgrounds();
void draw_background(Background *background);
void update_background(Background *background, int screenwidth,
                       int screenheight);
void destroy_background(Background *background);

#endif // !BACKGROUND_H
