#include "ataques.h"

void update_attacks(player *player1, player *player2) {
	// diminuindo o cooldown de todos os ataques dos jogadores
    if (player1->punchcool > 0){
        player1->punchcool--;
	}

    if (player2->punchcool > 0){
        player2->punchcool--;
	}

    if (player1->kickcool > 0){
        player1->kickcool--;
	}

    if (player2->kickcool > 0){
        player2->kickcool--;
	}

	if (player1->speccool > 0){
		player1->speccool--;
	}

	if (player2->speccool > 0){
		player2->speccool--;
	}

	// se o player soltou o especial, e o especial ainda nao acertou/caiu fora do mapa, ele ira andar 10 pixels
	if (player1->bullet){
		if(!special_collision(player1, player2)){

			if(player1->bullet->traj == 1)
				player1->bullet->x += 10;
			else
				player1->bullet->x -= 10;

			if (player1->bullet->frame_count >= 15)
				player1->bullet->current_frame = 1;
			else
				player1->bullet->frame_count++;
		}

	}

	if (player2->bullet){
		if(!special_collision(player2, player1)){

			if (player2->bullet->traj == 1)
				player2->bullet->x += 10;
			else
				player2->bullet->x -= 10;

			if (player2->bullet->frame_count >= 15)
				player2->bullet->current_frame = 1;
			else
				player2->bullet->frame_count++;
		}
	}


	// o AttackAnimation dos jogadores é referente ao tempo para o player completar a animacao de ataque ao atacar
    if (player1->control->punch && player1->punchcool == 0) {
        player_punch(player1, player2);
        player1->punchcool = PUNCH_COOLDOWN;
		player1->attackAnimation = 30;
    } else if (player1->control->kick && player1->kickcool == 0) {
        player_kick(player1, player2);
        player1->kickcool = KICK_COOLDOWN;
		player1->attackAnimation = 30;
    } else if (player1->control->special && player1->speccool == 0 && !player1->control->down) {
		player_special(player1, player2);
		player1->speccool = SPEC_COOLDOWN;
		player1->attackAnimation = 30;
	}

    if (player2->control->punch && player2->punchcool == 0) {
        player_punch(player2, player1);
        player2->punchcool = PUNCH_COOLDOWN;
        player2->attackAnimation = 30;
    } else if (player2->control->kick && player2->kickcool == 0) {
        player_kick(player2, player1);
        player2->kickcool = KICK_COOLDOWN;
        player2->attackAnimation = 30;
    } else if (player2->control->special && player2->speccool == 0 && !player2->control->down){
		player_special(player2, player1);
		player2->speccool = SPEC_COOLDOWN;
		player2->attackAnimation = 30;
	}

}

// colisao de ataque leva em consideracao a colisao 2d normal e a face do jogador
unsigned char attack_collision(player *element, player *enemy) {
    if (element->face) {
        if (enemy->x >= element->x) {
			if ((enemy->control->down && element->control->down) || !enemy->control->down)
				if (collision_2D(element, enemy))
					return 1;
        }
    } else {
        if (enemy->x <= element->x) {
			if ((enemy->control->down && element->control->down) || !enemy->control->down)
				if (collision_2D(element, enemy))
					return 1;
        }
    }

    return 0;
}

void player_punch(player *element, player *enemy){

	element->side += 20; // ao socar, hitbox do jogador aumenta em 20

	if (attack_collision(element, enemy)){

		enemy->hp -= 10;

		player_move(enemy, 50, element->face, X_S, Y_S); // knockback para tras do soco

	}

}

void player_kick(player *element, player *enemy){

	element->side += 30; // ao chutar, hitbox do jogador aumenta em 30

	if (attack_collision(element, enemy)){

		enemy->hp -= 15;

		player_move(enemy, 70, 2, X_S, Y_S);
		player_move(enemy, 70, element->face, X_S, Y_S); // knockback para tras e para cima do chute
	}
}

// aloca o ataque especial do player
void player_special(player* element, player *enemy){

	element->bullet = (special*)malloc(sizeof(special));
	element->bullet->traj = element->face;
	element->bullet->current_frame = 0;
	element->bullet->y = element->y - 15;

	if (element->face)
		element->bullet->x = element->x + element->side/2;

	else
		element->bullet->x = element->x - element->side/2;

}

int special_collision(player *element, player *enemy){

	// se o ataque especial acertar o jogador, dá dano, knockback e depois o especial é limpo
	if ((element->bullet->x <= enemy->x + enemy->side / 2) && (element->bullet->x >= enemy->x - enemy->side / 2)){
		if ((element->bullet->y <= enemy->y + enemy->side / 2) && (element->bullet->y >= enemy->y - enemy->side / 2)){

			element->bullet->current_frame = 2;
			enemy->hp -= 40;
			player_move(enemy, 70, element->face, X_S, Y_S);

			free(element->bullet);
			element->bullet = NULL;

			return 1;
		}
	}

	// se o ataque especial saiu para fora do mapa, ele é limpo
	if (element->bullet->x >= X_S || element->bullet->x <= 0){
		free(element->bullet);
		element->bullet = NULL;
		return 1;
	}

	return 0;
}

