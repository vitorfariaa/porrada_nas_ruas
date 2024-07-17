#include "streetlib.h"
#include "maingameFunc.h"

// defines dos cooldowns
#define PUNCH_COOLDOWN 30
#define KICK_COOLDOWN 40

#define SPEC_COOLDOWN 300

// atualiza no jogo os ataques dados pelos players
void update_attacks(player *player1, player *player2);

// colisao para ataques, mistura a colisao 2D  com a direção que o player esta vendo
unsigned char attack_collision(player *element, player *enemy);

// função de soco
void player_punch(player *element, player *enemy);

// função de chute
void player_kick(player *element, player *enemy);

// função de ataque especial
void player_special(player *element, player *enemy);

// função para carregar a colisão do ataque especial
int special_collision(player *element, player *enemy);
