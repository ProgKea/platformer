#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "entity.h"

#define PLAYER_SPEED 200
#define GRAVITY 10

Entity createPlayer();
void checkPlayerOnGround(Entity *player, Entity *platforms);
void playerMovement(Entity *player, float delta);

#endif
