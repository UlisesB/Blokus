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

#define VACIO 0
#define JUGADOR_1 1
#define JUGADOR_2 2

SDL_Surface *screen;
int EstadoTablero[NUMERO_CUADROS][NUMERO_CUADROS];

int Piezas [NUMERO_CUADROS][MATRIZ_PIEZA][MATRIZ_PIEZA] = 
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
void DibujarEstadoTablero (void);
void CambiarEstadoTablero (int posY, int posX, int (*)[5]);
void DibujarPieza (int posY, int posX, int (*)[5]);
int ValidarPieza (int posY, int posX, int (*)[5]);
void RotarDerecha (int pieza);
void RotarIzquierda (int pieza);
void EliminarVacio(int (*)[5]);
void ReflejarHorizontal (int pieza);
void ReflejarVertical (int pieza);

int main (int argc, char *argv[])
{
	int posY, posX, piezaRandom;
	srand(time(NULL));
    Setup ();
	memset(EstadoTablero, 0, sizeof(int)*NUMERO_CUADROS);
    DibujarTablero();
    
    /* Variable para recibir eventos */
    SDL_Event evento;
	
	piezaRandom = (int)(20.0*rand()/(RAND_MAX+1.0));
	
    do {
    	DibujarEstadoTablero();
		while (SDL_PollEvent (&evento)) {
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
						/*case SDLK_UP:
							RotarDerecha(piezaRandom);
							break;
						case SDLK_DOWN:
							RotarIzquierda(piezaRandom);
							break;*/
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch(evento.button.button) {
						case SDL_BUTTON_WHEELUP:
							RotarDerecha(piezaRandom);
							break;				
						case SDL_BUTTON_WHEELDOWN:						
							RotarIzquierda(piezaRandom);
							break;
						case SDL_BUTTON_MIDDLE:
							ReflejarVertical(piezaRandom);
							break;
						case SDL_BUTTON_RIGHT:
							ReflejarHorizontal(piezaRandom);
							break;
						case SDL_BUTTON_LEFT:
							if( evento.button.y >= CUADRO_CENTRAL_POSY && 
								evento.button.y <= (CUADRO_CENTRAL_POSY+CUADRO_CENTRAL) &&
								evento.button.x >= CUADRO_CENTRAL_POSX &&
								evento.button.x <= (CUADRO_CENTRAL_POSX+CUADRO_CENTRAL)) 
							{		
								evento.button.y = evento.button.y - CUADRO_CENTRAL_POSY;
								evento.button.x = evento.button.x - CUADRO_CENTRAL_POSX;

								if (evento.button.y % (TAMANO_CUADROS_TABLERO+SEPARACION) < TAMANO_CUADROS_TABLERO &&
									evento.button.x % (TAMANO_CUADROS_TABLERO+SEPARACION) < TAMANO_CUADROS_TABLERO) 
								{
									evento.button.y = evento.button.y/(TAMANO_CUADROS_TABLERO+SEPARACION);
									evento.button.x = evento.button.x/(TAMANO_CUADROS_TABLERO+SEPARACION);
									if (ValidarPieza (evento.button.y, evento.button.x, Piezas[piezaRandom])) {
										CambiarEstadoTablero(evento.button.y, evento.button.x, Piezas [piezaRandom]);
									}
								}
							}
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
}

void DibujarEstadoTablero (void) {
	SDL_Rect rect;
	int i, j;
	int colorJugador1[] = {0, 0, 255};
	int colorJugador2[] = {255, 0, 0};
	int colorVacio[] = {255, 255, 255};
	for (i = 0; i < NUMERO_CUADROS; i += 1)
	{
		for (j = 0; j < NUMERO_CUADROS; j += 1)
		{
			rect.x = CUADRO_CENTRAL_POSX + (TAMANO_CUADROS_TABLERO + SEPARACION) * j;
			rect.y = CUADRO_CENTRAL_POSY + (TAMANO_CUADROS_TABLERO + SEPARACION) * i;
			rect.w = rect.h = TAMANO_CUADROS_TABLERO;
			switch(EstadoTablero[i][j]) {
				case VACIO:
					SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format, colorVacio[0], colorVacio[1], colorVacio[2]));
					break;
				case JUGADOR_1:
					SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format, colorJugador1[0], colorJugador1[1], colorJugador1[2]));
					break;
				case JUGADOR_2:
					SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format, colorJugador2[0], colorJugador2[1], colorJugador2[2]));
					break;
			}
		}
	}
}

void CambiarEstadoTablero (int posY, int posX, int (*pieza)[5]) {
	int i, j;
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			if(pieza[i][j] == 1)
			{
				EstadoTablero[posY + i][posX + j] = JUGADOR_1;
			}
		}
	}
}

void DibujarPieza (int posY, int posX, int (*pieza)[5]) {
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

int ValidarPieza (int posY, int posX, int (*pieza)[5]) {
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

void EliminarVacios (int (*piezaRotada)[MATRIZ_PIEZA]) {
	int i, j;
	while(piezaRotada[0][0]+piezaRotada[1][0]+piezaRotada[2][0]+piezaRotada[3][0]+piezaRotada[4][0] == 0) {
		for (i = 0; i < MATRIZ_PIEZA - 1; i += 1)
		{
			for (j = 0; j < MATRIZ_PIEZA; j += 1)
			{
				piezaRotada[j][i] = piezaRotada[j][i+1];
			}
		}
		piezaRotada[0][4]=piezaRotada[1][4]=piezaRotada[2][4]=piezaRotada[3][4]=piezaRotada[4][4] = 0;
	}
	while(piezaRotada[0][0]+piezaRotada[0][1]+piezaRotada[0][2]+piezaRotada[0][3]+piezaRotada[0][4] == 0) {
		for (i = 0; i < MATRIZ_PIEZA - 1; i += 1)
		{
			for (j = 0; j < MATRIZ_PIEZA; j += 1)
			{
				piezaRotada[i][j] = piezaRotada[i+1][j];
			}
		}
		piezaRotada[4][0]=piezaRotada[4][1]=piezaRotada[4][2]=piezaRotada[4][3]=piezaRotada[4][4] = 0;
	}
}

void ReflejarVertical (int pieza) {
	int piezaReflejada[5][5];
	int h = MATRIZ_PIEZA-1, i, j;
	
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			piezaReflejada[h-i][j] = Piezas[pieza][i][j];
		}
	}
	EliminarVacios(piezaReflejada);
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			Piezas[pieza][i][j] = piezaReflejada[i][j];
		}
	}
}

void ReflejarHorizontal (int pieza) {
	int piezaReflejada[5][5];
	int h = MATRIZ_PIEZA-1, i, j;
	
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			piezaReflejada[i][h-j] = Piezas[pieza][i][j];
		}
	}
	EliminarVacios(piezaReflejada);
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			Piezas[pieza][i][j] = piezaReflejada[i][j];
		}
	}
}

void RotarDerecha (int pieza) {
	int piezaRotada[5][5];
	int h = MATRIZ_PIEZA-1, i, j;
	
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			piezaRotada[j][h] = Piezas[pieza][i][j];
		}
		h--;
	}
	EliminarVacios(piezaRotada);
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			Piezas[pieza][i][j] = piezaRotada[i][j];
		}
	}
}

void RotarIzquierda (int pieza) {
	int piezaRotada[5][5];
	int h = MATRIZ_PIEZA-1, i, j;
	
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			piezaRotada[h-j][i] = Piezas[pieza][i][j];
		}
	}
	EliminarVacios(piezaRotada);
	for (i = 0; i < MATRIZ_PIEZA; i += 1)
	{
		for (j = 0; j < MATRIZ_PIEZA; j += 1)
		{
			Piezas[pieza][i][j] = piezaRotada[i][j];
		}
	}
}


	
