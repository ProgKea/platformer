#include "header.h"
#include <raylib.h>

int main(void)
{
  const int width = 1200;
  const int height = 620;
  InitWindow(width, height, "Platformer");

  Entity player = createPlayer();

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    float deltaTime = GetFrameTime();

    // Player
    animate(4, &player.rect, (float)player.texture.width / player.frames);
    playerMovement(&player, 250.0, deltaTime);

    BeginDrawing();

    DrawRectangleGradientV(0, 0, width, height, LIGHTGRAY, WHITE);
    renderEntity(player);

    DrawFPS(10, 10);
    EndDrawing();
  }

  UnloadTexture(player.texture);
  CloseWindow();
  return 0;
}
