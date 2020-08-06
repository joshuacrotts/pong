#include "../include/paddle.h"

#define PADDLE_WIDTH  20
#define PADDLE_HEIGHT 80
#define DAMP_VELOCITY 0.95f

static void key_input_listener( struct entity_t *p );
static void check_edge_collision( struct entity_t *p );

/**
 *
 */
struct entity_t *
init_paddle( int ID_MASK ) {
  struct entity_t *paddle;
  paddle = malloc( sizeof( struct entity_t ) );
  if ( paddle == NULL ) {

    exit( EXIT_FAILURE );
  }

  paddle->w = PADDLE_WIDTH;
  paddle->h = PADDLE_HEIGHT;
  paddle->id_flags |= ID_MASK;

  /* We can use two AI masks to simulate AI vs AI... >:} */
  switch ( ID_MASK ) {
  case PLAYER_ONE_MASK:
  case P1_AI_MASK:
    paddle->pos = Stds_CreateVec2( PADDLE_WIDTH, g_app.SCREEN_HEIGHT / 2 - paddle->h );
    break;
  case PLAYER_TWO_MASK:
  case P2_AI_MASK:
    paddle->pos = Stds_CreateVec2( g_app.SCREEN_WIDTH - PADDLE_WIDTH * 2,
                                   g_app.SCREEN_HEIGHT / 2 - paddle->h );
    break;
  }

  SDL_Color c   = { 0xff, 0xff, 0xff, 0xff };
  paddle->color = c;

  return paddle;
}

/**
 *
 */
void
update_paddle( struct entity_t *p ) {
  key_input_listener( p );
  check_edge_collision( p );

  Stds_AddVec2( &p->pos, &p->velocity );
  Stds_MultiplyToVec2( &p->velocity, DAMP_VELOCITY );
}

/**
 *
 */
void
draw_paddle( struct entity_t *p ) {
  SDL_FRect fr = { p->pos.x, p->pos.y, p->w, p->h };
  Stds_DrawRectF( &fr, &p->color, true, false );
}

/**
 *
 */
static void
key_input_listener( struct entity_t *p ) {
  if ( p->id_flags & PLAYER_ONE_MASK ) {
    if ( g_app.keyboard[SDL_SCANCODE_W] ) {
      p->velocity = Stds_CreateVec2( 0, -DEFAULT_PADDLE_VELOCITY );
    } else if ( g_app.keyboard[SDL_SCANCODE_S] ) {
      p->velocity = Stds_CreateVec2( 0, DEFAULT_PADDLE_VELOCITY );
    }
  } else if ( p->id_flags & PLAYER_TWO_MASK ) {
    if ( g_app.keyboard[SDL_SCANCODE_UP] ) {
      p->velocity = Stds_CreateVec2( 0, -DEFAULT_PADDLE_VELOCITY );
    } else if ( g_app.keyboard[SDL_SCANCODE_DOWN] ) {
      p->velocity = Stds_CreateVec2( 0, DEFAULT_PADDLE_VELOCITY );
    }
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