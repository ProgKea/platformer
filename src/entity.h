#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

typedef struct Entity {
  Vector2 position;
  Texture2D texture;
  Rectangle rect;
  int frames;
} Entity;

void animate(int speed, Rectangle *frameRec, int width);
void renderEntity(Entity entity);

#endif
