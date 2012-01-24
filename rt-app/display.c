/*
 * display.c
 *
 *  Created on: 12 janv. 2012
 *      Author: redsuser
 */

#include <linux/module.h>

#include <native/task.h>
#include <native/intr.h>
#include <native/event.h>
#include <native/alarm.h>
#include <native/timer.h>
#include <native/mutex.h>

#include "lcdlib.h"
#include "rt-app-m.h"
#include "xeno-ts.h"
#include "menu.h"
#include "game.h"
#include "ennemi.h"

#define PERIOD_TASK_REFRESH 40
#define PIXELS 		LCD_MAX_X*LCD_MAX_Y
#define SHIP_SIZE	16

unsigned short buffer[PIXELS];

unsigned short ennemi_view[SHIP_SIZE][SHIP_SIZE] =
	{{0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff},
	 {0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff},
	 {0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff},
	 {0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff},
	 {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
	 {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00},
	 {0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00}};

unsigned short player_view[SHIP_SIZE][SHIP_SIZE] =
	{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00},
	 {0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00},
	 {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00},
	 {0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00}};

extern void refresh(void* cookie)
{

	int err;
	int i, j, k;
	int test = 0;
	char buffer_string[64];
	int last_score = 0xFF;
	int last_level = 0xFF;

	// Configuration de la tâche périodique
	if (TIMER_PERIODIC)
	{
		err = rt_task_set_periodic(&refresh_task, TM_NOW, PERIOD_TASK_REFRESH);
		if (err != 0) {
			printk("Menu task set periodic failed: %d\n", err);
			return;
		}

	}
	else
	{
		err = rt_task_set_periodic(&refresh_task, TM_NOW, PERIOD_TASK_REFRESH*MS);
		if (err != 0) {
			printk("Menu task set periodic failed: %d\n", err);
			return;
		}
	}



    while (1){


    	// Affiche une bande bleue en haut de l'écran avec le level et le score
    	// à chaque fois que ces valeurs sont modifiées
    	if((last_score != score) || (last_level != speed))
		{

    		for(i = 0; i < 10; i++)
    		{
    			for(j = 0; j < LCD_MAX_X; j++)
    			{
    				fb_set_pixel(i, j, 0xFF);
    			}
    		}

        	sprintf(buffer_string, "Level: %d  Score: %d", speed, score);
        	fb_print_string(0xFFFF, BLUE(0x1F), buffer_string, 1, 1);

        	last_score = score;
        	last_level = speed;
		}


    	// Réinitialise le buffer en noir
    	for(i = 0; i < PIXELS; i++)
    	{
    		buffer[i] = 0x00;
    	}

    	// Affichage des ennemis
    	for(k = 0; k < nbEnnemis; k++)
    	{
    		if(ennemi[k].enable == 1)
    		{
				for(i = 0; i < SHIP_SIZE; i++)
				{
					for(j = 0; j < SHIP_SIZE; j++)
					{
						buffer[ennemi[k].x + j + (ennemi[k].y + i)*LCD_MAX_X] = ennemi_view[i][j];
					}
				}
    		}
    		else if(ennemi[k].enable == 2)
    		{
				for(i = 0; i < SHIP_SIZE; i++)
				{
					for(j = 0; j < SHIP_SIZE; j++)
					{
						buffer[ennemi[k].x + j + (ennemi[k].y + i)*LCD_MAX_X] = 0xFFFF;
					}
				}
				ennemi[k].enable++;
				printk("ennemi.enable: %d\n", ennemi[k].enable);
    		}
    		else if(ennemi[k].enable == 3)
    		{
				for(i = 0; i < SHIP_SIZE; i++)
				{
					for(j = 0; j < SHIP_SIZE; j++)
					{
						buffer[ennemi[k].x + j + (ennemi[k].y + i)*LCD_MAX_X] = RED(0xFF) + GREEN(0xFF);
					}
				}
				ennemi[k].enable++;
				printk("ennemi.enable: %d\n", ennemi[k].enable);
    		}
    		else if(ennemi[k].enable == 4)
    		{
				for(i = 0; i < SHIP_SIZE; i++)
				{
					for(j = 0; j < SHIP_SIZE; j++)
					{
						buffer[ennemi[k].x + j + (ennemi[k].y + i)*LCD_MAX_X] = RED(0xFF);
					}
				}
				ennemi[k].enable = 0;
				printk("ennemi.enable: %d\n", ennemi[k].enable);
    		}

    	}

    	// Affichage du joueur
    	for(k = 0; k < NB_PLAYER; k++)
    	{
    		if(player[k].enable == 1)
    		{
				for(i = 0; i < SHIP_SIZE; i++)
				{
					for(j = 0; j < SHIP_SIZE; j++)
					{
						buffer[player[k].x + j + (player[k].y + i)*LCD_MAX_X] = player_view[i][j];
					}
				}
    		}
    		// Explosion du joueur
    		else if(player[k].enable == 2)
    		{
				for(i = 0; i < SHIP_SIZE; i++)
				{
					for(j = 0; j < SHIP_SIZE; j++)
					{
						buffer[player[k].x + j + (player[k].y + i)*LCD_MAX_X] = 0xFFFF;
					}
				}
				player[k].enable++;
				printk("player.enable: %d\n", player[k].enable);
    		}
    		else if(player[k].enable == 3)
    		{
				for(i = 0; i < SHIP_SIZE; i++)
				{
					for(j = 0; j < SHIP_SIZE; j++)
					{
						buffer[player[k].x + j + (player[k].y + i)*LCD_MAX_X] = RED(0xFF) + GREEN(0xFF);
					}
				}
				player[k].enable++;
				printk("player.enable: %d\n", player[k].enable);
    		}
    		else if(player[k].enable == 4)
    		{
				for(i = 0; i < SHIP_SIZE; i++)
				{
					for(j = 0; j < SHIP_SIZE; j++)
					{
						buffer[player[k].x + j + (player[k].y + i)*LCD_MAX_X] = RED(0xFF);
					}
				}
				player[k].enable = 0;
				printk("player.enable: %d\n", player[k].enable);
    		}
    	}

    	// Affichage des shots en blanc
    	for(k = 0; k < NB_MAX_SHOTS; k++)
    	{
    		if(shot[k].enable == 1)
    		{
    			for(i = 0; i < 6; i++)
    				buffer[shot[k].x + i%2 + (shot[k].y + i/2)*LCD_MAX_X] = 0xFFFF;
    		}
    	}

    	// Copie du buffer interne dans le frame buffer
    	for(i = 10; i < LCD_MAX_Y; i++)
    	{
    		for(j = 0; j < LCD_MAX_X; j++)
    		{
    			fb_set_pixel(i, j, buffer[j + i*LCD_MAX_X]);
    		}
    	}

    	/*
    	// POUR LES TESTS
    	for(k = 0; k < nbEnnemis; k++)
    	{
    		if(ennemi[k].enable == 1)
    		{
				ennemi[k].x = (ennemi[k].x + 1) % (LCD_MAX_X - 16);
    		}
    	}
*/
    	// TEST SCORE
    	if(test % 10 == 0)
    	{
    		rt_mutex_lock(&mutex_score, TM_INFINITE);
    		score += 5;
    		rt_mutex_unlock(&mutex_score);
    	}
    	test++;

    	rt_task_wait_period(NULL);

    	// POUR LES TEST DES EXPLOSIONS
    	/*
    	if(test < nbEnnemis)
    	{
    		ennemi[test++].enable = 2;
    	}
    	*/

    }


}
