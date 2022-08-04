#include "tiles.h"

int tileCount = 0;
int tileLimit = 1000;
int blockIndex = 0;
int blockCount = 0;

void createTile(Tileset tileset, Entity *blockArray, float blockScale, Vector2 target_block, Vector2 position)
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

  blockArray[blockCount] = tile;
  blockCount++;
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
  //if (tileCount+1 >= tileLimit && tileArray != NULL)
  //{
    //// reallocate memory wihout losing the old data and without double free error
    //Entity *newTileArray = MemAlloc(sizeof(Entity) * tileLimit * 2);
    //for (int i = 0; i < tileLimit; i++)
    //{
      //newTileArray[i] = tileArray[i];
    //}
    //MemFree(tileArray);
    //tileArray = newTileArray;
    //tileLimit *= 2;
  //}
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

void resetTiles(Entity *tileArray)
{
  MemFree(tileArray);
  tileArray = MemAlloc(sizeof(Entity) * tileLimit);
  tileCount = 0;
}

void tileControls(Entity *tileArray, Entity *blockArray, int blockArraySize, Vector2 position)
{
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
  {
    placeBlock(tileArray, blockArray[blockIndex], position);
  }
  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
  {
    removeBlock(tileArray, position);
  }
  if (IsKeyPressed(KEY_R))
  {
    resetTiles(tileArray);
  }
  if (IsKeyPressed(KEY_RIGHT))
  {
    if (blockIndex < blockArraySize)
    {
      blockIndex++;
    }
  }
  if (IsKeyPressed(KEY_LEFT))
  {
    if (blockIndex > 0)
    {
      blockIndex--;
    }
  }
}

void serializeTiles(Entity *tileArray, char *fileName)
{
  FILE *file = fopen(fileName, "wb");
  fwrite(&tileCount, sizeof(int), 1, file);
  for (int i = 0; i < tileCount; i++)
  {
    fwrite(&tileArray[i].position, sizeof(Vector2), 1, file);
    fwrite(&tileArray[i].rect, sizeof(Rectangle), 1, file);
    fwrite(&tileArray[i].texture, sizeof(Texture), 1, file);
  }
  fclose(file);
}

Entity *deserializeTiles(char *fileName)
{
  FILE *file = fopen(fileName, "rb");
  Entity *tileArray = MemAlloc(sizeof(Entity) * tileLimit);
  fread(&tileCount, sizeof(int), 1, file);
  for (int i = 0; i < tileCount; i++)
  {
    fread(&tileArray[i].position, sizeof(Vector2), 1, file);
    fread(&tileArray[i].rect, sizeof(Rectangle), 1, file);
    fread(&tileArray[i].texture, sizeof(Texture), 1, file);
  }
  fclose(file);
  return tileArray;
}
