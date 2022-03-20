#include "entity.h"

int currentFrame = 0;
int framesCounter = 0;

void animate(int speed, Rectangle *frameRec, int width)
{
  framesCounter++;

  if (framesCounter >= (60 / speed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > 5)
      currentFrame = 0;

    frameRec->x = (float)currentFrame * width;
  }
}

void renderEntity(Entity entity)
{
  DrawTextureRec(entity.texture, entity.rect, entity.position, WHITE);
}
  
