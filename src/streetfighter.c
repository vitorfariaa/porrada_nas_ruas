#include "maingameFunc.h"
#include "streetlib.h"

#include "ataques.h"

int main(){
	// iniciar processos do allegro
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_install_keyboard();

	// definir metricas importantes para o jogo
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_FONT* font = al_load_ttf_font("assets/font.ttf", 32, 0);
	ALLEGRO_FONT* fontMini = al_load_ttf_font("assets/font.ttf", 20, 0);
	ALLEGRO_DISPLAY* disp = al_create_display(X_S, Y_S);

	// importar os backgrounds da pasta "backgrounds"
	ALLEGRO_BITMAP *logo = al_load_bitmap("assets/backgrounds/mainMenu.bmp");
	ALLEGRO_BITMAP *controlLogo = al_load_bitmap("assets/backgrounds/mainMenuControls.bmp");
	ALLEGRO_BITMAP *map1 = al_load_bitmap("assets/backgrounds/BackG1.bmp");
	ALLEGRO_BITMAP *map2 = al_load_bitmap("assets/backgrounds/BackG2.bmp");
	ALLEGRO_BITMAP *mapSelLogo = al_load_bitmap("assets/backgrounds/mapSelection.bmp");
	ALLEGRO_BITMAP *playerSelLogo = al_load_bitmap("assets/backgrounds/PlayerNumSel.bmp");
	ALLEGRO_BITMAP *characSelLogo = al_load_bitmap("assets/backgrounds/persoSelect.bmp");

	// registrar o teclado, display e timer
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	// alocacao dos players
	player* player_1 = player_create(75, 1, 100, 200, X_S, Y_S);
	if (!player_1)
		return 1;

	player* player_2 = player_create(75, 0, 1180, 200, X_S, Y_S);
	if (!player_2)
		return 1;

	ALLEGRO_EVENT event;

	// booleanos importantes para o jogo
	short in_control = 0;
	short in_player_sel = 0;
	short in_charac_sel = 0;
	short in_map_sel = 0;
	short in_game = 0;
	short in_pause = 0;
	short map = 0;
	short ending = 0;

	// indices importantes para o jogo
	short selected_option = 0;
	short selected_playerN = 0;
	short selected_map = 0;

	short ai_cooldown = 0;
	short single_player = 0;

	short player1_char = 0;
	short player2_char = 1;

	short round = 1;
	short show_round = 0;

	short fechou = 0;
	short redraw = 1;

	// comeco do jogo
	al_start_timer(timer);
	while(!fechou){
		al_wait_for_event(queue, &event);

		// eventos que acontecem a cada tick do relogio
		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = 1; // tela irá atualizar independente do motivo

			if (in_game && !in_pause) { // se estiver em jogo, serao atualizados os ataques, posicoes e caracteristicas dos players baseado no round atual

				// se algum dos players morre, aparece o frame dele "derrotado" por 1,5s
				if (player_1->isDead){
					player_1->isDead--;

					if (player_1->isDead == 1){
						player_1->x = 100;
						player_1->face = 1;
						player_1->state = 0;

						player_2->x = 1180;
						player_2->face = 0;
						player_2->state = 0;
					}
				}

				else if (player_2->isDead){
					player_2->isDead--;

					if (player_2->isDead == 1){
						player_1->x = 100;
						player_1->face = 1;
						player_1->state = 0;

						player_2->x = 1180;
						player_2->face = 0;
						player_2->state = 0;
					}
				}

				else if (show_round && (!player_1->isDead && !player_2->isDead))
					show_round--;

				else{
					// hitbox dos players voltam ao normal (para caso tivessem dado golpes)
					player_1->side = 75;
					player_2->side = 75;

					// funcao para computador controlar o player no modo single player
					if (single_player)
						ai_control(player_2, player_1, &ai_cooldown);

					// atualizar as posicoes e ataques
					update_position(player_1, player_2);
					update_attacks(player_1, player_2);
					
					if (player_1->hp <= 0){
						player_1->isDead = 90;
						player_1->y = 275; 
						player_2->wins++;
						// jogo acabou
						if (player_2->wins == 2){
							round = 1;
							in_game = 0;
							ending = 1;
							selected_playerN = 0;

							player_1->isDead = 0;
							player_2->isDead = 0;

							joystick_destroy(player_1->control);

							joystick_destroy(player_2->control);

							player_1->control = joystick_create();

							player_2->control = joystick_create();
						}
						else{
							round++;
							show_round = 120;
						}
						
						player_1->hp = 100;
						player_1->kickcool = 0;
						player_1->punchcool = 0;
						player_1->speccool = 0;

						player_2->hp = 100;
						player_2->kickcool = 0;
						player_2->punchcool = 0;
						player_2->speccool = 0;
					}

					if (player_2->hp <= 0){
						player_2->isDead = 90;
						player_2->y = 275;
						player_1->wins++;
						// jogo acabou
						if (player_1->wins == 2){
							round = 1;
							in_game = 0;
							ending = 1;
							selected_playerN = 0;

							player_1->isDead = 0;
							player_2->isDead = 0;

							joystick_destroy(player_1->control);

							joystick_destroy(player_2->control);

							player_1->control = joystick_create();

							player_2->control = joystick_create();
						}
						else{
							round++;
							show_round = 120;
						}
							
						player_1->hp = 100;
						player_1->kickcool = 0;
						player_1->punchcool = 0;
						player_1->speccool = 0;

						player_2->hp = 100;
						player_2->kickcool = 0;
						player_2->punchcool = 0;
						player_2->speccool = 0;

					}
				}
			}
		}

		// escolha dos backgrounds de acordo com os booleanos
		if (redraw){
			if (in_control)
				draw_controlMenu(controlLogo);
			
			else if (show_round && !player_1->isDead && !player_2->isDead)
				draw_round(font, round);

			else if (in_player_sel)
				draw_playerSelMenu(font, selected_playerN, playerSelLogo);

			else if (in_charac_sel)
				draw_characSelMenu(font, fontMini, player1_char, player2_char, selected_playerN, characSelLogo);

			else if (in_map_sel)
				draw_mapSelMenu(font, fontMini, selected_map, mapSelLogo);

			else if (in_pause)
				draw_pauseMenu(font);

			else if (in_game && !map)
				draw_game(map1, font, player_1, player_2, round, 255);

			else if (in_game && map)
				draw_game(map2, font, player_1, player_2, round, 0);

			else if (ending && !map)
				draw_ending(map1, font, player_1, player_2);

			else if (ending && map)
				draw_ending(map2, font, player_1, player_2);

			else
				draw_menu(font, selected_option, logo);
			redraw = 0;
		}

		// jogo fechado pelo "x"
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			fechou = 1;

		// input da movimentacao dos players
		if ((in_game) && (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP) && (!in_pause)){

			switch(event.keyboard.keycode){

				case ALLEGRO_KEY_A: joystick_left(player_1->control); break;

				case ALLEGRO_KEY_D: joystick_right(player_1->control); break;

				case ALLEGRO_KEY_S: joystick_down(player_1->control); break;

                case ALLEGRO_KEY_W: joystick_up(player_1->control); break;

				case ALLEGRO_KEY_E: joystick_punch(player_1->control); break;

				case ALLEGRO_KEY_R: joystick_kick(player_1->control); break;

				case ALLEGRO_KEY_T: joystick_special(player_1->control); break;

				case ALLEGRO_KEY_ESCAPE: in_pause = 1;
			}
			
			if (!single_player){

				switch(event.keyboard.keycode){

					case ALLEGRO_KEY_LEFT: joystick_left(player_2->control); break;

					case ALLEGRO_KEY_RIGHT: joystick_right(player_2->control); break;

					case ALLEGRO_KEY_DOWN: joystick_down(player_2->control); break;

					case ALLEGRO_KEY_UP: joystick_up(player_2->control); break;

					case ALLEGRO_KEY_P: joystick_punch(player_2->control); break;

					case ALLEGRO_KEY_O: joystick_kick(player_2->control); break;

					case ALLEGRO_KEY_I: joystick_special(player_2->control); break;

				}
			}	
			
		} // input dos botoes de "menu"
		
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
	
			if (in_control){ // menu dos controles
				if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
					in_control = 0;
			}

			else if (in_pause){ // pause no meio do jogo
				if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
					in_pause = 0;
			}

			else if (ending){ // fim da partida
				if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
					ending = 0;
					player_1->wins = 0;
					player_2->wins = 0;
					
					player_1->x = 100;
					player_1->face = 1;

					player_2->x = 1180;
					player_2->face = 0;

				}
			}

			else if (in_map_sel){ // selecao de mapas
				switch (event.keyboard.keycode){
					case ALLEGRO_KEY_RIGHT:
						if (selected_map == 0)
							selected_map = 1;
						else
							selected_map = 0;
						break;

					case ALLEGRO_KEY_LEFT:
						if (selected_map == 0)
							selected_map = 1;
						else
							selected_map = 0;
						break;

					case ALLEGRO_KEY_ENTER:
						in_map_sel = 0;

						if (selected_map == 0){
							in_game = 1;
							show_round = 120;
							map = 0;
						}
						else{
							in_game = 1;
							show_round = 120;
							map = 1;
						}

						break;
				}
			}


			else if (in_charac_sel){ // selecao dos personagens
				switch (event.keyboard.keycode) {
					case ALLEGRO_KEY_LEFT:
						if (selected_playerN == 0) { // modo single-player. Computador sempre escolhe um personagem depois do escolhido pelo jogador
							player1_char = (player1_char - 1 + 4) % 4;
							player2_char = (player1_char + 1) % 4;
						} 
						else{ // modo multi-player
							if (selected_playerN == 1) {

								player1_char = (player1_char - 1 + 4) % 4;

								player2_char = (player1_char + 1) % 4;

							} 
							else{
								do {
									player2_char = (player2_char - 1 + 4) % 4;

								} while (player2_char == player1_char);
							}
						}
					break;

					case ALLEGRO_KEY_RIGHT:
						if (selected_playerN == 0) { // modo single-player
							player1_char = (player1_char + 1) % 4;
							player2_char = (player1_char + 1) % 4;
						} 
						else{ // modo multi-player

							if (selected_playerN == 1) {

								player1_char = (player1_char + 1) % 4;

								player2_char = (player1_char + 1) % 4;

							} 
							else{
								do {
									player2_char = (player2_char + 1) % 4;
								} while (player2_char == player1_char);
							}
						}
					break;

					case ALLEGRO_KEY_ENTER:
						
						single_player = (selected_playerN == 0);	

						if (selected_playerN == 0){ // modo single-player
							player2_char = (player1_char + 1) % 4;
							in_charac_sel = 0;
							in_map_sel = 1;

							if (player_1->sprites)
								free(player_1->sprites);

							if (player_2->sprites)
								free(player_2->sprites);


							player_1->sprites = load_sprites(player1_char);
							player_2->sprites = load_sprites(player2_char);
						} 
						else{
							if (selected_playerN == 1)
								selected_playerN = 2; // deixa o jogador 2 escolher o personagem
							else {
								in_charac_sel = 0;
								in_map_sel = 1;

								if (player_1->sprites)
									free(player_1->sprites);

								if (player_2->sprites)
									free(player_2->sprites);

								player_1->sprites = load_sprites(player1_char);
								player_2->sprites = load_sprites(player2_char);
							}
						}
					break;
				}
			}

			else if (in_player_sel){ // single player ou multi player
				switch(event.keyboard.keycode){
					case ALLEGRO_KEY_UP:
						if (selected_playerN == 0)
							selected_playerN = 1;
						else
							selected_playerN = 0;
						break;
					
					case ALLEGRO_KEY_DOWN:
						if (selected_playerN == 0)
							selected_playerN = 1;
						else
							selected_playerN = 0;
						break;

					case ALLEGRO_KEY_ENTER:
						in_charac_sel = 1;
						in_player_sel = 0;
						break;
				}
			}					
			
			else{ // menu padrao (start game, controls e exit)
				switch (event.keyboard.keycode) {
					case ALLEGRO_KEY_UP:
						if (selected_option == 0)
							selected_option = 2;
						else
							selected_option--;
						break;

					case ALLEGRO_KEY_DOWN:
						if (selected_option == 2)
							selected_option = 0;
						else
							selected_option++;
						break;

					case ALLEGRO_KEY_ENTER:

						if (selected_option == 0)
							in_player_sel = 1;

						else if (selected_option == 1)
							in_control = 1;
						
						else if (selected_option == 2)
							fechou = 1; // se exit, o jogo fecha simplesmente

						break;
				}
            }

		}
	}

	// limpeza de toda memoria utilizada pelo programa
	al_destroy_font(font);
    al_destroy_font(fontMini);
    al_destroy_bitmap(logo);
    al_destroy_bitmap(controlLogo);
    al_destroy_bitmap(map1);
    al_destroy_bitmap(map2);
    al_destroy_bitmap(mapSelLogo);
    al_destroy_bitmap(playerSelLogo);
    al_destroy_bitmap(characSelLogo);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    player_destroy(player_1);
    player_destroy(player_2);

	return 0;
}
