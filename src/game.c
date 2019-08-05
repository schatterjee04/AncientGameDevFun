#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "entity.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

void Init_All();


/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  SDL_Surface *temp;
  SDL_Surface *bg;
  Sprite *tile;
  int done;
  int keyn;
  int mx,my;
  int moveX;
  int moveY;
  int frame = 0;
  Uint8 *keys;
  Uint8 k;
  Init_All();
  temp = IMG_Load("images/bgtest.png");/*notice that the path is part of the filename*/
  if(temp != NULL)						/*ALWAYS check your pointers before you use them*/
    bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  if(bg != NULL)
    SDL_BlitSurface(bg,NULL,buffer,NULL);
  /*tile = LoadSprite("images/tile.png",32,32);
  if(tile != NULL)for(i = 0;i < 12;i++)
  {
    DrawSprite(tile,buffer,i * tile->w,0,0);
  }*/
  done = 0;
  do
  {
    ResetBuffer();
    updateWeaponsFire();
	updateDemon();
 	checkAll();
	drawAll();
	drawLives();
	drawHealth();
    DrawMouse();
    NextFrame();
    SDL_PumpEvents();
    keys = SDL_GetKeyState(&keyn);
	moveX = 0;
	moveY = 0;
	if(keys[SDLK_w]){
		updatePlayer(0,-10);
	}
	if(keys[SDLK_s]){
		updatePlayer(0,10);
	}
	if(keys[SDLK_a]){
		updatePlayer(-10,0);
	}
	if(keys[SDLK_d]){
		updatePlayer(10,0);
	}
	k = SDL_GetMouseState(NULL,NULL);
	if(keys[SDLK_SPACE]){
		int x;
		int y;
		SDL_GetMouseState(&x,&y);
		demonSpawn(x,y);
	}
	if(keys[SDLK_f])
	{
		int x;
		int y;
		SDL_GetMouseState(&x,&y);
		fireRocket(x,y);
	}
	if(k & SDL_BUTTON(1)){
		int x, y;
		SDL_GetMouseState(&x,&y);
		fireWeapon(x,y);
	}
	if(keys[SDLK_c]){
		clearAll();
	}
    if(keys[SDLK_ESCAPE])done = 1;
  }while(!done);
//  exit(0);		/*technically this will end the program, but the compiler likes all functions 
//                    that can return a value TO return a value*/
//  return 0;
}

void CleanUpAll()
{
  CloseSprites();
  clearAll();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
  Init_Graphics();
  initentityList();
  InitMouse();
  drawPlayer(750,750);
  demonSpawn(5,5);
  demonSpawn(1,1);
  atexit(CleanUpAll);
}

