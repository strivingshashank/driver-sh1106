#include "log.h"
#include "sh1106_core.h"
#include "sh1106_gfx.h"

#include <assert.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <limits.h>
#include <pico/cyw43_arch.h>
#include <pico/platform/common.h>
#include <pico/platform/compiler.h>
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

void demo_draw_line(sh1106_t *disp) {
	assert(disp);

	srand(get_absolute_time());

	while (true) {
		int x0 = rand() % SH1106_WIDTH, y0 = rand() % SH1106_HEIGHT;
		int x1 = rand() % SH1106_WIDTH, y1 = rand() % SH1106_HEIGHT;
		sh1106_draw_line(disp, x0, y0, x1, y1, SH1106_INVERT);
		sh1106_flush(disp);
		sleep_ms(50);
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

	demo_draw_line(&display);

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
