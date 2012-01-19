/*
 * game.h
 *
 *  Created on: 10 janv. 2012
 *      Author: redsuser
 */

#ifndef GAME_H_
#define GAME_H_

#define nbShotsMax 512
#define EDGE_EAST LCD_MAX_X-4
#define EDGE_WEST 4


typedef enum {
	false = 0, true = 1
} bool;



typedef struct t_ennemi {
	int enable;
	int x;
	int y;
	unsigned int pv;
} t_ennemi_;

typedef struct t_player {
	int enable;
	int x;
	int y;
	unsigned int lifes;
} t_player_;

typedef struct t_shot {
	int enable;
	int x;
	int y;
	int direction; // Up = -1, down = 1
} t_shot_;


extern t_player_ player[3];
extern t_shot_ shot[nbShotsMax];
extern unsigned int difficulty;
extern unsigned int score;
extern unsigned int speed;


void game_main(void);
void init_ennemi_init(void);
void move_player(void *cookie);
void move_ennemi(void* cookie);
void switch_events(void *cookie);
void show_ennemi(void);
bool detectShitEnable(void);

extern RT_MUTEX mutex_ennemi;

void shots_impacts(void * cookie);


void hp_update_leds(void);


#endif /* GAME_H_ */
