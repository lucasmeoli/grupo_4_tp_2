/*
 * ao_led_manager.c
 *
 *  Created on: Jul 14, 2024
 *      Author: lpmeoli
 */

/********************** inclusions *******************************************/

#include <led_manager.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"
#include "timers.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"

#include "led_manager.h"

/********************** macros and definitions *******************************/

#define MAX_LEDS_                (3)

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

/********************** internal functions definition ************************/

/********************** external functions definition ************************/


bool led_manager_turn_on_led(ao_led_handle_t * hao_led) {

    if (!hao_led->task_created) {
        ao_led_create(hao_led);
    }

    if(ao_led_send(hao_led, AO_LED_MESSAGE_ON)) {
        LOGGER_INFO("Led Manager: QueueSend");
        return true;
    }

    LOGGER_INFO("Led Manager: Error - No hay más lugar en la cola");

    return false;
}


/********************** end of file ******************************************/
