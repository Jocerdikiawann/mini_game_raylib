#include "background.h"
#include "util.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

int compare(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}
Backgrounds initiate_backgrounds() {
  // read path assets/background/*

  int w = GetScreenWidth(), h = GetScreenHeight();
  const char *asset_path = TextFormat("%s/background", GetWorkingDirectory());
  FilePathList path_list = LoadDirectoryFiles(asset_path);
  FilePathList sub_dirs;
  Backgrounds background = {};

  for (int i = 0; i < path_list.count; ++i) {
    sub_dirs = LoadDirectoryFiles(path_list.paths[i]);
    // qsort(sub_dirs.paths, sub_dirs.count, sizeof(char *), compare);
    for (int j = 0; j < sub_dirs.count; ++j) {
      Background bg = {
          // Must be freed
          .texture = LoadTexture(sub_dirs.paths[j]),
          .source = (Rectangle){0, 0, bg.texture.width, bg.texture.height},
          .destination = (Rectangle){0, 0, w, h},
      };
      append(background, bg);
      printf("Loaded %s\n", sub_dirs.paths[j]);
    }
  }

  UnloadDirectoryFiles(sub_dirs);
  UnloadDirectoryFiles(path_list);

  return background;
}

void update_background(Backgrounds *background, int screenwidth,
                       int screenheight, Instruction instruction) {
  for (int i = 0; i < background->count; ++i) {
    if (instruction == MOVE_LEFT)
      background->items[i].source.x -= GetFrameTime() * 100;
    if (instruction == MOVE_RIGHT)
      background->items[i].source.x += GetFrameTime() * 100;

    background->items[i].destination.width = screenwidth;
    background->items[i].destination.height = screenheight;
  }
}

void draw_background(Backgrounds *background) {
  for (int i = 0; i < background->count; ++i) {
    DrawTexturePro(background->items[i].texture, background->items[i].source,
                   background->items[i].destination, (Vector2){0, 0}, 0, WHITE);
  }
}

void destroy_background(Backgrounds *background) {
  for (int i = 0; i < background->count; ++i) {
    UnloadTexture(background->items[i].texture);
  }
  free(background->items);
  background->items = NULL;
  background->count = background->capacity = 0;
}
