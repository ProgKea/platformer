#include "tiles.h"

Entity createTile(Tileset tileset, float block_scale, Vector2 target_block)
{
  Entity tile;

  tile.texture = tileset.texture;
  tile.texture.width *= block_scale;
  tile.texture.height *= block_scale;

  tile.rect.x = (float)tile.texture.width / tileset.rows * target_block.x;
  tile.rect.y = (float)tile.texture.height / tileset.columns * target_block.y;
  tile.rect.width = (float)tile.texture.width / tileset.rows;
  tile.rect.height = (float)tile.texture.height / tileset.columns;

  return tile;
}
