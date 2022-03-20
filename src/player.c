#include "player.h"
#include "entity.h"
#include <raylib.h>


Entity createPlayer()
{
  Entity player;
  player.frames = 4;

  player.texture = LoadTexture("data/option_1/2/Idle.png");

  player.position.x = 600.0f;
  player.position.y = 350.0f;

  player.rect.x = 0.0f;
  player.rect.y = 0.0f;
  player.rect.width = (float)player.texture.width / player.frames;
  player.rect.height = (float)player.texture.height;

  return player;
}

void changeAnimation(Entity *src, int newFrames, Texture2D newTexture)
{
  src->frames = newFrames;
  /* UnloadTexture(src->texture); */
  src->texture = newTexture;
}

void playerMovement(Entity *player, float speed, float delta)
{
  Texture2D walking = LoadTexture("data/option_1/2/Walk.png");
  if (IsKeyDown(KEY_A)) {
    player->position.x-=speed*delta;
    changeAnimation(player, 6, walking);
  }
  if (IsKeyDown(KEY_D))
    player->position.x+=speed*delta;
}
