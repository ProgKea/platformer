#include "header.h"

int main(void)
{
  const int width = 1200;
  const int height = 620;
  InitWindow(width, height, "Platformer");
  
  Entity player = createPlayer();
  Entity grassBlock = createTile(32, 1, (Vector2){4,2}, (Vector2){0,0}, LoadTexture("data/option_2/tiles/tileset_32x32(new).png"));
  grassBlock.position = (Vector2){100, 100};
  Entity *entities[ENTITIES] = {&player, &grassBlock};

  SetTargetFPS(60);

  while (!WindowShouldClose())
    {
      float deltaTime = GetFrameTime();

      // Player
      animate(&player);
      playerMovement(&player, deltaTime);
      
      BeginDrawing();
      
      DrawRectangleGradientV(0, 0, width, height / 2, BLUE, WHITE);
      DrawRectangleGradientV(0, height / 2, width, height / 2, WHITE, RED);
      
      renderEntity(player);
      renderEntity(grassBlock);
      
      DrawFPS(10, 10);
      EndDrawing();
    }

  unloadEntities(*entities);
  unloadAnimationTextures(*animationTextures);

  CloseWindow();
  return 0;
}
