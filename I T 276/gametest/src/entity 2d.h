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
int collide();
void drawHealth();
void drawLives();
void checkAll();
void fireWeapon();
void freeEntity();
void clearAll();
void drawEntity();
void demonSpawn();
void drawAll();
void entThink();
void demonThink();
void metroidThink();
void pirateThink();
void blasterThink();
void blasterTouch();
void rocketThink();
void rocketTouch();
void bombThink();
void fireRocket();
void plantBomb();
void initentityList();
void drawPlayer();
void updatePlayer();
void updateDemon();
void updateWeaponsFire();
void move();
