#include "header.h"
#include "tiles.h"

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

  Entity *blockArray = MemAlloc(sizeof(Entity)*tileset_32x32.rows*tileset_32x32.columns);
  for (int i = 0; i < tileset_32x32.rows; i++)
  {
    for (int j = 0; j < tileset_32x32.columns; j++)
    {
      createTile(tileset_32x32, blockArray, 1, (Vector2){i, j}, (Vector2){0, 0});
    }
  }

  Entity *tiles = deserializeTiles("data/save/level1.sav");

  Entity *entities = MemAlloc(sizeof(Entity) * entityCount);
  entities[0] = player;

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    float deltaTime = GetFrameTime();
    Vector2 mousePos = (Vector2){GetMouseX() + player.camera.target.x - player.camera.offset.x, GetMouseY() + player.camera.target.y - player.camera.offset.y};
    Vector2 mousePosGrid = (Vector2){(int)(mousePos.x / 32) * 32, (int)(mousePos.y / 32) * 32};

    animate(&player);
    playerMovement(&player, deltaTime, tiles);

    tileControls(tiles, blockArray, tileset_32x32.rows*tileset_32x32.columns, mousePosGrid);
    if (IsKeyPressed(KEY_N))
    {
      player.noclip = !player.noclip ? true : false;
    }
    if (IsKeyPressed(KEY_I))
    {
      player.position.x = 600.0f;
      player.position.y = 600.0f;
      player.velocity.x = 0.0f;
      player.velocity.y = 0.0f;
    }

    BeginDrawing();
    ClearBackground((Color){24, 24, 24, 255});

    BeginMode2D(player.camera);
      renderEntity(player);
      renderEntities(tiles, tileCount);
    EndMode2D();

    // current tile
    renderEntityV(blockArray[blockIndex], (Vector2){100, height-100});
    DrawText(TextFormat("%d", blockIndex), 100, height-100, 20, WHITE);

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

  //serializeTiles(tiles, "data/save/level1.sav");

  CloseWindow();
  return 0;
}
