#include "player.h"
#include "entity.h"
#include "animation.h"
#include "tiles.h"
#include <stdio.h>
#include <raylib.h>

animationTexture Idle;
animationTexture Walk;
animationTexture Jump;
animationTexture Fall;

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

  Fall.texture = LoadTexture("data/option_2/herochar sprites(new)/herochar_jump_down_anim_strip_3.png");
  Fall.texture.width *= 3;
  Fall.texture.height *= 3;
  Fall.frames = 3;
  Fall.speed = 15;

  animationTextures[0] = &Idle;
  animationTextures[1] = &Walk;
  animationTextures[2] = &Jump;
  animationTextures[3] = &Fall;

  player.frames = Idle.frames;

  player.texture = Idle.texture;

  player.position.x = 600.0f;
  player.position.y = 350.0f;

  player.velocity = (Vector2){0.0f, 0.0f};
  player.moveSpeed = 200.0f;
  player.jumpSpeed = -400.0f;
  player.gravity = 16.0f;

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

void applyGravity(Entity *player, float delta)
{
  if (!player->isOnGround)
  {
    player->velocity.y += player->gravity;
  }
}

void horizontalMovementCollision(Entity *player, float delta, Entity *tiles[])
{
  player->position.x += player->velocity.x * delta;
  for (int i = 0; i<TILES; i++)
  {
    if (CheckCollisionRecs((Rectangle){player->position.x, player->position.y, player->rect.width, player->rect.height},
          (Rectangle){tiles[i]->position.x, tiles[i]->position.y, tiles[i]->rect.width, tiles[i]->rect.height}))
    {
      if (player->velocity.x > 0)
      {
        player->position.x = tiles[i]->position.x - player->rect.width;
      }
      else if (player->velocity.x < 0)
      {
        player->position.x = tiles[i]->position.x + tiles[i]->rect.width;
      }
      player->velocity.x = 0;
    }
  }
}

void verticalMovementCollision(Entity *player, float delta, Entity *tiles[])
{
  applyGravity(player, delta);
  player->position.y += player->velocity.y * delta;
  for (int i = 0; i<TILES; i++)
  {
    if (CheckCollisionRecs((Rectangle){player->position.x, player->position.y, player->rect.width, player->rect.height},
          (Rectangle){tiles[i]->position.x, tiles[i]->position.y, tiles[i]->rect.width, tiles[i]->rect.height}))
    {
      if (player->velocity.y > 0)
      {
        player->position.y = tiles[i]->position.y - player->rect.height;
        player->velocity.y = 0;
      }
      else if (player->velocity.y < 0)
      {
        player->position.y = tiles[i]->position.y + tiles[i]->rect.height;
        player->velocity.y = 0;
      }
    }
  }
  if (player->velocity.y > 0)
  {
    changeAnimation(player, Fall);
  }
  else if (player->velocity.y < 0)
  {
    changeAnimation(player, Jump);
  }
}

void jump(Entity *player)
{
  player->isJumping = true;
  player->velocity.y = player->jumpSpeed;
}

void playerMovement(Entity *player, float delta, Entity *tiles[])
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
  else
  {
    player->velocity.x = 0.0f;
    changeAnimation(player, Idle);
  }
  if (IsKeyPressed(KEY_SPACE))
  {
    jump(player);
  }
  horizontalMovementCollision(player, delta, tiles);
  verticalMovementCollision(player, delta, tiles);
}
