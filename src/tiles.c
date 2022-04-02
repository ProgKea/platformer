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
  for (int i = 0; i < length; i++)
  {
    if (blockArray[i].position.x == srcPos.x && blockArray[i].position.y == srcPos.y)
    {
      return true;
    }
  }
  return false;
}

void placeBlock(Entity *tileArray, Entity tile, Vector2 targetPosition)
{
  if (tileCount+1 >= tileLimit && tileArray != NULL)
  {
    // reallocate memory wihout losing the old data and without double free error
    Entity *newTileArray = MemAlloc(sizeof(Entity) * tileLimit * 2);
    for (int i = 0; i < tileLimit; i++)
    {
      newTileArray[i] = tileArray[i];
    }
    MemFree(tileArray);
    tileArray = newTileArray;
    tileLimit *= 2;
  }
  if (!blockPosExists(tileArray, tileCount, targetPosition) && !(tileCount >= tileLimit))
  {
    tile.position = targetPosition;
    tileArray[tileCount] = tile;
    tileCount++;
  }
}

void removeBlock(Entity *tileArray, Vector2 targetPosition)
{
  for (int i = 0; i < tileCount; i++)
  {
    if (tileArray[i].position.x == targetPosition.x && tileArray[i].position.y == targetPosition.y)
    {
      tileArray[i] = tileArray[tileCount-1];
      tileCount--;
      break;
    }
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
