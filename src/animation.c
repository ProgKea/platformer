#include "animation.h"

animationTexture *animationTextures[ANIMATIONS];

void changeAnimation(Entity *src, animationTexture dst)
{
  src->frames = dst.frames;
  src->texture = dst.texture;
  src->animSpeed = dst.speed;
}

void unloadAnimationTextures(animationTexture p_animationTextures[])
{
  for (int i = 0; i<(int)sizeof(animationTextures)/sizeof(*animationTextures[0]); i++)
  {
    UnloadTexture(animationTextures[i]->texture);
  }
}

int currentFrame = 0;
int framesCounter = 0;
void animate(Entity *entity)
{
  framesCounter++;

  if (framesCounter >= (60 / entity->animSpeed))
  {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > 5)
    {
      currentFrame = 0;
    }

    entity->rect.x = (float)currentFrame * entity->texture.width / entity->frames;
  }
}
