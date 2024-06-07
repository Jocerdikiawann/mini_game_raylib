#include "background.h"
#include "sprites.h"
#include "util.h"
#include <raylib.h>

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);

  int factor = 70, fullWidth = factor * 16, fullHeight = factor * 9;

  ChangeDirectory("./assets/");

  InitWindow(fullWidth, fullHeight, "Simple Game");
  InitAudioDevice();

  Music music = LoadMusicStream("music/background_music.ogg");

  Backgrounds background = initiate_backgrounds();
  Sprites sprites = initiate_heros_sprite();
  Sprite current_sprite = {};

  Frame frame = {.frame_delay = 5, .frame_index = 0, .frame_delay_counter = 0};
  select_texture_sprite_by_condition(&sprites, &current_sprite, IDLE);

  PlayMusicStream(music);
  SetTargetFPS(60);

  // Main loop
  while (!WindowShouldClose()) {
    UpdateMusicStream(music);
    int w = GetScreenWidth(), h = GetScreenHeight();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (IsKeyDown(KEY_RIGHT)) {
      update_background(&background, w, h, MOVE_RIGHT);
      set_current_sprite(&sprites, &current_sprite, 1);
    } else if (IsKeyDown(KEY_LEFT)) {
      update_background(&background, w, h, MOVE_LEFT);
      set_current_sprite(&sprites, &current_sprite, 1);
    } else if (IsKeyDown(KEY_SPACE)) {
      update_background(&background, w, h, JUMP);
      set_current_sprite(&sprites, &current_sprite, 2);
    } else {
      update_background(&background, w, h, IDLE);
      set_current_sprite(&sprites, &current_sprite, 0);
    }

    update_sprite(&current_sprite, w, h, MOVE_RIGHT, &frame);
    draw_background(&background);
    draw_sprite(&current_sprite);

    EndDrawing();
  }

  destroy_background(&background);
  destroy_sprite(&sprites);
  UnloadMusicStream(music);
  CloseAudioDevice();

  CloseWindow();
  return 0;
}
