#ifndef TILES_H
#define TILES_H

#define TILES 1

#include "entity.h"
#include <raylib.h>

typedef struct Tileset {
  Texture2D texture;
  int rows;
  int columns;
} Tileset;

Entity createTile(Tileset tileset, int blockScale, Vector2 target_block);
void drawDebugGrid(int width, int height);

#endif
