#include <raylib.h>

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);

  int factor = 70, fullWidth = factor * 16, fullHeight = factor * 9;

  ChangeDirectory("./assets/");

  InitWindow(fullWidth, fullHeight, "Game");
  Texture2D t_sky = LoadTexture("Bg_Bright/sky.png");
  Vector2 sky_pos = {0, 0};

  Texture2D t_grass_and_road = LoadTexture("Bg_Bright/grass&road.png");
  Vector2 grass_and_road_pos = {0, 0};

  Texture2D t_face = LoadTexture("Bg_Bright/tree_face.png");
  Vector2 face_pos = {0, 0};

  Texture2D t_samurai = LoadTexture("Samurai/Idle.png");
  Rectangle samurai_rec = {0.0f, 0.0f, (float)t_samurai.width / 6,
                           (float)t_samurai.height};
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    int w = GetScreenWidth(), h = GetScreenHeight();

    Vector2 samurai_pos = {(float)t_grass_and_road.width / 2 - t_samurai.width -
                               100,
                           (float)h / 2 - (float)t_samurai.height / 2 + 100};

    grass_and_road_pos.x += GetFrameTime() * 100;
    face_pos.x += GetFrameTime() * 100;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(t_sky, (Rectangle){0, 0, t_sky.width, t_sky.height},
                   (Rectangle){sky_pos.x, sky_pos.y, w, h}, (Vector2){0, 0}, 0,
                   WHITE);
    DrawTexturePro(t_grass_and_road,
                   (Rectangle){grass_and_road_pos.x, grass_and_road_pos.y, w,
                               t_grass_and_road.height},
                   (Rectangle){0, 0, w, h}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(t_face,
                   (Rectangle){face_pos.x, face_pos.y, w, t_face.height},
                   (Rectangle){0, 0, w, h}, (Vector2){0, 0}, 0, WHITE);

    // Center of the t_grass_and_road
    DrawTextureRec(t_samurai, samurai_rec, samurai_pos, WHITE);
    EndDrawing();
  }

  UnloadTexture(t_sky);
  UnloadTexture(t_grass_and_road);
  UnloadTexture(t_face);
  UnloadTexture(t_samurai);

  CloseWindow();
  return 0;
}
