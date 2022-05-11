#include<math.h>


#define PLAYER_COLLISION_BITMASK  1
#define WALL_COLLISION_BITMASK 2
#define BOMB_COLLISION_BITMASK 3
#define MOVE_NORTH 11
#define MOVE_EAST 12
#define MOVE_SOUTH 13
#define MOVE_WEST 14
#define TILE_SPACE 110
#define PLAYER_MOVE_ACTION 200
#define ENEMY_CHANGEDIRECTION_TAG 201
#define TIME_BOMB_EXPLODE 2.f

int getDirection(float cosA, float sinA);