#include "entity.h"
#include <raylib.h>

int entityCount = 0;

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

void renderEntityV(Entity entity, Vector2 position)
{
  entity.position = position;
  renderEntity(entity);
}

void renderEntities(Entity *entities, int count)
{
  for (int i = 0; i<count; i++)
  {
    renderEntity(entities[i]);
  }
}
