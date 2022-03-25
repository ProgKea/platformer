#ifndef ENTITY_H
#define ENTITY_H

#define ENTITIES 3

#include <raylib.h>
#include <stdbool.h>

typedef struct Entity {
  Vector2 position;
  Texture2D texture;
  Rectangle rect;

  int frames;
  int animSpeed;

  Vector2 velocity;
  float moveSpeed;

  bool isFlipped;
  bool isOnGround;
  bool isJumping;
  bool drawDebugLines;
} Entity;

void animate(Entity *entity);
void renderEntity(Entity entity);
void renderEntities(Entity entities[]);
void unloadEntities(Entity entities[]);

#endif
