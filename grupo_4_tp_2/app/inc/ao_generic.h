/*
 * ao_generic.h
 *
 *  Created on: Jul 15, 2024
 *      Author: lpmeoli
 */

#ifndef INC_AO_GENERIC_H_
#define INC_AO_GENERIC_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"

/********************** macros ***********************************************/

/********************** typedef **********************************************/
/*Esto no me convence*/
typedef int ao_generic_msg_t;

typedef void (*ao_generic_process_handler_t)(ao_generic_msg_t);

typedef struct {
    QueueHandle_t hqueue;
    ao_generic_process_handler_t handler;
} ao_generic_t;


/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

bool ao_generic_init(ao_generic_t * h_ao_generic, ao_generic_process_handler_t handler, char* str_name);

bool ao_generic_send(ao_generic_t * h_ao_generic, ao_generic_msg_t msg);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* INC_AO_GENERIC_H_ */
