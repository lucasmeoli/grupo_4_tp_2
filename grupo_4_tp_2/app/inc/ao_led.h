/*
 * ao_led.h
 *
 *  Created on: Jun 30, 2024
 *      Author: lpmeoli
 */

#ifndef AO_LED_H_
#define AO_LED_H_

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

typedef enum {
  AO_LED_MESSAGE_ON,
  AO_LED_MESSAGE_OFF,
  AO_LED_MESSAGE__N,
} ao_led_message_t;

typedef struct {
    QueueHandle_t hqueue;
    bool task_created;
    uint16_t time_on;
    GPIO_TypeDef* port;
    uint16_t pin;
} ao_led_handle_t;

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

bool ao_led_send(ao_led_handle_t* hao_led, ao_led_message_t msg);

void ao_led_create(ao_led_handle_t* hao_led);

void ao_led_destroy();

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* AO_LED_H_ */
/********************** end of file ******************************************/

