#ifndef PADDLE_H
#define PADDLE_H

#include "commons.h"

extern struct level_t *level;

extern struct entity_t *init_paddle( int mask );
extern void update_paddle( struct entity_t *p );
extern void draw_paddle( struct entity_t *p );

#endif // PADDLE_H
