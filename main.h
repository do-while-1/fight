#ifndef _game_
#define _game_

#include "stdio.h"
#include "/usr/include/SDL2/SDL.h"
#include "/usr/include/SDL2/SDL_ttf.h"
#include "/usr/include/SDL2/SDL_image.h"

#define PI 3.14159265
#define unitlimit 40
#define unitspeed 4
#define framelimit 9999

#define window_width 800
#define window_height 600
#define show_fps 1

struct centuria{
	double x, y;
	int size, team, alive;
	double angle;
};

struct graphics{
	SDL_Window * window;
	SDL_Renderer * renderer;
	TTF_Font * font;
	int frames;
	SDL_Texture * unit_red;
	SDL_Texture * unit_blue;
}gfx;

struct game{
	int running;
	int pause;
	struct centuria units[unitlimit];
	int nextfree;

}game;

void cMove();
void cTranslate();
void cSetPosition();
void cPoint();
void cTurn();
void cSetAngle();

void gameInit();
void gameClear();
void gameUpdate();
void gameEvents();

void graphicsInit();
void graphicsDraw();
void graphicsClose();

#endif
