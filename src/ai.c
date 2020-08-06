#include "../include/ai.h"

/**
 *
 */
void
update_ai_paddle( struct entity_t *ai_paddle ) {
  /* This threshold calculates the point that the AI
     travels to, to find the optimal spot to hit the ball. */
  float threshold = level->ball->pos.y - ai_paddle->h / 2;

  if ( ai_paddle->pos.y < threshold ) {
    ai_paddle->velocity = Stds_CreateVec2( 0, PADDLE_VELOCITY );
  } else if ( ai_paddle->pos.y > threshold ) {
    ai_paddle->velocity = Stds_CreateVec2( 0, -PADDLE_VELOCITY );
  } else {
    Stds_MultiplyToVec2( &ai_paddle->velocity, 0.f );
  }

  Stds_AddVec2( &ai_paddle->pos, &ai_paddle->velocity );
}

/**
 *
 */
void
draw_ai_paddle( struct entity_t *ai_paddle ) {
  SDL_FRect fr = { ai_paddle->pos.x, ai_paddle->pos.y, ai_paddle->w, ai_paddle->h };
  Stds_DrawRectF( &fr, &ai_paddle->color, true, false );
}