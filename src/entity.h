#ifndef ENTITY_H
#define ENTITY_H

#define ENTITIES 2

#include <raylib.h>
#include <stdbool.h>

typedef struct Entity {
  Vector2 position;
  Texture2D texture;
  Rectangle rect;

  int frames;
  int animSpeed;

  float moveSpeed;

  bool isFlipped;
  bool drawDebugLines;
} Entity;

void animate(Entity *entity);
void renderEntity(Entity entity);
void renderEntities(Entity entities[]);
void unloadEntities(Entity entities[]);

#endif
