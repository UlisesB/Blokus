#include <stdio.h>
#include <stdlib.h>
 
#include <SDL/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define CUADRO_CENTRAL 376
#define CUADRO_CENTRAL_POSX 132
#define CUADRO_CENTRAL_POSY 52

#define CUADROS_TABLERO 16
#define SEPARACION 2

SDL_Surface *screen;

void Setup (void);
void DibujarTablero (void);

int main (int argc, char *argv[])
{
    Setup ();
    DibujarTablero();
    
    SDL_Flip (screen);
    /* Variable para recibir eventos */
    SDL_Event evento;
 
    do {
        while (SDL_WaitEvent(&evento)) {
            /* Si el evento es de salida, pues, salir */
            if (evento.type == SDL_QUIT) {
                return 0;
            }
        }
    } while (1);
 
    return 0;
}


void Setup (void) {
    int depth;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf (stderr,
            "Error: No se pudo inicializar el sistema de video\n"
            "El error devuelto por SDL es:\n"
            "%s\n", SDL_GetError());
        exit (1);
    }
    depth = SDL_VideoModeOK (SCREEN_WIDTH, SCREEN_HEIGHT, 16, 0);
 
    if (depth == 0) {
        fprintf (stderr, "Error: No se pudo establecer el modo de video\n");
        exit (1);
    }
    
    screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, depth, 0);        
}

void DibujarTablero (void) {
	SDL_Rect rect;	
	
	/* Fondo Gris */
	rect.x = rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;
	SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format,0x76, 0x76, 0x76));
	
	rect.x = CUADRO_CENTRAL_POSX;
	rect.y = CUADRO_CENTRAL_POSY;
	rect.w = rect.h = CUADRO_CENTRAL;
	SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format,0xE8, 0xE8, 0xE8));
	
	int i, j;
	for (i = 0; i < 21; i += 1)
	{
		for (j = 0; j < 21; j += 1)
		{
			rect.x = CUADRO_CENTRAL_POSX + (CUADROS_TABLERO + SEPARACION) * j;
			rect.y = CUADRO_CENTRAL_POSY + (CUADROS_TABLERO + SEPARACION) * i;
			rect.w = rect.h = CUADROS_TABLERO;
			SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format,0xFF, 0xFF, 0xFF));
		}
	}
}


















