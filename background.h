#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "util.h"

typedef struct {
  Texture2D texture;
  Rectangle source;
  Rectangle destination;
} Background;

typedef struct {
  Background *items;
  size_t count, capacity;
} Backgrounds;

Backgrounds initiate_backgrounds();
void update_background(Backgrounds *background, int screenwidth,
                       int screenheight, Instruction instruction);
void draw_background(Backgrounds *background);
void destroy_background(Backgrounds *background);

#endif // !BACKGROUND_H
