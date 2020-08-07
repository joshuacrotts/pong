#include "../include/ball.h"

#define BALL_SIZE    10
#define MAX_VELOCITY 5.f
#define MIN_VELOCITY 3.f

static void check_ball_collision( struct entity_t *b );

/**
 *
 */
struct entity_t *
init_ball( void ) {
  struct entity_t *ball;
  ball = malloc( sizeof( struct entity_t ) );

  if ( ball == NULL ) {
    fprintf( stderr, "Error, could not allocate memory for ball entity_t struct.\n" );
    exit( EXIT_FAILURE );
  }

  memset( ball, 0, sizeof( struct entity_t ) );

  respawn_ball( ball );
  ball->w = BALL_SIZE;
  ball->h = ball->w;

  SDL_Color c = { 0xff, 0xff, 0xff, 0xff };
  ball->color = c;
  return ball;
}

/**
 *
 */
void
update_ball( struct entity_t *b ) {
  check_ball_collision( b );
  Stds_AddVec2( &b->pos, &b->velocity );
}

/**
 *
 */
void
draw_ball( struct entity_t *b ) {
  SDL_FRect fr = { b->pos.x, b->pos.y, b->w, b->h };
  Stds_DrawRectF( &fr, &b->color, true, false );
}

/**
 *
 */
void
respawn_ball( struct entity_t *b ) {
  b->pos      = Stds_CreateVec2( g_app.SCREEN_WIDTH / 2, g_app.SCREEN_HEIGHT / 2 );
  b->velocity = Stds_CreateVec2(
      Stds_RandomFloatBounded( -MAX_VELOCITY, -MIN_VELOCITY, MIN_VELOCITY, MAX_VELOCITY ),
      Stds_RandomFloatBounded( -MAX_VELOCITY, -MIN_VELOCITY, MIN_VELOCITY, MAX_VELOCITY ) );
}

/**
 *
 */
static void
check_ball_collision( struct entity_t *b ) {
  if ( b->pos.y <= 0 || b->pos.y > g_app.LEVEL_HEIGHT - b->h ) {
    b->velocity.y = -b->velocity.y;
  }
}