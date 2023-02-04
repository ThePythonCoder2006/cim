#ifndef __CONSTS__
#define __CONSTS__

#include <molecule.h>
#include <atom.h>
#include <texture.h>
#include <time.h>

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

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define SCREEN_FPS 60
#define SCREEN_TPS (1000 / SCREEN_FPS)

#define BG_COLOR 0x11, 0x11, 0x11, 0xFF
#define FRONT_COLOR 0xFF, 0xFF, 0xFF, 0xFF

#define BOND_LEN 80

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;
extern TTF_Font *gFPS_font;

#endif // __CONSTS__