#include "main.h"

void createCenturia();
void wrapValues();

void createCenturia(int x, int y, int angle, int team, int size){
	if(game.nextfree >= 40){
		printf("can't create more units\n");
		return;
	}
	game.units[game.nextfree].x = x;
	game.units[game.nextfree].y = y;
	game.units[game.nextfree].angle = angle;
	game.units[game.nextfree].size = size;
	game.units[game.nextfree].team = team;
	game.units[game.nextfree].alive = 1;
	game.nextfree++;

}

void gameUpdate(){
	gameEvents();
	if(game.pause == 1)		
		return;
	wrapValues();

	cTurn(&game.units[0], 3.0);
	cMove(&game.units[0]);
	cPoint(&game.units[1], &game.units[0]);
	cPoint(&game.units[2], &game.units[0]);
	cPoint(&game.units[3], &game.units[0]);
	
}

void gameInit(){
	gameClear();

	createCenturia(150, 300, 45, 0, 80);
	createCenturia(400, 100, 210, 1, 80);
	createCenturia(300, 300, 45, 0, 80);
	createCenturia(0, 100, 210, 1, 80);
}

void gameClear(){
	game.running = 1;
	game.pause = -1;
	//next free slot in units[]
	game.nextfree = 0;
	int i;
	for(i = 0; i < unitlimit; i++){
		game.units[i].alive = 0;
	}
}

void wrapValues(){
	int i;
	for(i = 0; i < unitlimit; i++){
		if(game.units[i].angle > 360)
			game.units[i].angle -= 360;
		if(game.units[i].angle < 0)
			game.units[i].angle += 360;

		if(game.units[i].x < 0)
			game.units[i].x = 0;
		if(game.units[i].y < 0)
			game.units[i].y = 0;
		if(game.units[i].x > window_width - game.units[i].size)
			game.units[i].x = window_width - game.units[i].size;
		if(game.units[i].y > window_height - game.units[i].size)
			game.units[i].y = window_height - game.units[i].size;
	}
}

void gameEvents(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT)
			game.running = 0;
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_ESCAPE)
				game.running = 0;
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_p)
				game.pause *= -1;
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_c)
				gameClear();
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_r)
				gameInit();
		}
	}
	
}
