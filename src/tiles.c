#include "tiles.h"

Entity createTile(Tileset tileset, Vector2 target_block)
{
  Entity tile;

  tile.texture = tileset.texture;
  tile.texture.width /= 3;
  tile.texture.height /= 3;

  tile.rect.x = (float)tile.texture.width / tileset.rows * target_block.x;
  tile.rect.y = (float)tile.texture.height / tileset.columns * target_block.y;
  tile.rect.width = (float)tile.texture.width / tileset.rows;
  tile.rect.height = (float)tile.texture.height / tileset.columns;

  return tile;
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
