//this is where all the entity stuff goes//
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "sge.h"

typedef struct
{
	int inUse;
	int moving;
	int living;
	int player;
	int health;
	int lives;
	int entType;
	double x, y, h, w;
	double dx, dy, m, b, px, py;
	double r, sine, cosine, rNew, theta;
	int frame;
	int entNum;
	Sprite *sprite;
	Uint32 lifespan;
}Entity;

Entity *NewEntity();
int collide(SDL_Rect,SDL_Rect);
void blasterThink(int);
void blasterTouch(int, int);
void bombThink();
void checkAll();
void clearAll();
void demonSpawn(int, int);
void demonThink();
void drawAll();
void drawEntity();
void drawHealth();
void drawLives();
void drawPlayer(int,int);
void entThink(int);
void fireRocket(int, int);
void fireWeapon(int,int);
void freeEntity();
void initentityList();
void metroidThink();
void move();
void plantBomb();
void pirateThink();
void rocketThink();
void rocketTouch();
void updateDemon();
void updatePlayer(int, int);
void updateWeaponsFire();
