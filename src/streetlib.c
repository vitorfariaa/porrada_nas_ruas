#include <stdio.h>
#include <stdlib.h>

#include "streetlib.h"

player* player_create(unsigned char side, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y){

	if ((x - side / 2 < 0) || (x + side/2 > max_x) || (y - side/2 < 0) || (y + side/2 > max_y))
		return NULL;

	player *new_player = (player*)malloc(sizeof(player));
	new_player->side = side;
	new_player->face = face;
	new_player->hp = 100;
	new_player->punchcool = 0;
	new_player->kickcool = 0;
	new_player->speccool = 0;
	new_player->x = x;
	new_player->y = y;
	new_player->veloY = 0;
	new_player->control = joystick_create();
	new_player->attackAnimation = 0;
	new_player->bullet = NULL;
	new_player->isDead = 0;

	new_player->sprites = NULL;
	new_player->state = 0;

	new_player->wins = 0;

	return new_player;
}

// funcao load_sprites busca os sprites na pasta "sprites" e com o numero do personagem escolhido
sprite* load_sprites(int charsel) {

    sprite *sprites = (sprite*)malloc(sizeof(sprite));

	for (int i = 0; i < 8; i++){
		char path[256];
		sprintf(path, "assets/sprites/sprites%d/walking%d.png", charsel, i+1);

		sprites->walk[i] = al_load_bitmap(path);
	}

	for (int i = 0; i < 7; i++){
        char path[256];
        sprintf(path, "assets/sprites/sprites%d/jump%d.png", charsel, i+1);

        sprites->jump[i] = al_load_bitmap(path);
    }

	for (int i = 0; i < 3; i++){
        char path[256];
        sprintf(path, "assets/sprites/sprites%d/kick%d.png", charsel, i+1);

        sprites->kick[i] = al_load_bitmap(path);
    }


	for (int i = 0; i < 3; i++){
        char path[256];
        sprintf(path, "assets/sprites/sprites%d/chuteDown%d.png", charsel, i+1);

        sprites->kickDown[i] = al_load_bitmap(path);
    }

	for (int i = 0; i < 4; i++){
        char path[256];
        sprintf(path, "assets/sprites/sprites%d/punch%d.png", charsel, i+1);

        sprites->punch[i] = al_load_bitmap(path);
    }

	for (int i = 0; i < 3; i++){
        char path[256];
        sprintf(path, "assets/sprites/sprites%d/socoDown%d.png", charsel, i+1);

        sprites->punchDown[i] = al_load_bitmap(path);
    }

	for (int i = 0; i < 3; i++){
		char path[256];
        sprintf(path, "assets/sprites/sprites%d/spec%d.png", charsel, i+1);

        sprites->specialSprite[i] = al_load_bitmap(path);
    }

	for (int i = 0; i < 3; i++){
        char path[256];
        sprintf(path, "assets/sprites/sprites%d/specAttack%d.png", charsel, i+1);

        sprites->specialAttack[i] = al_load_bitmap(path);
    }

	char path1[256];
	sprintf(path1, "assets/sprites/sprites%d/idleDown.png", charsel);
	sprites->down[0] = al_load_bitmap(path1);
	
	char path2[256];
	sprintf(path2, "assets/sprites/sprites%d/idle.png", charsel);
    sprites->idle[0] = al_load_bitmap(path2);

	char path3[256];
	sprintf(path3, "assets/sprites/sprites%d/isdead.png", charsel);
	sprites->isDead[0] = al_load_bitmap(path3);

	char path4[256];
	sprintf(path4, "assets/sprites/sprites%d/iswinner.png", charsel);
	sprites->isWinner[0] = al_load_bitmap(path4);

    sprites->current_frame = 0;
    sprites->frame_count = 0;
    return sprites;
}

void player_move(player *element, char steps, unsigned char traj, unsigned short max_x, unsigned short max_y){
	if (!traj){
		if ((element->x - steps) - element->side/2 >= 0)
			element->x = element->x - steps; // movimentacao para esquerda
	}

	else if (traj == 1){ 
		if ((element->x + steps) + element->side/2 <= max_x) 
			element->x = element->x + steps; // movimentacao para direita
	}

	else if (traj == 2){ 
		if ((element->y - steps) - element->side/2 >= 0) 
			element->y = element->y - steps; // movimentacao para cima
	}

	else if (traj == 3){ 
		if ((element->y + steps) + element->side/2 <= max_y) 
			element->y = element->y + steps; // movimentacao para baixo
	}
}

// limpeza do player e de todos os atributos dinamicos do player
void player_destroy(player *element){
	if (element->sprites) {
        for (int i = 0; i < 8; i++) {
            if (element->sprites->walk[i])
                al_destroy_bitmap(element->sprites->walk[i]);
        }
        for (int i = 0; i < 7; i++) {
            if (element->sprites->jump[i])
                al_destroy_bitmap(element->sprites->jump[i]);
        }
        for (int i = 0; i < 3; i++) {
            if (element->sprites->kick[i])
                al_destroy_bitmap(element->sprites->kick[i]);
            if (element->sprites->kickDown[i])
                al_destroy_bitmap(element->sprites->kickDown[i]);
            if (element->sprites->specialSprite[i])
                al_destroy_bitmap(element->sprites->specialSprite[i]);
            if (element->sprites->specialAttack[i])
                al_destroy_bitmap(element->sprites->specialAttack[i]);
        }
        for (int i = 0; i < 4; i++) {
            if (element->sprites->punch[i])
                al_destroy_bitmap(element->sprites->punch[i]);
        }
        for (int i = 0; i < 3; i++) {
            if (element->sprites->punchDown[i])
                al_destroy_bitmap(element->sprites->punchDown[i]);
        }
        if (element->sprites->idle[0])
            al_destroy_bitmap(element->sprites->idle[0]);
        if (element->sprites->down[0])
            al_destroy_bitmap(element->sprites->down[0]);
        if (element->sprites->isDead[0])
            al_destroy_bitmap(element->sprites->isDead[0]);
        if (element->sprites->isWinner[0])
            al_destroy_bitmap(element->sprites->isWinner[0]);
        free(element->sprites);
    }

	joystick_destroy(element->control);
	free(element);
}
