#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "entity.h"

Entity createPlayer();
void playerMovement(Entity *player, float delta, Entity tiles[]);

#endif
