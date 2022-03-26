#ifndef TILES_H
#define TILES_H
#define TILES 1

#include "entity.h"
#include <raylib.h>

typedef struct Tileset {
  Texture2D texture;
  int rows;
  int columns;
  int size;
} Tileset;

Entity createTile(Tileset tileset, float block_scale, Vector2 target_block);

#endif
