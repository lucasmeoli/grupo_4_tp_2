/*
 * ao_ui.c
 *
 *  Created on: Jun 30, 2024
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

#include "ao_ui.h"
#include "ao_led.h"
#include "led_manager.h"

/********************** macros and definitions *******************************/

#define QUEUE_LENGTH_			(1)
#define QUEUE_ITEM_SIZE_		(sizeof(ao_ui_message_t))

#define TIME_LED_ON_MS			1000
/* The length of the queues is defined based on the maximum number of times
 * the button can be pressed and generate an event while the LED is on. */
#define LED_RED_QUEUE_LENGTH	4
#define LED_GREEN_QUEUE_LENGTH	1
#define LED_BLUE_QUEUE_LENGTH	1

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

ao_led_handle_t hao_ledR = {NULL, LED_RED_QUEUE_LENGTH, false, TIME_LED_ON_MS, LED_RED_PORT, LED_RED_PIN};
ao_led_handle_t hao_ledG = {NULL, LED_GREEN_QUEUE_LENGTH, false, TIME_LED_ON_MS, LED_GREEN_PORT, LED_GREEN_PIN};
ao_led_handle_t hao_ledB = {NULL, LED_BLUE_QUEUE_LENGTH, false, TIME_LED_ON_MS, LED_BLUE_PORT, LED_BLUE_PIN};

/********************** internal functions definition ************************/

static void task_(void *argument) {
    ao_ui_handle_t* hao = (ao_ui_handle_t*)argument;

    while (true) {
        ao_ui_message_t msg;
        if (pdPASS == xQueueReceive(hao->hqueue, &msg, portMAX_DELAY)) {
            switch (msg) {
              case AO_UI_MESSAGE_BUTTON_NONE:
                  break;

              case AO_UI_MESSAGE_BUTTON_PULSE:
                  LOGGER_INFO("AO UI - Button pulse");
                  led_manager_turn_on_led(&hao_ledR);
                  break;

              case AO_UI_MESSAGE_BUTTON_SHORT:
                  LOGGER_INFO("AO UI - Button short");
                  led_manager_turn_on_led(&hao_ledG);
                  break;

              case AO_UI_MESSAGE_BUTTON_LONG:
                  LOGGER_INFO("AO UI - Button long");
                  led_manager_turn_on_led(&hao_ledB);
                  break;

              default:
                  LOGGER_ERROR("AO UI - Unknown message");
                  break;
            }
        }
    }
}

/********************** external functions definition ************************/

bool ao_ui_send(ao_ui_handle_t* hao, ao_ui_message_t msg) {
    return (pdPASS == xQueueSend(hao->hqueue, (void*)&msg, 0));
}

bool ao_ui_init(ao_ui_handle_t* hao) {
    hao->hqueue = xQueueCreate(QUEUE_LENGTH_, QUEUE_ITEM_SIZE_);
    if (NULL == hao->hqueue) {
        return false;
    }

    BaseType_t status;
    status = xTaskCreate(task_, "task_ao_ui", 128, (void* const)hao, tskIDLE_PRIORITY, NULL);
    if (pdPASS != status) {
        return false;
    }

    return true;
}

/********************** end of file ******************************************/
