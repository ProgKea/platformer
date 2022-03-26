#include "header.h"

int main(void)
{
  const int width = 1200;
  const int height = 620;
  InitWindow(width, height, "Platformer");

  Entity player = createPlayer();
  Tileset tileset_32x32;
  tileset_32x32.texture = LoadTexture("data/option_2/tiles/tileset_32x32(new).png");
  tileset_32x32.rows = 4;
  tileset_32x32.columns = 2;
  tileset_32x32.size = 32;
  Entity grassBlock = createTile(tileset_32x32, 1, (Vector2){2,0});
  grassBlock.position = (Vector2){(float)width/2-(float)grassBlock.rect.width/2, (float)height/2};
  Entity grassBlock1 = createTile(tileset_32x32, 1, (Vector2){0,0});
  grassBlock1.position = (Vector2){grassBlock.position.x - grassBlock1.rect.width*2, (float)height/2};
  Entity *tiles[TILES] = {&grassBlock, &grassBlock1};
  Entity *entities[ENTITIES] = {&player, *tiles};

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    float deltaTime = GetFrameTime();

    animate(&player);
    playerMovement(&player, deltaTime, tiles);

    BeginDrawing();

    DrawRectangleGradientV(0, 0, width, height / 2, BLUE, WHITE);
    DrawRectangleGradientV(0, height / 2, width, height / 2, WHITE, RED);

    renderEntity(player);
    for (int i = 0; i < TILES; i++)
      renderEntity(*tiles[i]);

    DrawFPS(10, 10);
    EndDrawing();
  }

  unloadEntities(*entities);
  unloadAnimationTextures(*animationTextures);

  CloseWindow();
  return 0;
}
