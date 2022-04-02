#include "tiles.h"
#include <raylib.h>
#include <stdbool.h>

int tileCount = 0;
int tileLimit = 1000;

Entity createTile(Tileset tileset, int blockScale, Vector2 target_block, Vector2 position)
{
  Entity tile;

  tile.texture = tileset.texture;
  tile.texture.width *= blockScale;
  tile.texture.height *= blockScale;

  tile.rect.x = (float)tile.texture.width / tileset.rows * target_block.x;
  tile.rect.y = (float)tile.texture.height / tileset.columns * target_block.y;
  tile.rect.width = (float)tile.texture.width / tileset.rows;
  tile.rect.height = (float)tile.texture.height / tileset.columns;

  tile.position = position;

  tile.isFlipped = false;

  return tile;
}

bool blockPosExists(Entity blockArray[], int length, Vector2 srcPos)
{
  for (int i = 0; i<length; i++)
  {
    if (CheckCollisionPointRec(srcPos, 
          (Rectangle){
          blockArray[i].position.x, blockArray[i].position.y,
          blockArray[i].rect.width, blockArray[i].rect.height}))
    {
      return true;
    }
  }
  return false;
}

void placeBlock(Entity *tileArray, Entity tile, Vector2 targetPosition)
{
  if (!blockPosExists(tileArray, tileCount, targetPosition) && !(tileCount >= tileLimit))
  {
    tile.position = targetPosition;
    tileArray[tileCount] = tile;
    tileCount++;
  }
}

void drawDebugGrid(int width, int height)
{
  for (int i = 0; i < width/32; i++)
  {
    DrawLine(i*32, 0, i*32, height, BLACK);
  }
  for (int i = 0; i < height/32; i++)
  {
    DrawLine(0, i*32, width, i*32, BLACK);
  }
}
