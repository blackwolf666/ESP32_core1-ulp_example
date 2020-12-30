#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp32/ulp.h"
#include "driver/rtc_io.h"

#define ___MYWAIT    I_DELAY(65535),\
                     I_DELAY(65535)
#define __MYWAIT    ___MYWAIT,\
                    ___MYWAIT
#define _MYWAIT     __MYWAIT,\
                    __MYWAIT

/* 16x 65535 it's enough */
#define MYWAIT      _MYWAIT,\
                    _MYWAIT,\
                    _MYWAIT,\
                    _MYWAIT



void app_main(void) {
    ulp_insn_t program[] = {
        I_WR_REG(RTC_IO_TOUCH_PAD2_REG, RTC_IO_TOUCH_PAD2_MUX_SEL_S,RTC_IO_TOUCH_PAD2_MUX_SEL_S, 1),
        I_WR_REG(RTC_GPIO_OUT_REG, RTC_GPIO_OUT_DATA_S + 12,  RTC_GPIO_OUT_DATA_S + 12, 1),
        M_LABEL(1),
        I_WR_REG(RTC_GPIO_ENABLE_W1TS_REG,26,26,1),
        MYWAIT,
        I_WR_REG(RTC_GPIO_ENABLE_W1TC_REG,26,26,1),
        MYWAIT,
        M_BX(1)
    };

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_SEL_4;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    vTaskDelay(1000/portTICK_PERIOD_MS);

    size_t load_addr = 0;
    size_t size = sizeof(program)/sizeof(ulp_insn_t);
    ulp_process_macros_and_load(load_addr, program, &size);
    ulp_run(load_addr);

    int s = 1;
    for (;;) {
        s = 1-s;
        gpio_set_level(4, s);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}
