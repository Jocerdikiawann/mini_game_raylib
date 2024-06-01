#include "background.h"
#include <raylib.h>

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);

  int factor = 70, fullWidth = factor * 16, fullHeight = factor * 9;

  ChangeDirectory("./assets/");

  InitWindow(fullWidth, fullHeight, "Game");
  InitAudioDevice();

  Music music = LoadMusicStream("music/background_music.ogg");
  // Load the textures
  Texture2D t_samurai = LoadTexture("Samurai/Run.png");
  Texture2D t_samurai_idle = LoadTexture("Samurai/Idle.png");
  Texture2D t_samurai_jump = LoadTexture("Samurai/Jump.png");

  Texture2D t_sky = LoadTexture("Bg_Bright/sky.png");
  Texture2D t_grass_and_road = LoadTexture("Bg_Bright/grass&road.png");
  Texture2D t_face = LoadTexture("Bg_Bright/tree_face.png");
  Texture2D t_grass = LoadTexture("Bg_Bright/grasses.png");
  Texture2D t_jungle_bg = LoadTexture("Bg_Bright/jungle_bg.png");
  Texture2D t_tree_and_bushes = LoadTexture("Bg_Bright/trees&bushes.png");

  // Set position of the textures
  Vector2 face_pos = {0, 0};
  Vector2 grass_and_road_pos = {0, 0};
  Vector2 sky_pos = {0, 0};
  Vector2 grass_pos = {0, 0};
  Vector2 jungle_bg_pos = {0, 0};
  Vector2 tree_and_bushes_pos = {0, 0};

  // Set the frame of the samurai
  int num_frame_samurai = 8, num_frame_samurai_idle = 6;
  unsigned int frame_delay = 5;
  unsigned int frame_delay_counter = 0;
  unsigned int frame_index = 0;

  // Set the rectangle of the samurai
  Rectangle samurai_rec_idle = {
      0.0f,
      0.0f,
      (float)t_samurai_idle.width / num_frame_samurai_idle,
      (float)t_samurai_idle.height,
  };
  Rectangle samurai_rec = {
      0.0f,
      0.0f,
      (float)t_samurai.width / num_frame_samurai,
      (float)t_samurai.height,
  };

  PlayMusicStream(music);

  SetTargetFPS(60);

  initiate_backgrounds();

  // Main loop
  while (!WindowShouldClose()) {
    UpdateMusicStream(music);
    int w = GetScreenWidth(), h = GetScreenHeight();

    Vector2 samurai_pos = {(float)t_samurai.width * .2f, (float)h * .6f};
    Vector2 samurai_idle_pos = {(float)t_samurai_idle.width * .2f,
                                (float)h * .6f};

    if (IsKeyDown(KEY_RIGHT)) {
      if (samurai_rec.width < 0)
        samurai_rec.width = -samurai_rec.width;
      grass_and_road_pos.x += GetFrameTime() * 100;
      face_pos.x += GetFrameTime() * 100;
      grass_pos.x += GetFrameTime() * 100;
      jungle_bg_pos.x += GetFrameTime() * 100;
      tree_and_bushes_pos.x += GetFrameTime() * 100;

      ++frame_delay_counter;
      if (frame_delay_counter >= frame_delay) {
        frame_delay_counter = 0;
        ++frame_index;
        frame_index %= num_frame_samurai;
        samurai_rec.x = (float)frame_index * samurai_rec.width;
      }
    } else if (IsKeyDown(KEY_LEFT)) {
      if (samurai_rec.width > 0)
        samurai_rec.width = -samurai_rec.width;
      grass_and_road_pos.x -= GetFrameTime() * 100;
      face_pos.x -= GetFrameTime() * 100;
      grass_pos.x -= GetFrameTime() * 100;
      jungle_bg_pos.x -= GetFrameTime() * 100;
      tree_and_bushes_pos.x -= GetFrameTime() * 100;

      ++frame_delay_counter;
      if (frame_delay_counter >= frame_delay) {
        frame_delay_counter = 0;
        if (frame_index == 0) {
          frame_index = num_frame_samurai - 1;
        } else {
          --frame_index;
        }
        samurai_rec.x = (float)frame_index * samurai_rec.width;
      }
    } else {
      ++frame_delay_counter;
      if (frame_delay_counter >= frame_delay) {
        frame_delay_counter = 0;
        ++frame_index;
        frame_index %= num_frame_samurai_idle;
        samurai_rec_idle.x = (float)frame_index * samurai_rec_idle.width;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexturePro(t_sky, (Rectangle){0, 0, t_sky.width, t_sky.height},
                   (Rectangle){sky_pos.x, sky_pos.y, w, h}, (Vector2){0, 0}, 0,
                   WHITE);
    DrawTexturePro(
        t_jungle_bg,
        (Rectangle){jungle_bg_pos.x, jungle_bg_pos.y, w, t_jungle_bg.height},
        (Rectangle){0, 0, w, h}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(t_tree_and_bushes,
                   (Rectangle){tree_and_bushes_pos.x, tree_and_bushes_pos.y, w,
                               t_tree_and_bushes.height},
                   (Rectangle){0, 0, w, h}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(t_grass,
                   (Rectangle){grass_pos.x, grass_pos.y, w, t_grass.height},
                   (Rectangle){0, 0, w, h}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(t_grass_and_road,
                   (Rectangle){grass_and_road_pos.x, grass_and_road_pos.y, w,
                               t_grass_and_road.height},
                   (Rectangle){0, 0, w, h}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(t_face,
                   (Rectangle){face_pos.x, face_pos.y, w, t_face.height},
                   (Rectangle){0, 0, w, h}, (Vector2){0, 0}, 0, WHITE);

    // Center of the t_grass_and_road
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)) {
      DrawTextureRec(t_samurai, samurai_rec, samurai_pos, WHITE);
    } else {
      DrawTextureRec(t_samurai_idle, samurai_rec_idle, samurai_idle_pos, WHITE);
    }
    EndDrawing();
  }

  UnloadTexture(t_sky);
  UnloadTexture(t_grass_and_road);
  UnloadTexture(t_face);
  UnloadTexture(t_samurai);
  UnloadMusicStream(music);
  CloseAudioDevice();

  CloseWindow();
  return 0;
}
