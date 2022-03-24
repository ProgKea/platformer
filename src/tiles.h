#ifndef TILES_H
#define TILES_H

#include "entity.h"
#include <raylib.h>

typedef struct Tileset {
  const Texture2D texture;
  const int rows;
  const int columns;
  const int size;
} Tileset;

Entity createTile(Tileset tileset, float block_scale, Vector2 target_block);

#endif
