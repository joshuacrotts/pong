#ifndef BALL_H
#define BALL_H

#include "commons.h"

extern struct level_t *level;

extern struct entity_t *init_ball( void );
extern void update_ball( struct entity_t *b );
extern void draw_ball( struct entity_t *b );
extern void respawn_ball( struct entity_t *b );

#endif // BALL_H
