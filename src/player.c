#include "player.h"
#include "entity.h"
#include "animation.h"
#include "tiles.h"
#include <raylib.h>

animationTexture Idle;
animationTexture Walk;
animationTexture Jump;

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

  Jump.texture = LoadTexture("data/option_2/herochar sprites(new)/herochar_jump_up_anim_strip_3.png");
  Jump.texture.width *= 3;
  Jump.texture.height *= 3;
  Jump.frames = 3;
  Jump.speed = 15;

  animationTextures[0] = &Idle;
  animationTextures[1] = &Walk;

  player.frames = Idle.frames;

  player.texture = Idle.texture;

  player.position.x = 600.0f;
  player.position.y = 350.0f;

  player.velocity = (Vector2){0.0f, 0.0f};
  player.moveSpeed = 200.0f;

  player.rect.x = 0.0f;
  player.rect.y = 0.0f;
  player.rect.width = (float)player.texture.width / player.frames;
  player.rect.height = (float)player.texture.height;

  player.animSpeed = Idle.speed;

  player.isFlipped = false;
  player.isOnGround = false;
  player.isJumping = false;

  return player;
}

bool checkPlayerCollision(Entity *player, Entity target)
{
  if (player->position.y + player->rect.height >= target.position.y &&
      player->position.y + player->rect.height <= target.position.y + target.rect.height &&
      player->position.x + player->rect.width >= target.position.x &&
      player->position.x <= target.position.x + target.rect.width)
  {
    return true;
  }
  return false;
}

void checkPlayerOnGround(Entity *player, Entity *platforms)
{
  for (int i = 0; i < TILES; i++)
  {
    if (checkPlayerCollision(player, platforms[i]))
    {
      player->isOnGround = true;
      player->velocity.y = 0.0f;
    }
    else
    {
      player->isOnGround = false;
    }
  }
}

void jump(Entity *player, float delta)
{
  if (player->isOnGround)
  {
    player->isJumping = true;
    player->position.y -= player->velocity.y * delta;
    changeAnimation(player, Jump);
  }
}

void playerMovement(Entity *player, float delta)
{
  if (IsKeyDown(KEY_A))
  {
    player->velocity.x = -player->moveSpeed;
    player->isFlipped = true;
    changeAnimation(player, Walk);
  }
  else if (IsKeyDown(KEY_D))
  {
    player->velocity.x = player->moveSpeed;
    player->isFlipped = false;
    changeAnimation(player, Walk);
  }
  else if (IsKeyDown(KEY_SPACE))
  {
    jump(player, delta);
  }
  else
  {
    player->velocity.x = 0.0f;
    changeAnimation(player, Idle);
  }

  if (!player->isOnGround)
  {
    player->velocity.y += GRAVITY;
    player->position.y += player->velocity.y * delta;
  }

  player->position.x += player-> velocity.x * delta;
}
