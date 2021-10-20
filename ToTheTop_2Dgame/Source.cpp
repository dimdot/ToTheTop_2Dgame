#include <stdio.h>
#include <stdlib.h>				// the atexit() function need it
#include <math.h>

#include <SDL.h>

SDL_Surface* g_pBackSurface;	// background image
SDL_Surface* g_platform1;	// foreground image for the platform1
SDL_Surface* g_platform2;	// foreground image for the platform2
SDL_Surface* g_platform3;	// foreground image for the platform3
SDL_Surface* g_portal;	// foreground image for the portal
SDL_Surface* g_ladder; // foreground image for the ladder


SDL_Surface* g_characterLeft;	// left image for the character
SDL_Surface *g_characterRight;	// right image for the character
SDL_Surface* g_characterHoldLeft;	// left image for the character holding ladder
SDL_Surface* g_characterHoldRight;	// right image for the character holding ladder
SDL_Surface* g_pScreen;			// video screen, there's always one of these

SDL_Window* g_pWindow;			// main window, there's always one of these

double back_ypos = 0;
double character_xpos = 752; double character_ypos = 672;  //800-48
double delta_character_ypos = 0.0001;
double platform_ypos = 400, platform1_xpos = 0, platform2_xpos = 400, platform3_xpos = 800;
double ladder_xpos = 500, ladder_ypos = 100;

int g_mode = 0;

int InitImages() {
	g_pBackSurface = SDL_LoadBMP("background.bmp");
	
	g_platform1 = SDL_LoadBMP("pipe_top.bmp");
	g_ladder = SDL_LoadBMP("pipe_bottom.bmp");
	g_characterRight = SDL_LoadBMP("flappybird_small_01.bmp");

	SDL_SetColorKey(g_characterRight, SDL_TRUE, SDL_MapRGB(g_characterRight->format, 255, 255, 255));
	return 0;
}

void DrawIMG(SDL_Surface* img, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface(img, NULL, g_pScreen, &dest);
}

void DrawObjects() {
	//back_ypos += 0.1;
	//if (back_ypos >= 224) { // 1024-800
		back_ypos = 0;
	//}
	SDL_Rect src_temp;
	src_temp.x = 0;
	src_temp.y = (int)back_ypos;
	src_temp.w = 1080;
	src_temp.h = 720;
	SDL_BlitSurface(g_pBackSurface, &src_temp, g_pScreen, NULL);

	
	DrawIMG(g_platform1, (int)platform1_xpos, (int)platform_ypos);
	DrawIMG(g_platform1, (int)platform2_xpos, (int)platform_ypos);
	DrawIMG(g_platform1, (int)platform3_xpos, (int)platform_ypos);

	DrawIMG(g_platform1, (int)platform1_xpos +50, (int)platform_ypos -200);
	DrawIMG(g_platform1, (int)platform2_xpos +70, (int)platform_ypos -200);
	DrawIMG(g_platform1, (int)platform3_xpos +80, (int)platform_ypos -200);

	DrawIMG(g_platform1, (int)platform1_xpos -100, (int)platform_ypos -400);
	DrawIMG(g_platform1, (int)platform2_xpos -50, (int)platform_ypos -400);
	DrawIMG(g_platform1, (int)platform3_xpos -20, (int)platform_ypos -400);


	DrawIMG(g_ladder, (int)platform3_xpos, (int)platform_ypos);
	DrawIMG(g_characterRight, (int)character_xpos, (int)character_ypos);

	//if (character_xpos -= 1.0) {
	//	DrawIMG(g_characterLeft, (int)character_xpos, (int)character_ypos);
	//}
	//else {
	//	DrawIMG(g_characterRight, (int)character_xpos, (int)character_ypos);
	//}
}

int main(int argc, char* argv[]) {

	const Uint8* keys;		// for keyboard key state

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	g_pWindow = SDL_CreateWindow("game_shooting_", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1080, 720, SDL_WINDOW_SHOWN);

	if (g_pWindow == NULL)
	{
		fprintf(stderr, "Error: Can't open window!  %s\n", SDL_GetError());
		exit(1);
	}

	g_pScreen = SDL_GetWindowSurface(g_pWindow);
	if (g_pScreen == NULL)
	{
		printf("Fail to get the main window surface : %s\n", SDL_GetError());
		exit(1);
	}

	InitImages();

	int done = 0;

	while (done == 0)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))		// Poll for the event
		{
			if (event.type == SDL_QUIT) { done = 1; }

			// item 
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE) { done = 1; }
			}
		}

		// item 0
		keys = SDL_GetKeyboardState(NULL);

		// SDL_GetKeyboardState() returns a pointer to an array of type Uint8. 
		// Each element of the array has information about a specific key 
		// (whether it is held down or not). 
		//
		// The reason why we don't check for the keys in the event loop is 
		// because in the event loop events are generated when a key has 
		// been pressed down, not if it is being held down. 
		//
		// We check if the left, right, up or down keys are pressed. 
		// And if so then we move the box one unit left, right, up or down. 
		// Since many keys can be pressed down at *once* so we don't 
		// use "else if" here.

		if (g_mode == 0) {

			if (character_ypos < 672) {
				delta_character_ypos += 0.001;
				character_ypos += delta_character_ypos;
			}else if (character_ypos = 672) {
					delta_character_ypos = 0;
			}
			else if (character_xpos <= (ladder_xpos + 350) && (character_xpos >= ladder_xpos + 280)) {
				if (character_ypos = platform_ypos) {
					delta_character_ypos = 0;
				}
			}
			
			// item 1
			// laser cannon
			// game loop (i) read user input ==========================
			// game loop (ii) do something based on user input ==========================
			if (keys[SDL_SCANCODE_LEFT]) {
				character_xpos -= 1.0; if (character_xpos < 0.0)   character_xpos = 0.0; 
				
			}
			if (keys[SDL_SCANCODE_RIGHT]) { 
				character_xpos += 1.0; if (character_xpos > 1024.0) character_xpos = 1024.0;
			}
			if (keys[SDL_SCANCODE_SPACE]) {
				if (character_xpos <= (ladder_xpos + 350) && (character_xpos >= ladder_xpos + 280))
				{
					character_ypos -= 1.0; if (character_ypos < 0.0)   character_ypos = 0.0;
				}
				//delta_character_ypos = -0.5;
			}
			//if (keys[SDL_SCANCODE_UP]) {
			//	character_ypos -= 1.0; if (character_ypos < 0.0)   character_ypos = 0.0;
			//}
			if (keys[SDL_SCANCODE_DOWN]) {
				if (character_xpos <= (ladder_xpos + 350) && (character_xpos >= ladder_xpos + 280)) {
					character_ypos += 1.0; if (character_ypos > 672.0)   character_ypos = 672.0;
				}
			}
			

			//if ((character_ypos <= (platform1_xpos + 310)) || (character_ypos >= platform2_xpos)) {
			//	if (((character_xpos + 64) >= platform_ypos) &&
			//		(character_xpos <= (platform_ypos + 100))) {
			//		delta_character_ypos = 0; // bird drops down
			//	}
			//}

			// no user input
			// game loop (ii) so do something, move in this case, by itself =================================
			

			// no user input
			// game loop (ii) so do something, move in this case =================================
			// item 3
			//lasercannon_bullet.move(arr_squids);

			// item 0
	//		if ( (ball_xpos >= 775) ||
	//			 (ball_xpos <= 0) ) {
	//			g_mode = 1;
	//		}
		}
		// item 0, g_mode above also
		// not really used here
		else if (g_mode == 1) {
			//showmessage_offboundary();
			if (keys[SDL_SCANCODE_SPACE]) {
				// reset variables
				//back_ypos = 0;
				
				character_xpos = 752;   //800-48
				character_ypos = 300 - 38;

				g_mode = 0;
			}
		}

		// item 0
		// game loop (iii) draw things based on world variables ===============
		DrawObjects();


		

		// update the Window
		// item 0
		SDL_UpdateWindowSurface(g_pWindow);
	}

	SDL_FreeSurface(g_pBackSurface);
	g_pBackSurface = NULL;
	SDL_FreeSurface(g_platform1);
	g_platform1 = NULL;
	SDL_FreeSurface(g_platform2);
	g_platform2 = NULL;
	SDL_FreeSurface(g_platform3);
	g_platform3 = NULL;

	SDL_FreeSurface(g_portal);
	g_portal = NULL;
	SDL_FreeSurface(g_ladder);
	g_ladder = NULL;

	SDL_FreeSurface(g_characterLeft);
	g_characterLeft = NULL;
	SDL_FreeSurface(g_characterRight);
	g_characterRight = NULL;
	SDL_FreeSurface(g_characterHoldLeft);
	g_characterHoldLeft = NULL;
	SDL_FreeSurface(g_characterHoldRight);
	g_characterHoldRight = NULL;

	//Destroy window
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}