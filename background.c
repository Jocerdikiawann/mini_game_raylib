#include "background.h"
#include <raylib.h>
#include <stdio.h>

Backgrounds *initiate_backgrounds() {
  // read path assets/background/*

  int w = GetScreenWidth(), h = GetScreenHeight();
  const char *asset_path = TextFormat("%s/background", GetWorkingDirectory());
  Backgrounds background = {};
  FilePathList path_list = LoadDirectoryFiles(asset_path);
  FilePathList sub_dirs;

  for (int i = 0; i < path_list.count; ++i) {
    sub_dirs = LoadDirectoryFiles(path_list.paths[i]);
    for (int j = 0; j < sub_dirs.count; ++j) {
      Background bg = {
          // Must be freed
          .texture = LoadTexture(sub_dirs.paths[i]),
          .source = (Rectangle){0, 0, bg.texture.width, bg.texture.height},
          .destination = (Rectangle){0, 0, w, h},
      };
      append(background, bg);
    }
  }

  UnloadDirectoryFiles(sub_dirs);
  UnloadDirectoryFiles(path_list);

  return NULL;
}
