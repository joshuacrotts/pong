#ifndef LEVEL_H
#define LEVEL_H

#include "ai.h"
#include "ball.h"
#include "commons.h"
#include "paddle.h"

#include "../lib/stds/include/collision.h"

extern struct level_t *level;

extern void init_level( void );
extern void update_level( void );
extern void draw_level( void );

#endif // LEVEL_H