#include "main.h"

int main(){
	printf("ESC exit - c clear - r reset - p pause \n");
	
	graphicsInit();
	gameInit();
	
	while(game.running == 1){
	
		Uint32 begintime = SDL_GetTicks();

		gameUpdate();
		graphicsDraw();

		Uint32 frametime = SDL_GetTicks() - begintime;		
		double delay = (1000.f / framelimit) - frametime;		
		if(delay > 0)
			SDL_Delay(delay);

		//framerate is estimated from loop's excecution time
		gfx.frames = 1000.f / (SDL_GetTicks() - begintime);		
		
	}

	graphicsClose(NULL);
	return 0;
}
