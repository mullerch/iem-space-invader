/*
 * switchs.c
 *
 *  Created on: 19 janv. 2012
 *      Author: redsuser
 */

#include <native/task.h>
#include <native/intr.h>
#include <native/event.h>
#include <native/alarm.h>
#include <native/timer.h>

#include "pca9554-m.h"
#include "rt-app-m.h"

int switchs_init() {
	// Création de la tâche gérant les switchs
	err =  rt_task_create (&switch_events_task, "switch_events", STACK_SIZE, 50, 0);
	if (err != 0) {
		printk("Switch events task creation failed: %d\n", err);
		return -1;
	}

	printk("Switch events task created\n");

	err = rt_task_start(&switch_events_task, switch_events, 0);
	if (err != 0) {
		printk("Switch events task start failed: %d\n", err);
		return -1;
	}
}

/*
void i2c_module_init() {
	mknod("/var/dev/i2c", S_IFCHR|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH, makedev(10,0));

	i2c_fd = open("/var/dev/i2c", O_RDWR);
}
*/

void switch_events(void *cookie) {

	int i;
	int ctr;

	// Configuration de la tâche périodique
	if (TIMER_PERIODIC) {
		err = rt_task_set_periodic(&switch_events_task, TM_NOW, PERIOD_TASK_SWITCHS);
		if (err != 0) {
			printk("Switch events task set periodic failed: %d\n", err);
			return;
		}

	} else {
		err = rt_task_set_periodic(&switch_events_task, TM_NOW, PERIOD_TASK_SWITCHS * MS);
		if (err != 0) {
			printk("Switch events task set periodic failed: %d\n", err);
			return;
		}
	}

	while(1) {
		rt_task_wait_period(NULL);

		i = 0;
		ctr = 0;

		check_switch_events_once();

		/* This is a cheat :p */
		if(SW5_event && SW3_event) {
			SW5_event = 0;
			SW3_event = 0;

			player[0].lifes++;
			hp_update_leds();

		}


		if(SW2_event) {
			SW2_event = 0;

			/* Parcours le tableau des tirs */
			while(1) {
				ctr++;

				/* Si le tir courant est inactif */
				if(shot[i].enable == 0) {
					/* L'initialise et l'active */
					shot[i].x = player[1].x;
					shot[i].y = player[1].y;
					shot[i].direction = -1; // Moves up
					shot[i].enable = 1;
					break;
				} else {
					/* Pase au tir suivant */
					i = ((i+1) % NB_MAX_SHOTS);

					/* Si on a parcouru plus de 2 fois le tableau */
					if(ctr > NB_MAX_SHOTS*2)
						/* Annule le tir pour éviter de planter les suivants */
						break;
				}
			}
		}

		if(SW3_event) {
			SW3_event = 0;

			if(player[0].lifes < 4) {
				player[0].lifes++;
				hp_update_leds();
			}
		}

		if(SW4_event) {
			SW4_event = 0;

			if(player[0].lifes > 0) {
				player[0].lifes--;
				hp_update_leds();
			}
		}
	}
}


void check_switch_events_once() {

	char buf[1];
	char lastBuf[1];

	char switch_change, switch_change_up;

	if((err = read(i2c_fd, buf, 1)) < 0) {
		printk("i2c read error : %d\n", err);
	} else if(buf[0] != lastBuf[0]) {

		switch_change = (buf[0] ^ lastBuf[0]) >> 4;
		switch_change_up = switch_change & ~(buf[0] >> 4);

		if(switch_change_up & 0x1) {
			SW5_event = 1;
		}

		if(switch_change_up & 0x2) {
			SW4_event = 1;
		}

		if(switch_change_up & 0x4) {
			SW3_event = 1;
		}

		if(switch_change_up & 0x8) {
			SW2_event = 1;
		}

		lastBuf[0] = buf[0];
	}
}