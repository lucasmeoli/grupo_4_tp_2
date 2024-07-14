/*
 * ao_led_manager.h
 *
 *  Created on: Jul 14, 2024
 *      Author: lpmeoli
 */

#ifndef INC_LED_MANAGER_H_
#define INC_LED_MANAGER_H_

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
#include "ao_led.h"


/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

bool led_manager_turn_on_led(ao_led_handle_t * hao_led);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif


#endif /* INC_LED_MANAGER_H_ */
