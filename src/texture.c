#include <texture.h>

Texture *Texture_init()
{
	return malloc(sizeof(Texture));
}

int Texture_free(Texture *texture)
{
	if (texture == NULL)
		return 0;

	if (texture->texture == NULL)
		return 0;

	SDL_DestroyTexture(texture->texture);

	texture->w = 0;
	texture->h = 0;

	return 0;
}

int Texture_load_from_file(Texture *texture, char *path)
{
	Texture_free(texture);

	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *surface = IMG_Load(path);
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		return 1;
	}

	// Convert surface to screen format
	newTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (newTexture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		return 1;
	}

	texture->w = surface->w;
	texture->h = surface->h;

	texture->texture = newTexture;

	SDL_FreeSurface(surface);

	return 0;
}

int Texture_render(Texture *texture, uint16_t x, uint16_t y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_Rect render_quad = {.x = x, .y = y, .w = texture->w, .h = texture->h};

	if (clip != NULL)
	{
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, texture->texture, clip, &render_quad, angle, center, flip);

	return 0;
}

int Texture_load_text(Texture *texture, char *text, SDL_Color color, TTF_Font *font)
{
	// Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
	if (textSurface == NULL)
	{
		printf("Unable to render text (%s) surface! SDL_ttf Error: %s\n", text, TTF_GetError());
		return 1;
	}

	// Create texture from surface pixels
	texture->texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	if (texture->texture == NULL)
	{
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		return 1;
	}

	// Get image dimensions
	texture->w = textSurface->w;
	texture->h = textSurface->h;

	// Get rid of old surface
	SDL_FreeSurface(textSurface);

	// Return success
	return 0;
}