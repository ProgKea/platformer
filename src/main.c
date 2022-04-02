#include "entity.h"
#include "header.h"
#include <raylib.h>
#include <stdio.h>

const int width = 1200;
const int height = 620;

int main(void)
{
  InitWindow(width, height, "Platformer");
  SetConfigFlags(FLAG_VSYNC_HINT);

  Entity player = createPlayer();

  Tileset tileset_32x32;
  tileset_32x32.texture = LoadTexture("data/sprites/tiles/tileset_32x32(new).png");
  tileset_32x32.rows = 4*3;
  tileset_32x32.columns = 2*3;

  Entity grassBlock = createTile(tileset_32x32, 1, (Vector2){7,0}, (Vector2){0,0});

  Entity *tiles = MemAlloc(sizeof(Entity) * tileLimit);
  Entity *entities = MemAlloc(sizeof(Entity) * entityCount);
  entities[0] = player;

  SetTargetFPS(GetMonitorRefreshRate(0));

  while (!WindowShouldClose())
  {
    float deltaTime = GetFrameTime();

    animate(&player);
    playerMovement(&player, deltaTime, tiles);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      placeBlock(tiles, grassBlock, (Vector2){GetMouseX()/32*32, GetMouseY()/32*32});
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
      removeBlock(tiles, (Vector2){GetMouseX()/32*32, GetMouseY()/32*32});
    }
    if (IsKeyDown(KEY_J))
    {
      player.position = GetMousePosition();
      player.velocity.y = 0;
    }
    if (IsKeyPressed(KEY_R))
    {
      MemFree(tiles);
      tiles = MemAlloc(sizeof(Entity) * tileLimit);
      tileCount = 0;
    }

    BeginDrawing();

    ClearBackground(BLACK);

    renderEntity(player);
    renderEntities(tiles, tileCount);

    DrawFPS(10, 10);
    EndDrawing();
  }

  if (tiles != NULL)
  {
    MemFree(tiles);
  }
  if (entities != NULL)
  {
    MemFree(entities);
  }
  unloadAnimationTextures(*animationTextures);

  CloseWindow();
  return 0;
}
