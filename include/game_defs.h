#ifndef GAME_DEFS_H
#define GAME_DEFS_H

#define S_WIDTH                 1366
#define S_HEIGHT                768
#define L_WIDTH                 S_WIDTH
#define L_HEIGHT                S_HEIGHT
#define FONT_SIZE               128
#define DEFAULT_PADDLE_VELOCITY 8.f

#define PLAYER_ONE_MASK           0x00000010
#define PLAYER_TWO_MASK           0x00000020
#define P1_AI_MASK                0x00000040
#define P2_AI_MASK                0x00000080
#define AI_VELOCITY_RECEDE_MASK   0x00000100
#define AI_VELOCITY_APPROACH_MASK 0x00000200
#define AI_VELOCITY_CLOSE_MASK    0x00000400

#define BALL_SPEED 10

#endif // GAME_DEFS_H