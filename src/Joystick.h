#ifndef __JOYSTICK__ 																									
#define __JOYSTICK__																								

// struct do joystick (comandos dos players)
typedef struct {																								
	unsigned char right;
	unsigned char left;
	unsigned char up;
	unsigned char down;

	unsigned char punch;
	unsigned char kick;
	unsigned char special;
} joystick;																															
// aloca e cria um joystick
joystick* joystick_create();																							

// libera memoria de um joystick
void joystick_destroy(joystick *element);	

// ordem para movimentar player a direita
void joystick_right(joystick *element);

// ordem para movimentar player a esquerda
void joystick_left(joystick *element);

// ordem para movimentar player para cima/pulo
void joystick_up(joystick *element);

// ordem para movimentar player para baixo/agachar
void joystick_down(joystick *element);

// ordem para player dar um soco
void joystick_punch(joystick *element);

// ordem para player dar um chute
void joystick_kick(joystick *element);

// ordem para player soltar o ataque especial
void joystick_special(joystick *element);

#endif																												
