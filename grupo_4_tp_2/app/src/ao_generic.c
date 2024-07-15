/*
 * ao_generic.c
 *
 *  Created on: Jul 15, 2024
 *      Author: lpmeoli
 */

/********************** inclusions *******************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"

#include "ao_generic.h"

/********************** macros and definitions *******************************/
#define QUEUE_LENGTH_			(1)
#define QUEUE_ITEM_SIZE_		(sizeof(ao_generic_msg_t))


/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

/********************** internal functions definition ************************/



static void task_(void *argument) {
	ao_generic_t * h_ao_generic = (ao_generic_t*)argument;

    while (true) {
    	/* que mensaje seria aca*/
    	ao_generic_msg_t msg;
        if (pdPASS == xQueueReceive(h_ao_generic->hqueue, &msg, portMAX_DELAY)) {
        	h_ao_generic->handler(msg);
        }
    }
}

/********************** external functions definition ************************/
bool ao_generic_send(ao_generic_t * h_ao_generic, ao_generic_msg_t msg) {
    return (pdPASS == xQueueSend(h_ao_generic->hqueue, (void*)&msg, 0));
}


bool ao_generic_init(ao_generic_t * h_ao_generic, ao_generic_process_handler_t handler, char* str_name) {
	h_ao_generic->handler = handler;

	h_ao_generic->hqueue = xQueueCreate(QUEUE_LENGTH_, QUEUE_ITEM_SIZE_);
    if(NULL == h_ao_generic->hqueue) {
      return false;
    }

    BaseType_t status;
    status = xTaskCreate(task_, str_name, 128, (void* const)h_ao_generic, tskIDLE_PRIORITY, NULL);
    if (pdPASS != status) {
    	return false;
    }

    return true;
}

