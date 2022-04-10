#include "player.h"
#include "entity.h"
#include "animation.h"
#include "tiles.h"

animationTexture Idle;
animationTexture Walk;
animationTexture Jump;
animationTexture doubleJump;
animationTexture Fall;

Entity createPlayer()
{
  Entity player;

  Idle.texture = LoadTexture("data/sprites/herochar sprites(new)/herochar_idle_anim_strip_4.png");
  Idle.texture.width *= 3;
  Idle.texture.height *= 3;
  Idle.frames = 4;
  Idle.speed = 4;

  Walk.texture = LoadTexture("data/sprites/herochar sprites(new)/herochar_run_anim_strip_6.png");
  Walk.texture.width *= 3;
  Walk.texture.height *= 3;
  Walk.frames = 6;
  Walk.speed = 15;

  Jump.texture = LoadTexture("data/sprites/herochar sprites(new)/herochar_jump_up_anim_strip_3.png");
  Jump.texture.width *= 3;
  Jump.texture.height *= 3;
  Jump.frames = 3;
  Jump.speed = 15;

  doubleJump.texture = LoadTexture("data/sprites/herochar sprites(new)/herochar_jump_double_anim_strip_3.png");
  doubleJump.texture.width *= 3;
  doubleJump.texture.height *= 3;
  doubleJump.frames = 3;
  doubleJump.speed = 15;

  Fall.texture = LoadTexture("data/sprites/herochar sprites(new)/herochar_jump_down_anim_strip_3.png");
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
  player.position.y = 600.0f;

  player.velocity = (Vector2){0.0f, 0.0f};
  player.moveSpeed = 350.0f;
  player.jumpSpeed = -400.0f;
  player.gravity = 16.0f;

  player.rect.x = 0.0f;
  player.rect.y = 0.0f;
  player.rect.width = (float)player.texture.width / player.frames;
  player.rect.height = (float)player.texture.height;

  player.camera = (Camera2D){ 0 };
  player.camera.target = (Vector2){player.position.x, player.position.y};
  player.camera.offset = (Vector2){1200.0f/2, 620.0f/2};
  player.camera.rotation = 0.0f;
  player.camera.zoom = 1.0f;

  player.animSpeed = Idle.speed;

  player.isFlipped = false;
  player.drawDebugLines = false;
  player.noclip = false;
  player.noclipSpeed = 1000.0f;

  entityCount++;

  return player;
}

void applyGravity(Entity *player, float delta)
{
  player->velocity.y += player->gravity;
}

void horizontalMovementCollision(Entity *player, float delta, Entity tiles[])
{
  player->position.x += player->velocity.x * delta;
  for (int i = 0; i<tileCount; i++)
  {
    if (CheckCollisionRecs((Rectangle){player->position.x, player->position.y, player->rect.width, player->rect.height},
          (Rectangle){tiles[i].position.x, tiles[i].position.y, tiles[i].rect.width, tiles[i].rect.height}))
    {
      if (player->velocity.x > 0)
      {
        player->position.x = tiles[i].position.x - player->rect.width;
      }
      else if (player->velocity.x < 0)
      {
        player->position.x = tiles[i].position.x + tiles[i].rect.width;
      }
      player->velocity.x = 0;
      if (player->velocity.y > 0)
      {
        player->velocity.y /= 1.25;
      }
      player->allowedToJump = true;
    }
  }
}

void verticalMovementCollision(Entity *player, float delta, Entity tiles[])
{
  applyGravity(player, delta);
  player->position.y += player->velocity.y * delta;
  for (int i = 0; i<tileCount; i++)
  {
    if (CheckCollisionRecs((Rectangle){player->position.x, player->position.y, player->rect.width, player->rect.height},
          (Rectangle){tiles[i].position.x, tiles[i].position.y, tiles[i].rect.width, tiles[i].rect.height}) && &tiles[i] != NULL)
    {
      if (player->velocity.y > 0)
      {
        player->allowedToJump = true;
        player->position.y = tiles[i].position.y - player->rect.height;
        player->velocity.y = 0;
      }
      else if (player->velocity.y < 0)
      {
        player->position.y = tiles[i].position.y + tiles[i].rect.height;
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
    if (player->allowedToDoubleJump)
    {
      changeAnimation(player, Jump);
    }
    else
    {
      changeAnimation(player, doubleJump);
    }
  }
}

void jump(Entity *player)
{
  player->allowedToJump = false;
  player->velocity.y = player->jumpSpeed;
}

void playerMovement(Entity *player, float delta, Entity tiles[])
{
  if (!player->noclip)
  {
    if (IsKeyDown(KEY_D))
    {
      player->velocity.x = player->moveSpeed;
      player->isFlipped = false;
      changeAnimation(player, Walk);
    }
    else if (IsKeyDown(KEY_A))
    {
      player->velocity.x = -player->moveSpeed;
      player->isFlipped = true;
      changeAnimation(player, Walk);
    }
    else
    {
      player->velocity.x = 0.0f;
      changeAnimation(player, Idle);
    }
    if (IsKeyPressed(KEY_SPACE) && (player->allowedToJump || player->allowedToDoubleJump))
    {
      if (player->allowedToJump)
      {
        jump(player);
        player->allowedToJump = false;
        player->allowedToDoubleJump = true;
      }
      else if (player->allowedToDoubleJump)
      {
        jump(player);
        player->allowedToDoubleJump = false;
      }
    }
    player->camera.target = (Vector2){player->position.x, player->position.y};
    horizontalMovementCollision(player, delta, tiles);
    verticalMovementCollision(player, delta, tiles);
  }
  else 
  {
    if (IsKeyDown(KEY_A))
    {
      player->position.x -= player->noclipSpeed * delta;
    }
    if (IsKeyDown(KEY_D))
    {
      player->position.x += player->noclipSpeed * delta;
    }
    if (IsKeyDown(KEY_W))
    {
      player->position.y -= player->noclipSpeed * delta;
    }
    if (IsKeyDown(KEY_S))
    {
      player->position.y += player->noclipSpeed * delta;
    }
    player->camera.target = (Vector2){player->position.x, player->position.y};
  }
}

