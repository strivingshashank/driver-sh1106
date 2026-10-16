#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

#define SDA_PIN 4
#define SCL_PIN 5

void scan_i2c(void)
{
    i2c_init(i2c0, 100 * 1000);

    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    sleep_ms(2000);

    printf("I2C Scanner\n");

    for (uint8_t addr = 0x08; addr <= 0x77; addr++)
    {
        uint8_t data;
        int result = i2c_read_blocking(
            i2c0,
            addr,
            &data,
            1,
            false
        );

        if (result >= 0)
            printf("Found device at 0x%02X\n", addr);
    }

    while (true)
        sleep_ms(1000);
}