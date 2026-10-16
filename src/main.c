// #include "sh1106_i2c.h"
#include "ssd1306.h"
#include "log.h"

#include <assert.h>
#include <pico/stdio_usb.h>
#include <pico/stdio.h>
#include <pico/time.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/cyw43_arch.h>
#include <pico/types.h>
#include <stdbool.h>
#include <stdint.h>

#define I2C_PORT i2c0
#define BAUD_RATE 100000
#define SDA_PIN 4
#define SCL_PIN 5

void setup_gpio(void);
void demo_ssd1306(ssd1306_t *display);
void demo_sh1106(void);

int main() {
        stdio_init_all();

        // wait for serial connection.
        while (!stdio_usb_connected()) {
                sleep_ms(10);
        }
        log_info("connected: serial");
        
        log_info("setup: gpio: begin");
        setup_gpio();
        log_info("setup: gpio: complete");

        log_info("setup: ssd1306: begin");
        ssd1306_t display = {0};
        display.external_vcc = false;
        bool initialised = ssd1306_init(&display, 128, 64, 0x3c, I2C_PORT);
        if (!initialised) {
                log_info("setup: ssd1306: unsuccessful");
                return -1;
        }
        log_info("setup: ssd1306: successful");
        
        
        log_info("start: demo_ssd1306");
        demo_ssd1306(&display);
        log_info("end: demo_ssd1306");

        return 0;
}

void setup_gpio(void) {
        i2c_init(I2C_PORT, BAUD_RATE);
        gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(SDA_PIN);
        gpio_pull_up(SCL_PIN);        
}

void demo_ssd1306(ssd1306_t *display) {
        assert(display);

        // Per-pixel on-off
        // while (1) {
        //         log_info("start: display test");
                
        //         for (uint8_t y = 0; y < 64; y++) {
        //                 for (uint8_t x = 0; x < 128; x++) {
        //                         ssd1306_draw_pixel(&display, x, y);
        //                 }
                
        //                 ssd1306_show(&display);
        //                 sleep_ms(100);
        //         }
                
        //         sleep_ms(1000);
        
        //         ssd1306_clear(&display);
        //         ssd1306_show(&display);
        //         sleep_ms(1000);
        // }

        // Page test
        // while (1) {
        //     for (uint8_t page = 0; page < 8; page++) {
        //         ssd1306_clear(display);
    
        //         // Draw an 8-pixel-high horizontal band.
        //         ssd1306_draw_square(display, 0, page * 8, 128, 8);
    
        //         ssd1306_show(display);
        //         sleep_ms(1000);
        //     }
        // }

        while (1) {
                // ssd1306_clear(display);
                // ssd1306_draw_square(display, 0, 0, 128, 64);
                // ssd1306_show(display);
                // sleep_ms(500);
                // ssd1306_clear(display);
                // ssd1306_show(display);
                // sleep_ms(500);

                ssd1306_clear(display);
                ssd1306_draw_square(display, 0, 0, 128, 64);
                ssd1306_show(display);
                // ssd1306_contrast(display, 0x00);
                sleep_ms(1000);
                ssd1306_clear(display);
                ssd1306_show(display);
                // ssd1306_contrast(display, 0xFF);
                sleep_ms(1000);
        }
}

void demo_sh1106(void) {
        // sh1106_t display;

        // SH1106_init(&display, I2C_PORT, 0x3c, 128, 64);
        // SH1106_clear(&display);
        // SH1106_drawRectangle(&display, 10, 10, 10, 10, 1);
}

