#ifndef TILES_H
#define TILES_H

#include "entity.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

extern int tileCount;
extern int tileLimit;
extern int blockIndex;
extern int blockSize;

extern bool save;

typedef struct Tileset {
  Texture2D texture;
  int rows;
  int columns;
} Tileset;

void createTile(Tileset tileset, Entity *blockArray, float blockScale, Vector2 target_block, Vector2 position);
void placeBlock(Entity *tileArray, Entity tile, Vector2 targetPosition);
void removeBlock(Entity *tileArray, Vector2 targetPosition);
void resetTiles(Entity *tileArray);
void drawDebugGrid(int width, int height);
void tileControls(Entity *tileArray, Entity *blockArray, int blockArraySize, Vector2 position);
void serializeTiles(Entity *tileArray, char *fileName);
Entity *deserializeTiles(char *fileName);

#endif
