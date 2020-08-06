#include "../include/main.h"


static void init_scene( void );
static void cleanup_stage( void );
static void load_fonts( void );

static void update( void );
static void draw( void );

/**
 *
 */
int
main( int argc, char *argv[] ) {
  atexit( cleanup_stage );
  Stds_InitGame( "SDL Pong", S_WIDTH, S_HEIGHT, L_WIDTH, L_HEIGHT );
  Stds_InitAppStructures();
  init_scene();
  Stds_GameLoop();

  return 0;
}

static void
init_scene( void ) {
  g_app.delegate.update = update;
  g_app.delegate.draw   = draw;

  init_level();
  load_fonts();
}

/**
 *
 */
static void
update( void ) {
  update_level();
}

/**
 *
 */
static void
draw( void ) {
  draw_level();
}

/**
 *
 */
static void
load_fonts( void ) {
  Stds_AddFont( "res/font/bit5x3.ttf", FONT_SIZE );
}

/**
 *
 */
static void
cleanup_stage( void ) {
  free( level->player_one );
  free( level->player_two );
  free( level->ball );
  free( level );
  Stds_Quit();
}