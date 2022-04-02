#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

extern int entityCount;

typedef struct Entity {
  Vector2 position;
  Texture2D texture;
  Rectangle rect;
  Camera2D camera;

  int frames;
  int animSpeed;

  Vector2 velocity;
  float moveSpeed;
  float gravity;
  float jumpSpeed;

  bool isFlipped;
  bool allowedToJump;
  bool allowedToDoubleJump;
  bool drawDebugLines;
} Entity;

void animate(Entity *entity);
void renderEntity(Entity entity);
void renderEntities(Entity *entities, int count);
void unloadEntities(Entity *entities, int count);

#endif
