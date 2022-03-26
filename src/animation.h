#ifndef ANIMATION_H
#define ANIMATION_H
#define ANIMATIONS 4

#include "entity.h"

typedef struct animationTexture {
  Texture2D texture;
  int frames;
  int speed;
} animationTexture;

extern animationTexture *animationTextures[ANIMATIONS];

void changeAnimation(Entity *src, animationTexture dst);
void unloadAnimationTextures(animationTexture animationTextures[]);
void animate(Entity *entity);

#endif
