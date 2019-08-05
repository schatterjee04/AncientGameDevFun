//this is where all the entity stuff gets its functions//

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "entity.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

#define Max_Ent 9999

Entity entityList[Max_Ent];

int entCount;


#define ScreenX	1920
#define ScreenY	1200

void initentityList()
{
	int i;
	for(i = 0; i < Max_Ent; i++)
	{
		entityList[i].inUse = 0;
		entityList[i].moving = 0;
		entityList[i].living = 0;
		entityList[i].player = 0;
		entityList[i].health = -1;
		entityList[i].entType = 0;
		entityList[i].frame = 0;
		entityList[i].sprite = NULL;
	}
	entCount = 0;
}
Entity *NewEntity()
{
	int count;
	if(entCount > Max_Ent)
	{
		return NULL;
	}
	for(count = 0; count < Max_Ent; count++)
	{
		if(entityList[count].inUse == 0)
		{
			break;
		}
	}
	entCount++;
	entityList[count].inUse = 1;
	return &entityList[count];
}
void freeEntity(Entity *ent)
{
	if(ent == NULL)
		return;
	if(ent->player == 1)
		return;
	entCount--;
	if(ent->sprite != NULL)
	{
		FreeSprite(ent->sprite);
		ent->sprite = NULL;
	}
	ent->inUse = 0;
	ent->moving = 0;
	ent->living = 0;
	ent->player = 0;
	ent->health = -1;
	ent->x = 0;
	ent->y = 0;
	ent->h = 0;
	ent->w = 0;
	ent->dx = 0;
	ent->dy = 0;
	ent->entType = 0;
	ent->frame = 0;
}

void clearAll()
{
	int x;
	for(x = 0; x <= Max_Ent; x++)
	{
		freeEntity(&entityList[x]);
	}
}
void drawEntity(Entity *ent, int frame)
{
	if(ent != NULL)
	{
		if(ent-> sprite != NULL)
		{
			DrawSprite(ent->sprite, screen, ent->x, ent->y,frame);
		}
	}
}
void drawAll()
{
	int x;
	for(x = 0; x <= Max_Ent; x++)
	{
		if(entityList[x].health > 0)
		{
			drawEntity(&entityList[x],entityList[x].frame);
		}
	}
}
void drawHealth()
{
	SDL_Rect Health;
	int findAll;
	int x , y;
	for(findAll = 0; findAll <= Max_Ent; findAll++)
	{
		if(entityList[findAll].health > 0 || entityList[findAll].player == 1)
		{
			if(entityList[findAll].entType < 10)
			{
				Health.x = (entityList[findAll].x - 5);
				Health.y = (entityList[findAll].y - 8);
				Health.h = 5;
				if(((entityList[findAll].health * 5) / 10) > 50)
					Health.w = 50;
				else
					Health.w = ((entityList[findAll].health * 5) / 10);

				if(entityList[findAll].player == 1)
				{
					if(entityList[findAll].health < 1 && entityList[findAll].lives < 1)
					{						
						Health.x = 0;
						Health.y = 0;
						Health.h = ScreenY;
						Health.w = ScreenX;
						SDL_FillRect(screen,&Health,SDL_MapRGB(screen->format, 250, 250, 255));
						clearAll();
						return;
					}
					else if(entityList[findAll].health < 1 && entityList[findAll].lives > 0)
					{
						updatePlayer(40,40);
					}
					else
					{
						if(entityList[findAll].health < 25)
							SDL_FillRect(screen,&Health,SDL_MapRGB(screen->format, 128,0,0));
						else if(entityList[findAll].health > 24)
							SDL_FillRect(screen,&Health,SDL_MapRGB(screen->format, 0,0,128));
					}
				}
				if(entityList[findAll].health < 25)
					SDL_FillRect(screen,&Health,SDL_MapRGB(screen->format, 128,0,0));
				else if(entityList[findAll].health > 24)
					SDL_FillRect(screen,&Health,SDL_MapRGB(screen->format, 0,0,128));
			}
		}
	}
}
void drawLives()
{
	SDL_Rect Lives;
	int findPlayer;
	int lives;
	int placement;
	int drawLife = 10;
	Sprite *health;
	health = LoadSprite("images/player.png",50, 50);
	for(findPlayer = 0; findPlayer <= Max_Ent; findPlayer++)
	{
		if(entityList[findPlayer].player == 1)
			break;
	}
	lives = entityList[findPlayer].lives;
	for(placement = 1; placement <= lives; placement++)
	{
		DrawSprite(health, screen, drawLife, 10,0);
		drawLife += 60;
	}
}
void checkAll(){
	int loc, check;
	SDL_Rect ent1, ent2;
	for(loc = 0; loc <= Max_Ent; loc++)
	{
		ent1.h = entityList[loc].h;
		ent1.w = entityList[loc].w; 
		ent1.x = entityList[loc].x;
		ent1.y = entityList[loc].y;

		if(entityList[loc].health == 0)
		{
			freeEntity(&entityList[loc]);
		}
		if(entityList[loc].x < -100 || entityList[loc].y < -100 || entityList[loc].x > ScreenX || entityList[loc].y > ScreenY)
		{
			freeEntity(&entityList[loc]);
		}
		//if(entityList[loc].y + entityList[loc].h < (ScreenY - 5))
		//{
		//	for(check = 0; check <= Max_Ent; check++)
		//	{
		//		if(loc != check)
		//		{
		//			ent2.h = entityList[check].h;
		//			ent2.w = entityList[check].w; 
		//			ent2.x = entityList[check].x;
		//			ent2.y = entityList[check].y;
		//			if(collide(ent1,ent2) == 1)
		//				return;
		//		}
		//	}
		//}
	}
}
void demonSpawn(int x, int y)
{
	Entity *ent;
	ent = NewEntity();
	if(ent != NULL)
	{
		ent->sprite = LoadSprite("images/demon.png",90,90);
		ent->x = x;
		ent->y = y;
		ent->entType = 2;
		ent->h = 80;
		ent->w = 80;
		ent->health = 100;
	}
}
void updateDemon()
{
	int findDemons;
	for(findDemons = 0; findDemons <= Max_Ent; findDemons++)
	{
		if(entityList[findDemons].health > 0)
		{
			if(entityList[findDemons].entType == 2)
			{
				entThink(findDemons);
			}
		}
	}
}
void fireWeapon(int x, int y)
{
	Entity *ent;
	int findPlayer;
	double playerx, playery;
	double m, b, x1, y1, r, sine, cosine;
	ent = NewEntity();
	for(findPlayer = 0; findPlayer <= Max_Ent; findPlayer++)
	{
		if(entityList[findPlayer].player == 1)
			break;
	}
	//Sanity Check, I JUST found out this is really what you call it...
	if(entityList[findPlayer].health <= 0)
		return;
	playerx = entityList[findPlayer].x;
	playery = entityList[findPlayer].y;
	x1 = (playerx+39);
	y1 = (playery+11);
	m = ((y - y1) / (x - x1));
	b = (-1 * (m*x + y));
	if(ent != NULL)
	{
		ent->sprite = LoadSprite("images/blaster.png",10,10);
		ent->x = x1;
		ent->y = y1;
		ent->m = m;
		ent->entType = 10;
		ent->h = 15;
		ent->w = 15;
		ent->dx = x;
		ent->dy = y;
		ent->b = b;
		ent->px = x1;
		ent->py = y1;
		ent->health = 100;
		ent->rNew = 0;
	}
}
void updateWeaponsFire()
{
	int findWeaponsFire;
	for(findWeaponsFire = 0; findWeaponsFire <= Max_Ent; findWeaponsFire++)
	{	
		if(entityList[findWeaponsFire].entType > 9)
		{
			if(entityList[findWeaponsFire].entType == 10)
				blasterThink(findWeaponsFire);
		}
	}
}
void entThink(int loc)
{
	int findAll, findPlayer;
	int player_x, player_y, player_h, player_w;
	SDL_Rect ent1, ent2;

	//Demon Think cont.

	//Lets just be sure that we are a demon...
	if(entityList[loc].entType == 2)
	{
		//Where the HELL is the PLAYER!? Lets find out...
		for(findPlayer = 0; findPlayer <= Max_Ent; findPlayer++)
			if(entityList[findPlayer].player == 1)
				break;

		//Now that I know, lets not forget, shall We?
		player_x = entityList[findPlayer].x;
		player_y = entityList[findPlayer].y;

		//While we're at it, lets try and keep in mind how big the player is.
		player_h = entityList[findPlayer].h;
		player_w = entityList[findPlayer].w;

		//Now that we know everything about the player...
		//why not know a thing or two bout this lil' demon...
		ent1.h = entityList[loc].h;
		ent1.w = entityList[loc].w;
		ent1.x = entityList[loc].x;
		ent1.y = entityList[loc].y;

		//Colliding or moving?
		for(findAll = 0; findAll <= Max_Ent; findAll++)
		{
			//Well, what is it that I need to know?
			//Oh yeah, am I hitting something...
			//but wait, I could be hitting my self, couldn't I?
			if(findAll != loc)
			{
				//Oh good, so now I know that I am not checking against my self.
				//Okay, so now what?
				//Am I touching something?
				//Lets find out:
				ent2.h = entityList[findAll].h;
				ent2.w = entityList[findAll].w;
				ent2.x = entityList[findAll].x;
				ent2.y = entityList[findAll].y;

				if(collide(ent1, ent2) == 1)
				{
					//Well if the demon hits something, it should move away, right?
					//Lets find out where the thing is that we hit then move away...
					//But wait, Demons CAN'T dodge bullets...
					if(entityList[findAll].player == 1)
						entityList[findAll].health--;
					if(entityList[findAll].entType < 10)
					{
						if(ent1.x <= ent2.x)
						{
							//I guess this demon is to the LEFT of the other ENTITY.
							entityList[loc].x--;
							//Now we are moving away from the other entity.
							//Am I above or below?
							if(ent1.y <= ent2.y)
							{
								//The demon is above, lets move away
								entityList[loc].y--;
							}
							else if(ent1.y > player_y)
							{
								//It seems the demon is below the other entity...
								//Lets get further.
								entityList[loc].y++;
							}
						}
						else if(ent1.x > ent2.x)
						{
							//I guess this demon is to the RIGHT of the other ENTITY.
							entityList[loc].x++;
							//Now we are moving away from the other entity.
							//Am I above or below?
							if(ent1.y <= ent2.y)
							{
								//The demon is above, lets move away
								entityList[loc].y--;
							}
							else if(ent1.y > player_y)
							{
								//It seems the demon is below the other entity...
								//Lets get further.
								entityList[loc].y++;
							}
						}
					}
				}
			}
		}
		//Well, I guess we didn't hit anything...
		//What do I do? Well we look for the player.
		if(entityList[findPlayer].health > 0)
		{
			if((ent1.x + 100) < player_x)
			{
				//I guess this demon is to the LEFT of the PLAYER.
				//But I'm sure the player likes his/her personal space, right?
				//I'm sure a 100 pixels are enough...
				entityList[loc].x++;
				//Now we are moving closer to the player.
				//What if the demon is above or below?
				//Lets find out...
				if((ent1.y + (ent1.h - player_h)) < player_y)
				{
					//It seems the demon is above the player...
					//Lets get closer.
					entityList[loc].y++;
				}
				else if((ent1.y + (ent1.h - player_h)) > player_y)
				{
					//It seems the demon is below the player...
					//Lets get closer.
					entityList[loc].y--;
				}
			}
			else if(((ent1.x - player_w) - 100) > player_x)
			{
				//I guess this demon is to the RIGHT of the PLAYER.
				//But I'm sure the player likes his/her personal space, right?
				//I'm sure a 100 pixels plus the players width is enough...
				entityList[loc].x--;
				//Now we are moving closer to the player.
				//What if the demon is above or below?
				//Lets find out...
				if((ent1.y + (ent1.h - player_h)) < player_y)
				{
					//It seems the demon is above the player...
					//Lets get closer.
					entityList[loc].y++;
				}
				else if((ent1.y + (ent1.h - player_h)) > player_y)
				{
					//It seems the demon is below the player...
					//Lets get closer.
					entityList[loc].y--;
				}
			}
			else 
			{
				if((ent1.y + (ent1.h - player_h)) < player_y)
				{
					//It seems the demon is above the player...
					//Lets get closer.
					entityList[loc].y++;
				}
				else if((ent1.y + (ent1.h - player_h)) > player_y)
				{
					//It seems the demon is below the player...
					//Lets get closer.
					entityList[loc].y--;
				}
			}
		}
		/*if((entityList[loc].x + entityList[loc].w + 200) < entityList[findPlayer].x)
		{

		}*/
	}
	//end demon think
	//start weapon think
}
void drawPlayer(int dx, int dy)
{
	Entity *player;
	player = NewEntity();
	if(player != NULL)
	{
		player->sprite = LoadSprite("images/player.png",50, 50);
		player->x = dx;
		player->y = dy;
		player->living = 1;
		player->health = 100;
		player->lives = 3;
		player->entType = 1;
		player->player = 1;
		player->h = 45;
		player->w = 45;
		player->frame = 0;
	}
}
void updatePlayer(int dx, int dy)
{
	int findPlayer;
	int findAll;
	int x, y;
	SDL_Rect Player;
	SDL_Rect EntCheck;
	for(findPlayer = 0; findPlayer < Max_Ent; findPlayer++)
	{
		if(entityList[findPlayer].player == 1)
		{
			break;
		}
	}
	if(entityList[findPlayer].health <= 0)
	{
		if(entityList[findPlayer].lives <= 0)
		{
			entityList[findPlayer].living = 0;
		}
		else
		{
			entityList[findPlayer].x = 40;
			entityList[findPlayer].y = 40;
			entityList[findPlayer].health = 100;
			entityList[findPlayer].lives--;
		}
	}

	if(entityList[findPlayer].living == 0 || entityList[findPlayer].health <= 0)
		return;
	x = entityList[findPlayer].x;
	y =	entityList[findPlayer].y;
	if((x + dx) <= 0 || (x + dx) >= (ScreenX - entityList[findPlayer].w))
		return;
	if((y + dy) <= 0 || (y + dy) >= (ScreenY - entityList[findPlayer].h))
		return;
	Player.x = x;
	Player.y = y;
	Player.h = entityList[findPlayer].h;
	Player.w = entityList[findPlayer].w;
	
	for(findAll = 0; findAll <= Max_Ent; findAll++)
	{
		if(findAll != findPlayer)
		{
			EntCheck.h = entityList[findAll].h;
			EntCheck.w = entityList[findAll].w;
			EntCheck.x = entityList[findAll].x;
			EntCheck.y = entityList[findAll].y;
			if(collide(Player, EntCheck) == 1)
			{
				if(entityList[findAll].entType != 10)
				{
					entityList[findPlayer].health--;
				}
			}
		}
	}
	if((x + dx) != x)
	{
		if((x + dx) > x)
		{
			entityList[findPlayer].frame = ((entityList[findPlayer].frame + 1) % 11);
			entityList[findPlayer].sprite = LoadSprite("images/player_run.png",44, 44);
		}
		else if((x + dx) < x)
		{
			entityList[findPlayer].frame = ((entityList[findPlayer].frame + 1) % 11);
			entityList[findPlayer].sprite = LoadSprite("images/player_run_left.png",44, 44);
		}

	}
	else
	{
		entityList[findPlayer].frame = 0;	
		entityList[findPlayer].sprite = LoadSprite("images/player.png",50, 50);
	}
	entityList[findPlayer].x = (x + dx);
	entityList[findPlayer].y = (y + dy);	
}
int collide(SDL_Rect obj1, SDL_Rect obj2)
{
	if(((obj1.x + obj1.w) >= obj2.x) && (obj1.x <= (obj2.x + obj2.w)) && ((obj1.y + obj1.h) >= obj2.y) && (obj1.y <= (obj2.y + obj2.h)))
		return 1;
	return 0;
}
void demonThink(int loc)
{

}
void metroidThink()
{
}
void pirateThink()
{
}
void blasterThink(int loc)
{
	SDL_Rect ent1, ent2;
	int findAll;
	if(entityList[loc].health > 0)
	{
		ent1.h = entityList[loc].h;
		ent1.w = entityList[loc].w;
		ent1.x = entityList[loc].x;
		ent1.y = entityList[loc].y;
		for(findAll = 0; findAll <= Max_Ent; findAll++)
		{
			if(findAll != loc)
			{
				if(entityList[findAll].health > 0)
				{
					if(entityList[findAll].player != 1)
					{
						ent2.h = entityList[findAll].h;
						ent2.w = entityList[findAll].w;
						ent2.x = entityList[findAll].x;
						ent2.y = entityList[findAll].y;
						if(collide(ent1,ent2) == 1)
						{
							blasterTouch(loc,findAll);
						}
					}
				}
			}
		}
		entityList[loc].frame = 0;
		if(entityList[loc].m > 40 || entityList[loc].m  < -40)
		{
			if(entityList[loc].py < entityList[loc].dy)
			{
				entityList[loc].y += 40;
			}
			else
			{
				entityList[loc].y -= 40;
			}
		}
		else if(entityList[loc].dx < entityList[loc].px)
		{
			entityList[loc].x-=30;
			if(entityList[loc].dy > entityList[loc].py)
			{
				entityList[loc].y-=(entityList[loc].m * 30);
			}
			else if(entityList[loc].dy < entityList[loc].py)
			{
				entityList[loc].y-=(entityList[loc].m * 30);
			}
		}
		else if(entityList[loc].dx > entityList[loc].px)
		{
			entityList[loc].x+=30;
			if(entityList[loc].dy > entityList[loc].py)
			{
				entityList[loc].y+=(entityList[loc].m * 30);
			}
			else if(entityList[loc].dy < entityList[loc].py)
			{
				entityList[loc].y+=(entityList[loc].m * 30);
			}
		}
	}	
}
void blasterTouch(int roundLoc, int entLoc)
{
	int coolDown = 0;
	int k;
	Sprite *anim;
	anim = LoadSprite("images/blasterExplode.png",8,8);
	if(entityList[entLoc].player != 1)
	{
		if(entityList[entLoc].entType != entityList[roundLoc].entType)
		{
			for(k = 0; k < 30; k++)
			{
				DrawSprite(anim, screen, entityList[roundLoc].x, entityList[roundLoc].y,coolDown);
				coolDown = (coolDown+1)%3;
			}
			entityList[entLoc].health-=5;
			entityList[roundLoc].health=0;
		}
	}
}
void rocketThink()
{
}
void rocketTouch()
{
}
void bombThink()
{
}
void fireRocket(int x, int y)
{
}
void plantBomb(int x, int y)
{
}