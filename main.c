#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#include <SDL/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define CUADRO_CENTRAL 376
#define CUADRO_CENTRAL_POSX 132
#define CUADRO_CENTRAL_POSY 52

#define NUMERO_CUADROS 21
#define TAMANO_CUADROS_TABLERO 16
#define SEPARACION 2

#define MATRIZ_PIEZA 5

SDL_Surface *screen;
int Piezas [21][5][5] = 
	{ 
		{ {1,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {1,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {1,1,0,0,0},
		  {0,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		
		{ {1,1,1,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {1,1,0,0,0},
		  {1,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,1,0,0,0},
		  {1,1,1,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {1,1,1,1,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,0,1,0,0},
		  {1,1,1,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,1,1,0,0},
		  {1,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {1,0,0,0,0},
		  {1,1,1,1,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,1,0,0,0},
		  {0,1,0,0,0},
		  {1,1,1,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {1,0,0,0,0},
		  {1,0,0,0,0},
		  {1,1,1,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,1,1,1,0},
		  {1,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		
		{ {0,0,1,0,0},
		  {1,1,1,0,0},
		  {1,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {1,0,0,0,0},
		  {1,0,0,0,0},
		  {1,0,0,0,0},
		  {1,0,0,0,0},
		  {1,0,0,0,0} },
		  
		{ {1,0,0,0,0},
		  {1,1,0,0,0},
		  {1,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,1,1,0,0},
		  {1,1,0,0,0},
		  {1,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {1,1,0,0,0},
		  {1,0,0,0,0},
		  {1,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,1,1,0,0},
		  {1,1,0,0,0},
		  {0,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,1,0,0,0},
		  {1,1,1,0,0},
		  {0,1,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
		  
		{ {0,1,0,0,0},
		  {1,1,1,1,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0},
		  {0,0,0,0,0} },
	};

void Setup (void);
void DibujarTablero (void);
void DibujarPieza (int posY, int posX, int pieza[5][5]);
int ValidarPieza (int posY, int posX, int pieza[5][5]);

int main (int argc, char *argv[])
{
	int posY, posX, piezaRandom;
	srand(time(NULL)); 
    Setup ();
    DibujarTablero();
    
    /* Variable para recibir eventos */
    SDL_Event evento;
	
	piezaRandom = (int)(20.0*rand()/(RAND_MAX+1.0));
	
    do {
		while (SDL_PollEvent (&evento)) {
			DibujarTablero();
			switch (evento.type) {
				case SDL_QUIT:
					return 0;
					break;
				case SDL_KEYDOWN:
					switch(evento.key.keysym.sym) {
						case SDLK_LEFT:
							piezaRandom = (piezaRandom-1) < 0 ? 20 : (piezaRandom-1); 
							break;
						case SDLK_RIGHT:
							piezaRandom = (piezaRandom+1)%21; 
							break;
					}
					break;
			}
		}
		SDL_GetMouseState(&posX, &posY);
		if( posY >= CUADRO_CENTRAL_POSY && 
			posY <= (CUADRO_CENTRAL_POSY+CUADRO_CENTRAL) &&
			posX >= CUADRO_CENTRAL_POSX &&
			posX <= (CUADRO_CENTRAL_POSX+CUADRO_CENTRAL)) 
		{		
				posY = posY - CUADRO_CENTRAL_POSY;
				posX = posX - CUADRO_CENTRAL_POSX;

				if (posY % (TAMANO_CUADROS_TABLERO+SEPARACION) < TAMANO_CUADROS_TABLERO &&
					posX % (TAMANO_CUADROS_TABLERO+SEPARACION) < TAMANO_CUADROS_TABLERO) 
				{
					posY = posY/(TAMANO_CUADROS_TABLERO+SEPARACION);
					posX = posX/(TAMANO_CUADROS_TABLERO+SEPARACION);
					if (ValidarPieza (posY, posX, Piezas[piezaRandom])) {
						DibujarPieza (posY, posX, Piezas [piezaRandom]);
					}
				}
		}		

		SDL_Flip (screen);
		SDL_Delay (32);
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
	for (i = 0; i < NUMERO_CUADROS; i += 1)
	{
		for (j = 0; j < NUMERO_CUADROS; j += 1)
		{
			rect.x = CUADRO_CENTRAL_POSX + (TAMANO_CUADROS_TABLERO + SEPARACION) * j;
			rect.y = CUADRO_CENTRAL_POSY + (TAMANO_CUADROS_TABLERO + SEPARACION) * i;
			rect.w = rect.h = TAMANO_CUADROS_TABLERO;
			SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format,0xFF, 0xFF, 0xFF));
		}
	}
}

void DibujarPieza (int posY, int posX, int pieza[5][5]) {
	SDL_Rect rect;
	//int color[] = {(int)(254.0*rand()/(RAND_MAX+1.0)), (int)(254.0*rand()/(RAND_MAX+1.0)), (int)(254.0*rand()/(RAND_MAX+1.0))};
	int color[] = {0, 0, 255};
	
	int i, j;
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			if(pieza[i][j] == 1)
			{
				rect.x = CUADRO_CENTRAL_POSX + ((TAMANO_CUADROS_TABLERO+SEPARACION)*posX) + ((TAMANO_CUADROS_TABLERO+SEPARACION)*j);
				rect.y = CUADRO_CENTRAL_POSY + ((TAMANO_CUADROS_TABLERO+SEPARACION)*posY) + ((TAMANO_CUADROS_TABLERO+SEPARACION)*i);
				rect.w = rect.h = TAMANO_CUADROS_TABLERO;
				SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format, color[0], color[1], color[2]));
			}
		}
	}
}

int ValidarPieza (int posY, int posX, int pieza[5][5]) {
	int i, j;
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			if(pieza[i][j] == 1 && ((i+posY) >= NUMERO_CUADROS || (j+posX) >= NUMERO_CUADROS))
			{
				return 0;
			}
		}
	}
	return 1;
}

	/*DibujarPieza (0, 0, Piezas [0]);
    DibujarPieza (0, 2, Piezas [1]);
    DibujarPieza (0, 5, Piezas [2]);
    DibujarPieza (0, 8, Piezas [3]);
    ////////////////////////////////
    DibujarPieza (3, 0, Piezas [4]);
    DibujarPieza (3, 3, Piezas [5]);
    DibujarPieza (3, 7, Piezas [6]);
    DibujarPieza (3, 12, Piezas [7]);
    DibujarPieza (3, 16, Piezas [8]);
    ////////////////////////////////
    DibujarPieza (6, 0, Piezas [9]);
    DibujarPieza (6, 5, Piezas [10]);
    DibujarPieza (6, 9, Piezas [11]);
    DibujarPieza (6, 13, Piezas [12]);
    DibujarPieza (6, 18, Piezas [13]);
    ////////////////////////////////
    DibujarPieza (10, 0, Piezas [14]);
    DibujarPieza (10, 2, Piezas [15]);
    DibujarPieza (10, 5, Piezas [16]);
    DibujarPieza (10, 9, Piezas [17]);
    DibujarPieza (10, 12, Piezas [18]);
    DibujarPieza (10, 16, Piezas [19]);
    ////////////////////////////////
    DibujarPieza (16, 0, Piezas [20]);*/


