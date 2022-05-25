#pragma once
#include<math.h>


#define PLAYER_COLLISION_BITMASK  1
#define WALL_COLLISION_BITMASK 2
#define BOMB_COLLISION_BITMASK 3
#define FLAME_COLLISION_BITMASK 4
#define ENEMY_COLLISION_BITMASK 5
#define CONTAINER_COLLISION_BITMASK 6
#define ITEM_COLLISION_BITMASK 7

#define MOVE_NORTH 11
#define MOVE_EAST 12
#define MOVE_SOUTH 13
#define MOVE_WEST 14
#define TILE_SPACE 110
#define PLAYER_MOVE_ACTION 200
#define ENEMY_CHANGEDIRECTION_TAG 201
#define TIME_BOMB_EXPLODE 2.f
#define FLAME_DOUSE  2.f

#define BONUS_BOMB_ITEM 301
#define POWERUP_FLAME_BOMB 302
#define SPEEDUP_ITEM 303
#define KICKBOMB_ITEM 304
#define PORTAL 305
#define BONUS_LIFE_ITEM 306
#define SPEEDUP_EXPLODE_ITEM 307

#define MOVE_VIA_AILOW 351
#define MOVE_VIA_AIMEDIUM 352
#define MOVE_VIA_AIHIGH 353
#define MOVE_VIA_IDLE 354

#define ENEMY_VISION 200.f
#define ANIMATION_DELAY_PER_UNIT 0.15f

struct Cam {
	float posX = 0;
	float posY = 0;
};


int randRange(int min, int max);

int getDirection(float cosA, float sinA);