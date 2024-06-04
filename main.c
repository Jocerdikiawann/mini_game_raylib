#include "background.h"
#include "sprites.h"
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

    // if (IsKeyDown(KEY_RIGHT)) {
    //   if (samurai_rec.width < 0)
    //     samurai_rec.width = -samurai_rec.width;
    //   grass_and_road_pos.x += GetFrameTime() * 100;
    //   face_pos.x += GetFrameTime() * 100;
    //   grass_pos.x += GetFrameTime() * 100;
    //   jungle_bg_pos.x += GetFrameTime() * 100;
    //   tree_and_bushes_pos.x += GetFrameTime() * 100;

    //   ++frame_delay_counter;
    //   if (frame_delay_counter >= frame_delay) {
    //     frame_delay_counter = 0;
    //     ++frame_index;
    //     frame_index %= num_frame_samurai;
    //     samurai_rec.x = (float)frame_index * samurai_rec.width;
    //   }
    // } else if (IsKeyDown(KEY_LEFT)) {
    //   if (samurai_rec.width > 0)
    //     samurai_rec.width = -samurai_rec.width;
    //   grass_and_road_pos.x -= GetFrameTime() * 100;
    //   face_pos.x -= GetFrameTime() * 100;
    //   grass_pos.x -= GetFrameTime() * 100;
    //   jungle_bg_pos.x -= GetFrameTime() * 100;
    //   tree_and_bushes_pos.x -= GetFrameTime() * 100;

    //   ++frame_delay_counter;
    //   if (frame_delay_counter >= frame_delay) {
    //     frame_delay_counter = 0;
    //     if (frame_index == 0) {
    //       frame_index = num_frame_samurai - 1;
    //     } else {
    //       --frame_index;
    //     }
    //     samurai_rec.x = (float)frame_index * samurai_rec.width;
    //   }
    // } else {
    //   ++frame_delay_counter;
    //   if (frame_delay_counter >= frame_delay) {
    //     frame_delay_counter = 0;
    //     ++frame_index;
    //     frame_index %= num_frame_samurai_idle;
    //     samurai_rec_idle.x = (float)frame_index * samurai_rec_idle.width;
    //   }
    // }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (IsKeyDown(KEY_RIGHT)) {
      update_background(&background, w, h, MOVE_RIGHT);
      set_current_sprite(&sprites, &current_sprite, 1);
      update_sprite(&current_sprite, w, h, MOVE_RIGHT, &frame);
    } else if (IsKeyDown(KEY_LEFT)) {
      update_background(&background, w, h, MOVE_LEFT);
      set_current_sprite(&sprites, &current_sprite, 1);
      update_sprite(&current_sprite, w, h, MOVE_LEFT, &frame);
    } else {
      update_background(&background, w, h, IDLE);
      set_current_sprite(&sprites, &current_sprite, 0);
      update_sprite(&current_sprite, w, h, IDLE, &frame);
    }
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
