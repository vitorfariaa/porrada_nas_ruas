#include "maingameFunc.h"

void draw_menu(ALLEGRO_FONT *font, int selected_option, ALLEGRO_BITMAP *logo) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(logo, 0, 0, 0);

	// botao atualmente selecionado fica branco
    if (selected_option == 0) {
        al_draw_text(font, al_map_rgb(255, 255, 255), 620, 180, ALLEGRO_ALIGN_CENTRE, "Start Game");
        al_draw_text(font, al_map_rgb(255, 0, 0), 620, 215, ALLEGRO_ALIGN_CENTRE, "Controls");
        al_draw_text(font, al_map_rgb(255, 0, 0), 620, 250, ALLEGRO_ALIGN_CENTRE, "Exit");
    }
        else if (selected_option == 1){
        al_draw_text(font, al_map_rgb(255, 0, 0), 620, 180, ALLEGRO_ALIGN_CENTRE, "Start Game");
        al_draw_text(font, al_map_rgb(255, 255, 255), 620, 215, ALLEGRO_ALIGN_CENTRE, "Controls");
        al_draw_text(font, al_map_rgb(255, 0, 0), 620, 250, ALLEGRO_ALIGN_CENTRE, "Exit");
    }
        else{
        al_draw_text(font, al_map_rgb(255, 0, 0), 620, 180, ALLEGRO_ALIGN_CENTRE, "Start Game");
        al_draw_text(font, al_map_rgb(255, 0, 0), 620, 215, ALLEGRO_ALIGN_CENTRE, "Controls");
        al_draw_text(font, al_map_rgb(255, 255, 255), 620, 250, ALLEGRO_ALIGN_CENTRE, "Exit");
        }
    al_flip_display();
}

void draw_playerSelMenu(ALLEGRO_FONT *font, int selected_playerN, ALLEGRO_BITMAP *logo){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(logo, 0, 0, 0);

	if (selected_playerN == 0){
		al_draw_text(font, al_map_rgb(255, 255, 255), 620, 120, ALLEGRO_ALIGN_CENTRE, "Single-Player");
		al_draw_text(font, al_map_rgb(255, 0, 0), 620, 155, ALLEGRO_ALIGN_CENTRE, "Multi-Player");
	}

	else{
		al_draw_text(font, al_map_rgb(255, 0, 0), 620, 120, ALLEGRO_ALIGN_CENTRE, "Single-Player");
		al_draw_text(font, al_map_rgb(255, 255, 255), 620, 155, ALLEGRO_ALIGN_CENTRE, "Multi-Player");
	}

	al_flip_display();
}

void draw_characSelMenu(ALLEGRO_FONT *font, ALLEGRO_FONT *fontMini, int player1_char, int player2_char, int selected_playerN, ALLEGRO_BITMAP *logo){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(logo, 0, 0, 0);

	al_draw_text(font, al_map_rgb(255, 0, 0), 490, 200, ALLEGRO_ALIGN_LEFT, "Player 1:");
	al_draw_text(font, al_map_rgb(0, 0, 255), 490, 235, ALLEGRO_ALIGN_LEFT, "Player 2:");

	char vetorPersonagens[4][10] = {"Geki", "Ken", "Ryu", "Chun"};
	short vetorCoordenadas[4] = {396,520,643,763};

	if (selected_playerN == 0){
		al_draw_text(font, al_map_rgb(255, 0, 0), 660, 200, ALLEGRO_ALIGN_LEFT, vetorPersonagens[player1_char]);
		al_draw_rectangle(vetorCoordenadas[player1_char], 76, vetorCoordenadas[player1_char] + 98, 164, al_map_rgb(255,0,0), 4.0);

		al_draw_text(font, al_map_rgb(0, 0, 255), 660, 235, ALLEGRO_ALIGN_LEFT, vetorPersonagens[(player1_char+1)%4]);
		al_draw_rectangle(vetorCoordenadas[player2_char], 76, vetorCoordenadas[player2_char] + 98, 164, al_map_rgb(0,0,255), 4.0);
	}

	else if (selected_playerN == 1){
		al_draw_text(font, al_map_rgb(255, 0, 0), 660, 200, ALLEGRO_ALIGN_LEFT, vetorPersonagens[player1_char]);
		al_draw_rectangle(vetorCoordenadas[player1_char], 76, vetorCoordenadas[player1_char] + 98, 164, al_map_rgb(255,0,0), 4.0);

		al_draw_text(font, al_map_rgb(0, 0, 255), 660, 235, ALLEGRO_ALIGN_LEFT, "Esperando...");
	}

	else{
		al_draw_text(font, al_map_rgb(255, 0, 0), 660, 200, ALLEGRO_ALIGN_LEFT, vetorPersonagens[player1_char]);
		al_draw_rectangle(vetorCoordenadas[player1_char], 76, vetorCoordenadas[player1_char] + 98, 164, al_map_rgb(255,0,0), 4.0);

		al_draw_text(font, al_map_rgb(0, 0, 255), 660, 235, ALLEGRO_ALIGN_LEFT, vetorPersonagens[player2_char]);
		al_draw_rectangle(vetorCoordenadas[player2_char], 76, vetorCoordenadas[player2_char] + 98, 164, al_map_rgb(0,0,255), 4.0);
	}

	al_flip_display();
}

void draw_mapSelMenu(ALLEGRO_FONT *font, ALLEGRO_FONT *fontMini, int selected_map, ALLEGRO_BITMAP *logo){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(logo, 0, 0, 0);

	char vetorMapas[2][25] = {"Floresta Negra", "Centro Politecnico"};
	short vetorCoordenadas[2] = {247, 632};

	al_draw_text(fontMini, al_map_rgb(255, 255, 255), 610, 260, ALLEGRO_ALIGN_CENTRE, "Mapa:");
	al_draw_text(font, al_map_rgb(255, 0, 0), 610, 280, ALLEGRO_ALIGN_CENTRE, vetorMapas[selected_map]);
	al_draw_rectangle(vetorCoordenadas[selected_map], 78, vetorCoordenadas[selected_map] + 333, 256, al_map_rgb(255,255,255), 4.0);

	al_flip_display();
}
	

void draw_game(ALLEGRO_BITMAP *logo, ALLEGRO_FONT *font, player *player_1, player *player_2, short round, short color){

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(logo, 0, 0, 0);

	char player1HP[4]; 
	sprintf(player1HP, "%d", player_1->hp);

	char player2HP[4];
	sprintf(player2HP, "%d", player_2->hp);

	char Sround[2];
	sprintf(Sround, "%d", round);

	al_draw_text(font, al_map_rgb(255, 0, 0), 20, 20, ALLEGRO_ALIGN_LEFT, "Player 1 Health: ");
	al_draw_text(font, al_map_rgb(255, 0, 0), 320, 20, ALLEGRO_ALIGN_CENTRE, player1HP);

	if(player_1->wins)
		al_draw_text(font, al_map_rgb(0, 255, 0), 20, 60, ALLEGRO_ALIGN_LEFT, "x");

	al_draw_text(font, al_map_rgb(255, 0, 0), 1200, 20, ALLEGRO_ALIGN_RIGHT, "Player 2 Health: ");
	al_draw_text(font, al_map_rgb(255, 0, 0), 1230, 20, ALLEGRO_ALIGN_CENTRE, player2HP);

	if (player_2->wins)
		al_draw_text(font, al_map_rgb(0, 255, 0), 1230, 60, ALLEGRO_ALIGN_LEFT, "x");

	al_draw_text(font, al_map_rgb(color, color, color), 670, 20, ALLEGRO_ALIGN_RIGHT, "Round");
	al_draw_text(font, al_map_rgb(color, color, color), 700, 20, ALLEGRO_ALIGN_RIGHT, Sround);

	// desenhar sprite do player 1 baseado na posicao e acao atual
	ALLEGRO_BITMAP *sprite1;
	if (player_1->isDead) {
		sprite1 = player_1->sprites->isDead[0];
	} else{ 
		if (player_1->state == 0) {  // idle
			sprite1 = player_1->sprites->idle[player_1->sprites->current_frame];
		} else if (player_1->state == 1) {  // andando
			sprite1 = player_1->sprites->walk[player_1->sprites->current_frame];
		} else if (player_1->state == 2) {  // pulando
			sprite1 = player_1->sprites->jump[player_1->sprites->current_frame];
		} else if (player_1->state == 3) {  // chutando
			sprite1 = player_1->sprites->kick[player_1->sprites->current_frame];
		} else if (player_1->state == 4) {  // socando
			sprite1 = player_1->sprites->punch[player_1->sprites->current_frame];
		} else if (player_1->state == 5) {  // agachado
			sprite1 = player_1->sprites->down[player_1->sprites->current_frame];
		} else if (player_1->state == 6) { // chute abaixado
			sprite1 = player_1->sprites->kickDown[player_1->sprites->current_frame];
		} else if (player_1->state == 7) { // soco abaixado
			sprite1 = player_1->sprites->punchDown[player_1->sprites->current_frame];
		} else if (player_1->state == 8) { // ataque especial
			sprite1 = player_1->sprites->specialAttack[player_1->sprites->current_frame];
		}
	}
	// espelhar a imagem do player de acordo com o lado que esta olhando
    int flags1 = player_1->face ? 0 : ALLEGRO_FLIP_HORIZONTAL;
    al_draw_bitmap(sprite1, player_1->x - player_1->side / 2, player_1->y - player_1->side / 2, flags1);

	// desenhar ataque especial do player 1 se tiver
	if (player_1->bullet){
		ALLEGRO_BITMAP *specialSprite = player_1->sprites->specialSprite[player_1->bullet->current_frame];
		al_draw_bitmap(specialSprite, player_1->bullet->x, player_1->bullet->y, flags1);
	}

    // desenhar sprite do player 2 baseado na posicao e acao atual
    ALLEGRO_BITMAP *sprite2;
	if (player_2->isDead){
		sprite2 = player_2->sprites->isDead[0];
	}
	else{
		if (player_2->state == 0) {  // idle
			sprite2 = player_2->sprites->idle[player_2->sprites->current_frame];
		} else if (player_2->state == 1) {  // andando
			sprite2 = player_2->sprites->walk[player_2->sprites->current_frame];
		} else if (player_2->state == 2) {  // pulando
			sprite2 = player_2->sprites->jump[player_2->sprites->current_frame];
		} else if (player_2->state == 3) {  // chutando
			sprite2 = player_2->sprites->kick[player_2->sprites->current_frame];
		} else if (player_2->state == 4) {  // socando
			sprite2 = player_2->sprites->punch[player_2->sprites->current_frame];
		} else if (player_2->state == 5) {  // abaixado
			sprite2 = player_2->sprites->down[player_2->sprites->current_frame];
		} else if (player_2->state == 6) {  // chute abaixado
			sprite2 = player_2->sprites->kickDown[player_2->sprites->current_frame];
		} else if (player_2->state == 7) {  // soco abaixado
			sprite2 = player_2->sprites->punchDown[player_2->sprites->current_frame];
		} else if (player_2->state == 8) {  // ataque especial
			sprite2 = player_2->sprites->specialAttack[player_2->sprites->current_frame];
		}
	}
	// espelhar imagem do jogador baseado em que lado ele esta olhando
    int flags2 = player_2->face ? 0 : ALLEGRO_FLIP_HORIZONTAL;
    al_draw_bitmap(sprite2, player_2->x - player_2->side / 2, player_2->y - player_2->side / 2, flags2);

	// desenhar o ataque especial do player2, se tiver
	if (player_2->bullet){
		ALLEGRO_BITMAP *specialSprite = player_2->sprites->specialSprite[player_2->bullet->current_frame];
		al_draw_bitmap(specialSprite, player_2->bullet->x, player_2->bullet->y, flags2);
	}

	al_flip_display();
}

// "round X fight!"
void draw_round(ALLEGRO_FONT *font, short round) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    char round_message[20];
    sprintf(round_message, "ROUND %d", round);
    al_draw_text(font, al_map_rgb(255, 255, 0), 640, 120, ALLEGRO_ALIGN_CENTRE, round_message);
    al_draw_text(font, al_map_rgb(255, 0, 0), 640, 160, ALLEGRO_ALIGN_CENTRE, "FIGHT!");
    al_flip_display();
}

// players sao passados como parametro para desenhar o frame de derrota/vitoria de cada personagem
void draw_ending(ALLEGRO_BITMAP *logo, ALLEGRO_FONT *font, player *player_1, player *player_2){

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(logo, 0, 0, 0);

	if (player_1->wins == 2){
		al_draw_text(font, al_map_rgb(255, 0, 0), 640, 160, ALLEGRO_ALIGN_CENTRE, "Player 1 Venceu, pressione enter para continuar");
		al_draw_bitmap(player_2->sprites->isDead[0], 660, 275, 0);
		al_draw_bitmap(player_1->sprites->isWinner[0], 580, 200, 0);
	}

	else{
		al_draw_text(font, al_map_rgb(255, 0, 0), 640, 160, ALLEGRO_ALIGN_CENTRE, "Player 2 Venceu, pressione enter para continuar");
		al_draw_bitmap(player_1->sprites->isDead[0], 660, 275, 0);
		al_draw_bitmap(player_2->sprites->isWinner[0], 580, 200, 0);
	}

	al_flip_display();
}


void draw_controlMenu(ALLEGRO_BITMAP *logo){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(logo, 0, 0, 0);
        al_flip_display();
}

void draw_pauseMenu(ALLEGRO_FONT *font){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font, al_map_rgb(255, 255, 0), 640, 120, ALLEGRO_ALIGN_CENTRE, "Jogo Pausado");
	al_draw_text(font, al_map_rgb(255, 255, 0), 640, 160, ALLEGRO_ALIGN_CENTRE, "Pressione enter para retomar");
	al_flip_display();
}

// colisao simples entre dois objetos/personagens baseado no Agressive Squares
unsigned char collision_2D(player *element_first, player *element_second){

        if ((((element_first->y+element_first->side/2 >= element_second->y-element_second->side/2) && (element_second->y-element_second->side/2 >= element_first->y-element_first->side/2)) ||
                ((element_second->y+element_second->side/2 >= element_first->y-element_first->side/2) && (element_first->y-element_first->side/2 >= element_second->y-element_second->side/2))) &&
                (((element_first->x+element_first->side/2 >= element_second->x-element_second->side/2) && (element_second->x-element_second->side/2 >= element_first->x-element_first->side/2)) ||
                ((element_second->x+element_second->side/2 >= element_first->x-element_first->side/2) && (element_first->x-element_first->side/2 >= element_second->x-element_second->side/2))))
                return 1;
        else
                return 0;
}

void ai_control(player *cpu, player *human, short *ai_cooldown) {
	srand(time(NULL)); // seed para sortear ataque aleatorio

	if(*ai_cooldown)
		(*ai_cooldown)--; // cooldown do ataque da IA

	if (!human->control->down)
		cpu->control->down = 0; // se player estiver de pé, CPU fica de pé

	// CPU segue o player até ficar a 50 pixeis de distancia, para assim comecar a atacar
    if (human->x - cpu->x > 50) {
		cpu->control->left = 0;
        cpu->control->right = 1;
    } else if (cpu->x - human->x > 50) {
		cpu->control->right = 0;
        cpu->control->left = 1;;
    } else{
		cpu->control->right = 0;
		cpu->control->left = 0;
	}

    if (abs(cpu->x - human->x) <= 50 && !(*ai_cooldown)) {
		if (human->control->down)
			cpu->control->down = 1;

		// cpu sorteia uma ataque aleatorio a cada 90 frames (1,5s)
		int random_attack = (rand() % 3) + 1;

		if (random_attack == 1)
			joystick_punch(cpu->control);

		else if (random_attack == 2)
			joystick_kick(cpu->control);

		else
			joystick_special(cpu->control);

		*ai_cooldown = 90;
    } 
	else {
        cpu->control->punch = 0; // para parar o ataque continuo se CPU esta longe ou em cooldown
		cpu->control->kick = 0;
		cpu->control->special = 0;
    }
}

void update_position(player *player_1, player *player_2){
	float acelGrav = 0.5; // gravidade do jogo
	short forcaPulo = -12; // forca de impulso do pulo
	short chao = 220; // coordenada do chao
	short step1, step2; // tamanho dos passos de cada player

	if (player_1->control->down) // se o player tiver abaixado, passo tem tamanho 1
		step1 = 1;
	else
		step1 = 8; // se nao, tem tamanho 8

	if (player_2->control->down)
		step2 = 1;
	else
		step2 = 8;


	// reduzindo o cooldown das animacoes de ataque
	if (player_1->attackAnimation)
		player_1->attackAnimation--;

	if (player_2->attackAnimation)
		player_2->attackAnimation--;

	if (player_1->y < chao){
	    player_1->veloY += acelGrav;
		if (!player_1->attackAnimation)
			player_1->state = 2; // animacao de pulo
	}
	else{
	    player_1->veloY = 0;
		player_1->y = chao;
		if (!player_1->control->left && !player_1->control->right && !player_1->control->up && !player_1->attackAnimation) {
	        player_1->state = 0; // estado idle
		}
	}

	if (player_1->control->up && player_1->y == chao){
	    player_1->veloY = forcaPulo;
		if (!player_1->attackAnimation)
			player_1->state = 2; // pulo
	}
	
	player_move(player_1, player_1->veloY, 3, X_S, Y_S); // forca de gravidade puxando player para baixo

	if (player_1->control->left){
	    player_move(player_1, step1, 0, X_S, Y_S);
		player_1->face = 0; // se player for para esquerda, sua face estara voltada a esquerda

		if (player_1->y == chao && !player_1->attackAnimation)
			player_1->state = 1; // outras animacoes nao interrompem animacao de ataque se o attackAnimation estiver ON
	}

	if (player_1->control->right){
	    player_move(player_1, step1, 1, X_S, Y_S);
		player_1->face = 1; // se player for para direita, sua face estara voltada a direita

		if (player_1->y == chao && !player_1->attackAnimation)
			player_1->state = 1;
	}

	if (player_1->control->kick) {
	    player_1->state = 3;  // estado de chute
	}

	if (player_1->control->punch) {
	    player_1->state = 4;  // estado de soco
	}

	if (player_1->control->down && !player_1->attackAnimation){
		player_1->state = 5;
		player_1->y = 250; // quando player se abaixa, o "Y" diminui para condizer com os sprites
	}

	if (player_1->control->down && player_1->attackAnimation){
        player_1->y = 250;

		if (player_1->control->kick)
			player_1->state = 6; // chute abaixado

        if (player_1->control->punch)
            player_1->state = 7; // soco abaixado
    }

	if (player_1->control->special && !player_1->speccool && !player_1->control->down){
		player_1->state = 8; // ataque especial
	}


	// TODAS AS FUNCOES DE CIMA SO QUE AGORA PARA PLAYER 2
	if (player_2->y < chao){
		player_2->veloY += acelGrav;
		if (!player_2->attackAnimation)
			player_2->state = 2;
	}
	else{
		player_2->veloY = 0;
		player_2->y = chao;
		if (!player_2->control->left && !player_2->control->right && !player_2->control->up && !player_2->attackAnimation){
	        player_2->state = 0; // estado idle
	    }
	}

	if (player_2->control->up && player_2->y == chao){
		player_2->veloY = forcaPulo;
		if (!player_2->attackAnimation)
			player_2->state = 2; // estado pulo
	}

	player_move(player_2, player_2->veloY, 3, X_S, Y_S);

	if (player_2->control->left){
	    player_move(player_2, step2, 0, X_S, Y_S);
		player_2->face = 0;

		if (player_2->y == chao && !player_2->attackAnimation)
			player_2->state = 1; // estado andando
	}

	if (player_2->control->right){
	    player_move(player_2, step2, 1, X_S, Y_S);
		player_2->face = 1;

		if (player_2->y == chao && !player_2->attackAnimation)
			player_2->state = 1;
	}

	if (player_2->control->kick) {
	    player_2->state = 3;  // estado de chute
	}

	if (player_2->control->punch) {
	    player_2->state = 4;  // estado de soco
	}

	if (player_2->control->down && !player_2->attackAnimation){
		player_2->state = 5;
		player_2->y = 250;
	}

	if (player_2->control->down && player_2->attackAnimation){
		player_2->y = 250;

		if (player_2->control->kick)
			player_2->state = 6; // estado chute abaixado

		if (player_2->control->punch)
			player_2->state = 7; // estado soco abaixado
	}

	if (player_2->control->special && !player_2->speccool && !player_2->control->down){
		player_2->state = 8; // estado ataque especial
	}


	// funcoes abaixo servem para atualizar os frames atuais das acoes dos jogadores
	player_1->sprites->frame_count++;

    if (player_1->sprites->frame_count >= 10) {  // alterar o frame a cada 10 atualizações
        player_1->sprites->current_frame++;
        player_1->sprites->frame_count = 0;
    }
    // limitar o frame atual baseado na quantidade de sprites de cada estado
    if (player_1->state == 0) {  // idle
        player_1->sprites->current_frame %= 1;
    } else if (player_1->state == 1) {  // andando
        player_1->sprites->current_frame %= 8;
    } else if (player_1->state == 2) {  // pulando
        player_1->sprites->current_frame %= 7;
    } else if (player_1->state == 3) {  // chutando
		player_1->sprites->current_frame %= 3;	
    } else if (player_1->state == 4) {// socando
		player_1->sprites->current_frame %= 4;
	} else if (player_1->state == 5) { // abaixado
		player_1->sprites->current_frame %= 1;
	} else if (player_1->state == 6) { // chute abaixado
        player_1->sprites->current_frame %= 3;
    } else if (player_1->state == 7) { // soco abaixado
        player_1->sprites->current_frame %= 3;
    } else if (player_1->state == 8) { // ataque especial
		player_1->sprites->current_frame %= 3;
	}

	// MESMAS FUNCOES DA PARTE DE CIMA SO QUE PARA PLAYER 2
	player_2->sprites->frame_count++;
    if (player_2->sprites->frame_count >= 10) {
        player_2->sprites->current_frame++;
        player_2->sprites->frame_count = 0;
    }

    if (player_2->state == 0) {
        player_2->sprites->current_frame %= 1;
    } else if (player_2->state == 1) {
        player_2->sprites->current_frame %= 8;
    } else if (player_2->state == 2) {
        player_2->sprites->current_frame %= 7;
    } else if (player_2->state == 3) {
        player_2->sprites->current_frame %= 3;
    } else if (player_2->state == 4) {
		player_2->sprites->current_frame %= 4;
	} else if (player_2->state == 5) {
		player_2->sprites->current_frame %= 1;
	} else if (player_2->state == 6) {
		player_2->sprites->current_frame %= 3;
	} else if (player_2->state == 7) {
		player_2->sprites->current_frame %= 3;
	} else if (player_2->state == 8) {
		player_2->sprites->current_frame %= 3;
	}
}
