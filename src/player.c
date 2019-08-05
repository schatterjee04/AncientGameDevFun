#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
//#include "sge.h"
#include "entity.h"
#include "player.h"

void init_player(int x, int y){
	Entity *player;
	player = NewEntity();
	if(player != NULL){
		player->sprite = LoadSprite("images/player.png",44, 44);
		player->x = 100;
		player->y = 100;
		player->living = 1;
		player->health = 100;
		player->entType = 1;
		player->player = 1;
	}
}
