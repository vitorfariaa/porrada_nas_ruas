#ifndef __PLAYER__
#define __PLAYER__

#include "Joystick.h"
#include <allegro5/allegro.h>
#include <string.h>

// struct que guarda todos os sprites para a movimentacao de um personagem
typedef struct {
	ALLEGRO_BITMAP *walk[8];
	ALLEGRO_BITMAP *jump[7];
	ALLEGRO_BITMAP *kick[3];
	ALLEGRO_BITMAP *kickDown[3];
	ALLEGRO_BITMAP *punch[4];
	ALLEGRO_BITMAP *punchDown[3];
	ALLEGRO_BITMAP *idle[1];
	ALLEGRO_BITMAP *down[1];
	ALLEGRO_BITMAP *specialSprite[3];
	ALLEGRO_BITMAP *specialAttack[3];
	ALLEGRO_BITMAP *isDead[1];
	ALLEGRO_BITMAP *isWinner[1];
	int current_frame;
	int frame_count;
} sprite;

// struct que guarda as informacoes do ataque especial
typedef struct {
	short traj;
	short x;
	short y;
	short current_frame;
	short frame_count;
} special;

// struct que guarda todas as informacoes referentes ao player
typedef struct {
	unsigned char side;
	unsigned char face;
	short hp;
	unsigned char punchcool;
	unsigned char kickcool;
	unsigned short speccool;
	unsigned short x;
	unsigned short y;
	float veloY;
	joystick *control;
	sprite *sprites;
	unsigned char wins;
	unsigned char state;
	unsigned char attackAnimation;
	unsigned char isDead;
	special *bullet;
} player;

// aloca e cria um novo player
player* player_create(unsigned char side, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);

// carrega os sprites do personagem baseado no personagem escolhido
sprite* load_sprites(int charsel);

// movimentação do player
void player_move(player *element, char steps, unsigned char traj, unsigned short max_x, unsigned short max_y);

// libera a memoria do player
void player_destroy(player *element);

#endif
