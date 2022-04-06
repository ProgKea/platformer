#include "header.h"

const int width = 1200;
const int height = 620;

int main(void)
{
  InitWindow(width, height, "Platformer");

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
    Vector2 mousePos = (Vector2){GetMouseX() + player.camera.target.x - player.camera.offset.x, GetMouseY() + player.camera.target.y - player.camera.offset.y};
    Vector2 mousePosGrid = (Vector2){(int)(mousePos.x / 32) * 32, (int)(mousePos.y / 32) * 32};

    animate(&player);
    playerMovement(&player, deltaTime, tiles);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      placeBlock(tiles, grassBlock, mousePosGrid);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
      removeBlock(tiles, mousePosGrid);
    }
    if (IsKeyPressed(KEY_R))
    {
      resetTiles(tiles);
    }
    if (IsKeyPressed(KEY_N))
    {
      player.noclip = !player.noclip ? true : false;
    }

    BeginDrawing();
    ClearBackground((Color){24, 24, 24, 255});

    BeginMode2D(player.camera);
      renderEntity(player);
      renderEntities(tiles, tileCount);
    EndMode2D();

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
