#pragma once
#ifndef __TEXTURE__
#define __TEXTURE__

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

typedef struct struct_Texture
{
	uint16_t w, h;
	SDL_Texture *texture;
} Texture;

int Texture_load_from_file(Texture *texture, char *path);

int Texture_render(Texture *texture, uint16_t x, uint16_t y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip);

Texture *Texture_init();

int Texture_free(Texture *texture);

int Texture_load_text(Texture *texture, const char *text, SDL_Color color, TTF_Font *font);

#endif // __TEXTURE__