#include "log.h"
#include "sh1106.h"

#include <assert.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <limits.h>
#include <pico/cyw43_arch.h>
#include <pico/platform/common.h>
#include <pico/stdio.h>
#include <pico/stdio_usb.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <pico/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MICRO_TO_MILLI(x) (x / 1000)
#define KILO(x) (x * 1000)
#define MEGA(x) (KILO(x) * 1000)

#define I2C_PORT i2c0
#define DISPLAY_ADDR 0x3C
#define BAUD_RATE MEGA(1)
#define SDA_PIN 4
#define SCL_PIN 5

void demo1(sh1106_t *disp) {
	assert(disp);

	// sh1106_fill_screen(disp);
	// sh1106_flush(disp);
	while (true) {
		for (uint8_t y = 0; y < SH1106_HEIGHT; y++) {
			for (uint8_t x = 0; x < SH1106_WIDTH; x++) {
				sh1106_draw_pixel(disp, x, y);
			}
			sh1106_flush(disp);
		}
		sleep_ms(250);

		// sh1106_display_off(disp);
		// // sh1106_clear_screen(disp);
		// // sh1106_flush(disp);
		// sleep_ms(100);
		// sh1106_display_on(disp);
		// // sh1106_fill_screen(disp);
		// // sh1106_flush(disp);
		// sleep_ms(100);
	}
}

void demo2(sh1106_t *disp) {
	assert(disp);

	sh1106_fill_screen(disp);
	sh1106_flush(disp);
	while (true) {
		// for (uint8_t i = 0; i < UINT8_MAX; i++) {
		// 	sh1106_set_contrast(disp, i);
		// 	sleep_ms(20);
		// }

		sleep_ms(500);
		sh1106_set_contrast(disp, 0);
		sleep_ms(500);
		sh1106_set_contrast(disp, 33);
		sleep_ms(500);
		sh1106_set_contrast(disp, 66);
		sleep_ms(500);
		sh1106_set_contrast(disp, 100);
		sleep_ms(500);
		sh1106_set_contrast(disp, UINT8_MAX);
		sleep_ms(500);
	}
}

void demo3(sh1106_t *disp) {
	assert(disp);

	srand(get_absolute_time());
	while (true) {
		for (int i = 0; i < 5000; i++) {
			uint8_t x = rand() % SH1106_WIDTH;
			uint8_t y = rand() % SH1106_HEIGHT;

			sh1106_invert_pixel(disp, x, y);
		}
		sh1106_flush(disp);
	}
}

void setup_gpio(void);

int main(void) {
	srand(get_absolute_time());
	stdio_init_all();

	// wait for serial connection.
	while (!stdio_usb_connected()) {
		sleep_ms(10);
	}
	log_info("connected: serial");

	log_info("setup: gpio: begin");
	setup_gpio();
	log_info("setup: gpio: complete");

	sh1106_t display = {0};
	bool init_successful = sh1106_init(&display, I2C_PORT, DISPLAY_ADDR);
	if (init_successful) {
		log_info("init: display: successful");
	} else {
		log_info("init: display: failed");
		return 0;
	}

	demo3(&display);

	while (true) {
		tight_loop_contents();
	}

	return 0;
}

void setup_gpio(void) {
	i2c_init(I2C_PORT, BAUD_RATE);
	gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(SDA_PIN);
	gpio_pull_up(SCL_PIN);
}
