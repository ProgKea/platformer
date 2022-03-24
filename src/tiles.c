#include "tiles.h"

// TODO: refactor
Entity createTile(int size, int block_scale, Vector2 max, Vector2 target, Texture2D texture)
{
  Entity tile;

  tile.texture = texture;
  tile.texture.width *= block_scale;
  tile.texture.height *= block_scale;

  tile.rect.x = (float)tile.texture.width / max.x * target.x;
  tile.rect.y = (float)tile.texture.height / max.y * target.y;
  tile.rect.width = tile.texture.width / max.x;
  tile.rect.height = tile.texture.height / max.y;

  return tile;
}
