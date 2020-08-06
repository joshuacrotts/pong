#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "commons.h"

struct level_t {
  struct entity_t *player_one;
  struct entity_t *player_two;
  struct entity_t *ball;

  int score_p1;
  int score_p2;

  float difficulty; /* SPEED FACTOR. */
};

#endif // GAME_STRUCTS_H