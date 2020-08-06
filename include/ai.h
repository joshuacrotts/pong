#ifndef AI_H
#define AI_H

#include "commons.h"

extern struct level_t *level;

extern void update_ai_paddle( struct entity_t *p );
extern void draw_ai_paddle( struct entity_t *p );

#endif // AI_H