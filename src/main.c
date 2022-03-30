#include "header.h"
#include "tiles.h"

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

  Entity grassBlock = createTile(tileset_32x32, (Vector2){2,0});
  grassBlock.position = (Vector2){32 * 10, 32 * 15};

  Entity dirtBlock = createTile(tileset_32x32, (Vector2){0,0});
  dirtBlock.position = (Vector2){32 * 10, 32 * 14};

  Entity *tiles[TILES] = {&grassBlock, &dirtBlock};
  Entity *entities[ENTITIES] = {&player, *tiles};

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    float deltaTime = GetFrameTime();

    animate(&player);
    playerMovement(&player, deltaTime, tiles);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
      // create a new tile and add it to the tiles array at the mouse position in the grid
      tiles[0]->position = (Vector2){GetMouseX() / 32 * 32, GetMouseY() / 32 * 32};
    }

    BeginDrawing();

    DrawRectangleGradientV(0, 0, width, height / 2, BLUE, WHITE);
    DrawRectangleGradientV(0, height / 2, width, height / 2, WHITE, RED);

    renderEntity(player);
    for (int i = 0; i < TILES; i++)
      if (tiles[i] != NULL)
        renderEntity(*tiles[i]);

    DrawFPS(10, 10);
    EndDrawing();
  }

  unloadEntities(*entities);
  unloadAnimationTextures(*animationTextures);

  CloseWindow();
  return 0;
}
