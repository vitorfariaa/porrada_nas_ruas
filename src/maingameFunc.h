#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "streetlib.h"

#define X_S 1280
#define Y_S 320

// funcoes "draw" imprimem os backgrounds do jogo e os "botoes"
void draw_menu(ALLEGRO_FONT *font, int selected_option, ALLEGRO_BITMAP *logo);

void draw_controlMenu(ALLEGRO_BITMAP *logo);

void draw_pauseMenu(ALLEGRO_FONT *font);

void draw_playerSelMenu(ALLEGRO_FONT *font, int selected_playerN, ALLEGRO_BITMAP *logo);

void draw_characSelMenu(ALLEGRO_FONT *font, ALLEGRO_FONT *fontMini, int player1_char, int player2_char, int selected_playerN, ALLEGRO_BITMAP *logo);

void draw_mapSelMenu(ALLEGRO_FONT *font, ALLEGRO_FONT *fontMini, int selected_map, ALLEGRO_BITMAP *logo);

// draw game alem de imprimir o background, imprime os jogadores baseado nas posicoes atuais
void draw_game(ALLEGRO_BITMAP *logo, ALLEGRO_FONT *font, player *player_1, player *player_2, short round, short color);

void draw_round(ALLEGRO_FONT *font, short round);

void draw_ending(ALLEGRO_BITMAP *logo, ALLEGRO_FONT *font, player *player_1, player *player_2);

// funcao de colisao basica entre dois players
unsigned char collision_2D(player *element_first, player *element_second);

// funcao para o computador controlar um player em modo single-player
void ai_control(player *cpu, player *human, short *ai_cooldown);

// funcao para atualizar as posicoes dos players baseados na sua ação atual e posicao
void update_position(player *player_1, player *player_2);
