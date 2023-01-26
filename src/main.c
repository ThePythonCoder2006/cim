#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include <texture.h>
#include <molecule.h>
#include <timer.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define FILES_PATH "files"

/* ---------------- printf macros ------------------ */

#define PRINTF_BLACK "\033[0;30m"
#define PRINTF_RED "\033[0;31m"
#define PRINTF_GREEN "\033[0;32m"
#define PRINTF_YELLOW "\033[0;33m"
#define PRINTF_BLUE "\033[0;34m"
#define PRINTF_PURPLE "\033[0;35m"
#define PRINTF_CYAN "\033[0;36m"
#define PRINTF_WHITE "\033[0;37m"
#define PRINTF_RESET "\033[0m"

#define PRINTF_ERROR PRINTF_RED "[ERROR]" PRINTF_RESET
#define PRINTF_SUCESS PRINTF_GREEN "[SUCESS]" PRINTF_RESET
#define PRINTF_WARNING PRINTF_YELLOW "[WARNING]" PRINTF_RESET

/* ---------------- SDL macros ------------------ */

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define SCREEN_FPS 60
#define SCREEN_TPS (1000 / SCREEN_FPS)

// The window on wich we render the app
SDL_Window *gWindow = NULL;

// The renderer for the window
SDL_Renderer *gRenderer = NULL;

// the normal font for rendering anything (Fira code)
TTF_Font *gFont;

Texture *bond_wedge;
Texture *fpstext;

int SDL_init(void);

int load_media(void);

void SDL_quit(void);

int main(int argc, char **argv)
{
	(void)argc, (void)argv; // do not care about args

	if (SDL_init() != 0)
	{
		fprintf(stderr, PRINTF_ERROR " could not init SDL !!!!\n");
		return 1;
	}

	if (load_media() != 0)
	{
		fprintf(stderr, PRINTF_ERROR " could not load media !!!!\n");
		return 1;
	}

	SDL_Color text_color = {0, 0, 0, 255};

	char buff[64];

	uint32_t counted_frames = 0;
	Timer *fpstimer = Timer_init();
	Timer_start(fpstimer);

	uint8_t quit = 0;
	while (!quit)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = 1;
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		/* ---------------- geometry rendering ------------------ */

		/* ---------------- textures rendering ------------------ */
		Texture_render(bond_wedge, 100, 100, NULL, 20, &(SDL_Point){0, 0}, 0);
		Texture_render(bond_wedge, 100, 100, NULL, 110, &(SDL_Point){0, 0}, 0);

		// calculate and correct fps
		double avgFPS = counted_frames / (Timer_get_ticks(fpstimer) / 1000.0);
		if (avgFPS > 2000000)
			avgFPS = 0;

		snprintf(buff, 64, "%lf", avgFPS);
		Texture_load_text(fpstext, buff, text_color, gFont);

		Texture_render(fpstext, 0, 0, NULL, 0, NULL, 0);

		SDL_RenderPresent(gRenderer);
		++counted_frames;
		// do the average over 2000 frames
		if (counted_frames > 200)
		{
			counted_frames = 0;
			Timer_stop(fpstimer);
			Timer_start(fpstimer);
		}
	}

	SDL_quit();

	return 0;
}

int SDL_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf(PRINTF_ERROR "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return 1;
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		printf(PRINTF_WARNING "Warning: Linear texture filtering not enabled!");

	// Create a window
	gWindow = SDL_CreateWindow("cim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf(PRINTF_ERROR "Couln't create a window ! SDL error : %s", SDL_GetError());
		return 1;
	}

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 1;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be create! : %s\n", SDL_GetError());
		return 1;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}

	// Set the rendering color to black
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

	return 0;
}

void SDL_quit(void)
{
	Texture_free(bond_wedge);
	Texture_free(fpstext);

	TTF_CloseFont(gFont);

	// Destroy window
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	return;
}

int load_media(void)
{
	bond_wedge = Texture_init();
	if (Texture_load_from_file(bond_wedge, FILES_PATH "/wedge.png") != 0)
	{
		printf("could not load texture %s ! SDL error : %s\n", FILES_PATH "/wedge.png", SDL_GetError());
		return 1;
	}

	// load the font (Fira code)
	gFont = TTF_OpenFont(FILES_PATH "/FiraCode.ttf", 10);
	if (gFont == NULL)
	{
		printf("could not load the font file %s: %s\n", FILES_PATH "/FiraCode.ttf", TTF_GetError());
		return 1;
	}

	fpstext = Texture_init();
	SDL_Color text_color = {0, 0, 0, 255};
	if (Texture_load_text(fpstext, "ok boomer, I'm text !!!", text_color, gFont))
	{
		printf("error, could not render text !!!\n");
		return 1;
	}

	return 0;
}