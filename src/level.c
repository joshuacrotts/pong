#include "../include/level.h"

#define MIN_X_VELOCITY    5.f
#define MAX_X_VELOCITY    15.f
#define MIN_Y_VELOCITY    5.f
#define MAX_Y_VELOCITY    10.f
#define SCORE_P1_X_OFFSET 264
#define SCORE_P2_X_OFFSET 200
#define SCORE_Y_OFFSET    20
#define MAX_VLINES        15
#define VLINE_WIDTH       5
#define VLINE_HEIGHT      25
#define VLINE_SPACE       g_app.SCREEN_HEIGHT / MAX_VLINES

struct level_t *level;

static void draw_score( void );
static void draw_background( void );
static void draw_vlines( void );

static void handle_collisions( void );
static bool check_paddle_ball_collision( struct entity_t *p, struct entity_t *b );

/**
 *
 */
void
init_level( void ) {
  level = malloc( sizeof( struct level_t ) );

  if ( level == NULL ) {
    fprintf( stderr, "Error, could not allocate memory for level_t struct! %s\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( level, 0, sizeof( struct level_t ) );

  /* Now initialize the components. */
  level->player_one = init_paddle( PLAYER_ONE_MASK );
  level->player_two = init_paddle( P2_AI_MASK );
  level->ball       = init_ball();
}

/**
 *
 */
void
update_level( void ) {
  handle_collisions();
  update_ball( level->ball );

  if ( level->player_one->id_flags & PLAYER_ONE_MASK ) {
    update_paddle( level->player_one );
  } else if ( level->player_one->id_flags & P1_AI_MASK ) {
    update_ai_paddle( level->player_one );
  }

  if ( level->player_two->id_flags & PLAYER_TWO_MASK ) {
    update_paddle( level->player_two );
  } else if ( level->player_two->id_flags & P2_AI_MASK ) {
    update_ai_paddle( level->player_two );
  }
}

/**
 *
 */
void
draw_level( void ) {
  draw_background();
  draw_score();
  draw_ball( level->ball );

  if ( level->player_one->id_flags & PLAYER_ONE_MASK ) {
    draw_paddle( level->player_one );
  } else if ( level->player_one->id_flags & P1_AI_MASK ) {
    draw_ai_paddle( level->player_one );
  }

  if ( level->player_two->id_flags & PLAYER_TWO_MASK ) {
    draw_paddle( level->player_two );
  } else if ( level->player_two->id_flags & P2_AI_MASK ) {
    draw_ai_paddle( level->player_two );
  }
}

/**
 *
 */
static void
draw_score( void ) {
  SDL_Color c = {0xff, 0xff, 0xff, 0xff};
  Stds_DrawText( g_app.SCREEN_WIDTH / 2 - SCORE_P1_X_OFFSET, SCORE_Y_OFFSET, "res/font/bit5x3.ttf",
                 FONT_SIZE, &c, "%d", level->score_p1 );
  Stds_DrawText( g_app.SCREEN_WIDTH / 2 + SCORE_P2_X_OFFSET, SCORE_Y_OFFSET, "res/font/bit5x3.ttf",
                 FONT_SIZE, &c, "%d", level->score_p2 );
}

/**
 *
 */
static void
draw_background( void ) {
  SDL_Rect  r = {0, 0, g_app.SCREEN_WIDTH, g_app.SCREEN_HEIGHT};
  SDL_Color c = {0xff, 0x55, 0, 0xff};
  Stds_DrawRect( &r, &c, true, false );

  draw_vlines();
}

/**
 *
 */
static void
handle_collisions( void ) {
  struct entity_t *p1 = level->player_one;
  struct entity_t *p2 = level->player_two;
  struct entity_t *b  = level->ball;

  bool p1_collide = check_paddle_ball_collision( p1, b );
  bool p2_collide = check_paddle_ball_collision( p2, b );

  /* Handle collisions against the paddles. */
  if ( p1_collide || p2_collide ) {
    /* If they collided with p1, it's on the right side, otherwise
       it's the left. */
    if ( p1_collide ) {
      Stds_PlaySFX( SND_P1_HIT, CH_ANY );
      b->pos.x = p1->pos.x + p1->w;
    } else {
      Stds_PlaySFX( SND_P2_HIT, CH_ANY );
      b->pos.x = p2->pos.x;
      p2->flags &= 0;
    }

    /* The velocity is randomized every time the ball hits the paddle. */
    b->velocity.x =
        Stds_RandomFloat( MIN_X_VELOCITY, MAX_X_VELOCITY ) * -( SIGNUM( b->velocity.x ) );
    b->velocity.y =
        Stds_RandomFloatBounded( -MAX_Y_VELOCITY, -MIN_Y_VELOCITY, MIN_Y_VELOCITY, MAX_Y_VELOCITY );
  }

  /* If the ball goes off the screen on either side, increment the player score. */
  bool is_restart = b->pos.x >= g_app.SCREEN_WIDTH || b->pos.x <= 0;
  if ( b->pos.x >= g_app.SCREEN_WIDTH ) {
    level->score_p1++;
  } else if ( b->pos.x <= 0 ) {
    level->score_p2++;
  }

  if ( is_restart ) {
    respawn_ball( b );
    Stds_PlaySFX( SND_SCORE, CH_ANY );
    p2->flags &= 0;
  }
}

/**
 *
 */
static bool
check_paddle_ball_collision( struct entity_t *p, struct entity_t *b ) {
  return Stds_CheckIntersection( p->pos.x, p->pos.y, p->w, p->h, b->pos.x, b->pos.y, b->w, b->h );
}

/**
 *
 */
static void
draw_vlines( void ) {
  for ( int i = 0, x = 0; i < MAX_VLINES; i++, x += VLINE_SPACE ) {
    SDL_Rect  r = {g_app.SCREEN_WIDTH / 2 - VLINE_WIDTH, x, VLINE_WIDTH, VLINE_HEIGHT};
    SDL_Color c = {0xff, 0xff, 0xff, 0xff};
    Stds_DrawRect( &r, &c, true, false );
  }
}