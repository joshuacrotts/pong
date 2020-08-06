#include "../include/ai.h"

#define MIN_RECEDE_VEL   0.5f
#define MAX_RECEDE_VEL   0.75f
#define MIN_APPROACH_VEL 0.75f
#define MAX_APPROACH_VEL 0.875f

static void update_ai_velocities( struct entity_t *ai_paddle );
static void compute_threshold( struct entity_t *ai_paddle );
static void check_edge_collision( struct entity_t *p );

/**
 *
 */
void
update_ai_paddle( struct entity_t *ai_paddle ) {
  update_ai_velocities( ai_paddle );

  /* Position the paddle where it should be (following the y coordinate of the ball). */
  compute_threshold( ai_paddle );
  check_edge_collision( ai_paddle );
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

/**
 *
 */
static void
update_ai_velocities( struct entity_t *ai_paddle ) {
  bool is_receding_ball = SIGNUM( level->ball->velocity.x ) == -1;

  /* If the ball is going away from the ai_paddle, we can move twice as slow. */
  if ( is_receding_ball && ( ( ai_paddle->flags & AI_VELOCITY_RECEDE_MASK ) == 0 ) ) {
    ai_paddle->velocity.y =
        DEFAULT_PADDLE_VELOCITY * Stds_RandomFloat( MIN_RECEDE_VEL, MAX_APPROACH_VEL );
    ai_paddle->flags |= AI_VELOCITY_RECEDE_MASK;
  } else if ( !is_receding_ball ) {
    /* If the ball is heading towards the paddle and it is not close, move around
       1/4 as slow. */
    if ( ( level->ball->pos.x <= g_app.SCREEN_WIDTH / 2 ) &&
         ( ( ai_paddle->flags & AI_VELOCITY_APPROACH_MASK ) == 0 ) ) {
      ai_paddle->velocity.y =
          DEFAULT_PADDLE_VELOCITY * Stds_RandomFloat( MIN_APPROACH_VEL, MAX_APPROACH_VEL );
      ai_paddle->flags |= AI_VELOCITY_APPROACH_MASK;
    }
    /* If the ball is "close", make it travel at normal speed. */
    else if ( ( level->ball->pos.x > g_app.SCREEN_WIDTH / 2 ) &&
              ( ( ai_paddle->flags & AI_VELOCITY_CLOSE_MASK ) == 0 ) ) {
      ai_paddle->velocity.y = DEFAULT_PADDLE_VELOCITY;
      ai_paddle->flags |= AI_VELOCITY_CLOSE_MASK;
    }
  }
}

/**
 *
 */
static void
compute_threshold( struct entity_t *ai_paddle ) {
  /* This threshold calculates the point that the AI
     travels to, to find the optimal spot to hit the ball. */
  float threshold = level->ball->pos.y - ai_paddle->h / 2;
  if ( ai_paddle->pos.y > threshold && SIGNUM( ai_paddle->velocity.y ) > 0 ) {
    ai_paddle->velocity.y *= -1;
  } else if ( ai_paddle->pos.y < threshold && SIGNUM( ai_paddle->velocity.y ) < 0 ) {
    ai_paddle->velocity.y *= -1;
  } else if ( ai_paddle->pos.y == threshold ) {
    Stds_MultiplyToVec2( &ai_paddle->velocity, 0.f );
  }
}

/**
 *
 */
static void
check_edge_collision( struct entity_t *p ) {
  if ( p->pos.y <= 0 ) {
    p->pos.y = 0;
  }

  if ( p->pos.y > g_app.LEVEL_HEIGHT - p->h ) {
    p->pos.y = g_app.LEVEL_HEIGHT - p->h;
  }
}