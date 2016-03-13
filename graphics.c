#include "main.h"

void graphicsClose(const char * message);

void Text(const char * message, int x, int y);
void Box(int x, int y, int w, int h, int angle, int r, int g, int b, int a);
void updateFPS();
void drawUnits();
SDL_Texture * loadTexture(const char * path);


void graphicsDraw(){
	SDL_SetRenderDrawColor(gfx.renderer, 0, 0, 0, 255);
	SDL_RenderClear(gfx.renderer);

	if(show_fps == 1)
		updateFPS();
	drawUnits();

	SDL_RenderPresent(gfx.renderer);
}

void drawUnits(){
	int i;
	for(i = 0; i < unitlimit; i++){
		if (game.units[i].alive == 1){
			SDL_Rect rect = {game.units[i].x, game.units[i].y, game.units[i].size, game.units[i].size};
			if(game.units[i].team == 0)
				SDL_RenderCopyEx(gfx.renderer, gfx.unit_red, NULL, &rect, game.units[i].angle, NULL, SDL_FLIP_NONE);
			if(game.units[i].team == 1)
				SDL_RenderCopyEx(gfx.renderer, gfx.unit_blue, NULL, &rect, game.units[i].angle, NULL, SDL_FLIP_NONE);
			
		}
	}

}

//Init SDL, create window, renderer, font, load font, unit texture
void graphicsInit(){
	gfx.window = NULL;
	gfx.renderer = NULL;
	gfx.font = NULL;
	gfx.unit_red = NULL;
	gfx.unit_blue = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		graphicsClose("SDL_Init failed");
	if(TTF_Init() != 0)
		graphicsClose("TTF_Init failed");	

    	gfx.window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, 0);
   	gfx.renderer = SDL_CreateRenderer(gfx.window, -1, SDL_RENDERER_ACCELERATED);

	if(gfx.window == NULL)
		graphicsClose("windows creation failed");
	if(gfx.renderer == NULL)
		graphicsClose("renderer creation failed");
	
	gfx.font = TTF_OpenFont("media/font.ttf", 28);
	
	if(gfx.font == NULL)
		graphicsClose("Font not loaded");	

	gfx.unit_red = loadTexture("media/red.png");
	gfx.unit_blue = loadTexture("media/blue.png");

}

SDL_Texture * loadTexture(const char * path){
	SDL_Surface * surface = IMG_Load(path);
	if(surface == NULL)
		graphicsClose("surface not loaded");

	SDL_Texture * texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);
	if(texture == NULL)
		graphicsClose("texture not created");
	SDL_FreeSurface(surface);
	return texture;
}

void updateFPS(){
	char buf[100] = {0};
	sprintf(buf, "%i", gfx.frames);
	Text(buf, 0, 0);

}

void Text(const char * message, int x, int y){
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface * text = TTF_RenderText_Blended(gfx.font, message, color);
	if(message == NULL)
		graphicsClose("text not rendered");

	SDL_Texture * texture = SDL_CreateTextureFromSurface(gfx.renderer, text);
	if(texture == NULL)
		graphicsClose("text texture not created");
	
	SDL_Rect rect = {x, y, 0, 0};
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);	
	SDL_RenderCopy(gfx.renderer, texture, NULL, &rect);	
	
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text);

}

void Box(int x, int y, int w, int h, int angle, int r, int g, int b, int a){
	SDL_Rect rect = {x, y, w, h};
	SDL_Texture * texture = SDL_CreateTexture(gfx.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	SDL_SetRenderTarget(gfx.renderer, texture);
	SDL_SetRenderDrawColor(gfx.renderer, r, g, b, a);
	SDL_RenderClear(gfx.renderer);
	SDL_SetRenderTarget(gfx.renderer, NULL);
	SDL_RenderCopyEx(gfx.renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
	SDL_DestroyTexture(texture);

}

//clean up SDL
void graphicsClose(const char * message){
	if(message != NULL)
		printf("%s\n", message);
	//check if window and renderer exist, destroy them
	if(gfx.window != NULL)
		SDL_DestroyWindow(gfx.window);
	if(gfx.renderer != NULL)
		SDL_DestroyRenderer(gfx.renderer);
	if(gfx.font != NULL)
		TTF_CloseFont(gfx.font);
	if(gfx.unit_red != NULL)
		SDL_DestroyTexture(gfx.unit_red);
	if(gfx.unit_blue != NULL)
		SDL_DestroyTexture(gfx.unit_blue);
	TTF_Quit();
	SDL_Quit();
	exit(1);
}
