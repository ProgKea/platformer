#ifndef TILES_H
#define TILES_H

#include "entity.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

extern int tileCount;
extern int tileLimit;

typedef struct Tileset {
  Texture2D texture;
  int rows;
  int columns;
} Tileset;

Entity createTile(Tileset tileset, int blockScale, Vector2 target_block, Vector2 position);
void placeBlock(Entity *tileArray, Entity tile, Vector2 targetPosition);
void removeBlock(Entity *tileArray, Vector2 targetPosition);
void drawDebugGrid(int width, int height);

#endif
