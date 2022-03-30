#include "entity.h"
#include <raylib.h>

void renderDebugLines(Entity entity, Color color)
{
  if (entity.isFlipped)
  {
    DrawRectangleLines(entity.position.x, entity.position.y, entity.rect.width*-1, entity.rect.height, color);
  }
  else
  {
    DrawRectangleLines(entity.position.x, entity.position.y, entity.rect.width, entity.rect.height, color);
  }
}

void renderEntity(Entity entity)
{
  if (entity.isFlipped)
  {
    entity.rect.width *= -1;
  }
  if (entity.drawDebugLines)
  {
    renderDebugLines(entity, GREEN);
  }
  DrawTextureRec(entity.texture, entity.rect, entity.position, WHITE);
}

void unloadEntities(Entity entities[])
{
  for (int i = 0; i<(int)sizeof(*entities)/sizeof(entities[0]); i++)
  {
    UnloadTexture(entities[i].texture);
  }
}
