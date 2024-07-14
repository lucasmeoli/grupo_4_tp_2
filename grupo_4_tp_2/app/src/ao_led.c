/*
 * ao_led.c
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
#include "timers.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"

#include "ao_led.h"

/********************** macros and definitions *******************************/

#define QUEUE_LENGTH_            (4)
#define QUEUE_ITEM_SIZE_         (sizeof(ao_led_message_t))

#define TASK_PERIOD_MS_          (1000)

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

/********************** internal functions definition ************************/

static void turn_on_led(ao_led_handle_t* hao_led) {
    HAL_GPIO_WritePin(hao_led->port, hao_led->pin, GPIO_PIN_SET);
    LOGGER_INFO("AO LED - led on");
    vTaskDelay(hao_led->time_on);
    HAL_GPIO_WritePin(hao_led->port, hao_led->pin, GPIO_PIN_RESET);
    LOGGER_INFO("AO LED - led off");
}

static void task_destroy(ao_led_handle_t* hao_led) {
    LOGGER_INFO("AO LED - Elimino tarea");
    hao_led->task_created = false;
    vTaskDelete(NULL);
}

static void task_(void *argument) {
    ao_led_handle_t* hao_led = (ao_led_handle_t*)argument;
    ao_led_message_t msg;

    while (pdPASS == xQueueReceive(hao_led->hqueue, &msg, 0)) {
        switch (msg) {
            case AO_LED_MESSAGE_ON:
                turn_on_led(hao_led);
                break;
            default:
                LOGGER_INFO("AO LED - error");
                break;
        }
    }
    task_destroy(hao_led);
}


/********************** external functions definition ************************/

bool ao_led_send(ao_led_handle_t* hao_led, ao_led_message_t msg) {
    return (pdPASS == xQueueSend(hao_led->hqueue, (void*)&msg, 0));
}

void ao_led_create(ao_led_handle_t* hao_led) {
    hao_led->hqueue = xQueueCreate(QUEUE_LENGTH_, QUEUE_ITEM_SIZE_);
    while(NULL == hao_led->hqueue) {
      // error
    }

    BaseType_t status;
    LOGGER_INFO("AO LED - task create");
    status = xTaskCreate(task_, "task_ao_led", 128, (void* const)hao_led, tskIDLE_PRIORITY, NULL);
    while (pdPASS != status) {
        // error
    }
    hao_led->task_created = true;
}

/********************** end of file ******************************************/