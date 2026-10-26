#include "demo.h"
#include "log.h"
#include "sh1106_core.h"
#include "util.h"

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

void setup_gpio(void);

int main(void) {
	srand(get_absolute_time());
	stdio_init_all();

	/* Wait for serial connection. */
	while (!stdio_usb_connected()) {
		sleep_ms(10);
	}
	log_info("connected: serial");

	log_info("setup: gpio: begin");
	setup_gpio();
	log_info("setup: gpio: complete");

	sh1106_t disp = {0};
	bool init_successful = sh1106_init(&disp, I2C_PORT, DISPLAY_ADDR);
	if (init_successful) {
		log_info("init: display: successful");
	} else {
		log_info("init: display: failed");
		return 0;
	}

	log_info("demo: begin");
	demo(&disp);
	log_info("demo: complete");

	/* Keep looping instead of exiting. */
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
