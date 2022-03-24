#include "player.h"
#include "entity.h"
#include "animation.h"
#include <raylib.h>

animationTexture Idle;
animationTexture Walk;

Entity createPlayer()
{
  Entity player;

  Idle.texture = LoadTexture("data/option_2/herochar sprites(new)/herochar_idle_anim_strip_4.png");
  Idle.texture.width *= 3;
  Idle.texture.height *= 3;
  Idle.frames = 4;
  Idle.speed = 4;

  Walk.texture = LoadTexture("data/option_2/herochar sprites(new)/herochar_run_anim_strip_6.png");
  Walk.texture.width *= 3;
  Walk.texture.height *= 3;
  Walk.frames = 6;
  Walk.speed = 15;

  animationTextures[0] = &Idle;
  animationTextures[1] = &Walk;

  player.frames = Idle.frames;

  player.texture = Idle.texture;

  player.position.x = 600.0f;
  player.position.y = 350.0f;

  player.rect.x = 0.0f;
  player.rect.y = 0.0f;
  player.rect.width = (float)player.texture.width / player.frames;
  player.rect.height = (float)player.texture.height;

  player.animSpeed = Idle.speed;
  player.moveSpeed = 250.0f;

  player.isFlipped = false;

  return player;
}

void playerMovement(Entity *player, float delta)
{
  if (IsKeyDown(KEY_A))
    {
      player->position.x-=player->moveSpeed*delta;
      player->isFlipped = true;
      changeAnimation(player, Walk);
    }
  else if (IsKeyDown(KEY_D))
    {
      player->position.x += player->moveSpeed * delta;
      player->isFlipped = false;
      changeAnimation(player, Walk);
    }
  else
    {
      changeAnimation(player, Idle);
    }
}
