#include "demo.h"
#include "log.h"
#include "sh1106_core.h"
#include "sh1106_gfx.h"

#include <pico/time.h>
#include <pico/types.h>
#include <stdlib.h>

#define DELAY_MS 500

void demo_core_display(sh1106_t *disp) {
	assert(disp);

	for (int i = 0; i < 10; i++) {
		sh1106_set_screen(disp, SH1106_INVERT);
		sh1106_flush(disp);
		sleep_ms(DELAY_MS);
	}
}

void demo_core_contrast(sh1106_t *disp) {
	assert(disp);

	sh1106_set_screen(disp, SH1106_WHITE);
	sh1106_flush(disp);

	sh1106_set_contrast(disp, 0);
	sleep_ms(DELAY_MS);
	sh1106_set_contrast(disp, 50);
	sleep_ms(DELAY_MS);
	sh1106_set_contrast(disp, 100);
	sleep_ms(DELAY_MS);
	sh1106_set_contrast(disp, 150);
	sleep_ms(DELAY_MS);
	sh1106_set_contrast(disp, 200);
	sleep_ms(DELAY_MS);
	sh1106_set_contrast(disp, 255);
	sleep_ms(DELAY_MS);
}

void demo_core_screen(sh1106_t *disp) {
	assert(disp);

	for (int i = 0; i < 10; i++) {
		sh1106_set_screen(disp, SH1106_INVERT);
		sh1106_flush(disp);
		sleep_ms(DELAY_MS);
	}
}

void demo_core_pixel(sh1106_t *disp) {
	assert(disp);

	absolute_time_t start = get_absolute_time();
	absolute_time_t end = delayed_by_ms(start, 7000);
	srand(start);
	while (true) {
		absolute_time_t now = get_absolute_time();
		if (absolute_time_diff_us(now, end) <= 0) {
			break;
		}

		for (int i = 0; i < 5; i++) {
			int x = rand() % SH1106_WIDTH;
			sleep_ms(1);
			int y = rand() % SH1106_HEIGHT;
			sh1106_set_pixel(disp, x, y, SH1106_INVERT);
		}
		sh1106_flush(disp);
	}
}

void demo_gfx_line(sh1106_t *disp) {
	assert(disp);

	absolute_time_t start = get_absolute_time();
	absolute_time_t end = delayed_by_ms(start, 7000);
	srand(start);
	while (true) {
		absolute_time_t now = get_absolute_time();
		if (absolute_time_diff_us(now, end) <= 0) {
			break;
		}

		int x0 = rand() % SH1106_WIDTH;
		sleep_ms(1);
		int y0 = rand() % SH1106_HEIGHT;
		sleep_ms(1);
		int x1 = rand() % SH1106_WIDTH;
		sleep_ms(1);
		int y1 = rand() % SH1106_HEIGHT;

		sh1106_draw_line(disp, x0, y0, x1, y1, SH1106_INVERT);
		sh1106_flush(disp);
		sleep_ms(100);
	}
}

void demo_gfx_hline(sh1106_t *disp) {
	assert(disp);

	absolute_time_t start = get_absolute_time();
	absolute_time_t end = delayed_by_ms(start, 7000);
	srand(start);
	while (true) {
		absolute_time_t now = get_absolute_time();
		if (absolute_time_diff_us(now, end) <= 0) {
			break;
		}

		int x0 = rand() % SH1106_WIDTH;
		sleep_ms(1);
		int y0 = rand() % SH1106_HEIGHT;
		int width = rand() % 60;

		sh1106_draw_hline(disp, x0, y0, width, SH1106_INVERT);
		sh1106_flush(disp);
		sleep_ms(100);
	}
}

void demo_gfx_vline(sh1106_t *disp) {
	assert(disp);

	absolute_time_t start = get_absolute_time();
	absolute_time_t end = delayed_by_ms(start, 7000);
	srand(start);
	while (true) {
		absolute_time_t now = get_absolute_time();
		if (absolute_time_diff_us(now, end) <= 0) {
			break;
		}

		int x0 = rand() % SH1106_WIDTH;
		sleep_ms(1);
		int y0 = rand() % SH1106_HEIGHT;
		int height = rand() % 30;

		sh1106_draw_vline(disp, x0, y0, height, SH1106_INVERT);
		sh1106_flush(disp);
		sleep_ms(100);
	}
}

void demo_gfx_rect(sh1106_t *disp) {
	assert(disp);

	absolute_time_t start = get_absolute_time();
	absolute_time_t end = delayed_by_ms(start, 7000);
	srand(start);
	while (true) {
		absolute_time_t now = get_absolute_time();
		if (absolute_time_diff_us(now, end) <= 0) {
			break;
		}

		int x0 = rand() % SH1106_WIDTH;
		sleep_ms(1);
		int y0 = rand() % SH1106_HEIGHT;
		int width = rand() % 20;
		int height = rand() % 20;

		sh1106_draw_rect(disp, x0, y0, width, height, SH1106_INVERT);
		sh1106_flush(disp);
		sleep_ms(100);
	}
}

void demo_gfx_fill_rect(sh1106_t *disp) {
	assert(disp);

	absolute_time_t start = get_absolute_time();
	absolute_time_t end = delayed_by_ms(start, 7000);
	srand(start);
	while (true) {
		absolute_time_t now = get_absolute_time();
		if (absolute_time_diff_us(now, end) <= 0) {
			break;
		}

		int x0 = rand() % SH1106_WIDTH;
		sleep_ms(1);
		int y0 = rand() % SH1106_HEIGHT;
		int width = rand() % 20;
		int height = rand() % 20;

		sh1106_fill_rect(disp, x0, y0, width, height, SH1106_INVERT);
		sh1106_flush(disp);
		sleep_ms(100);
	}
}

void demo(sh1106_t *disp) {
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: core: display ON/OFF");
	demo_core_display(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: core: display contrast");
	demo_core_contrast(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: core: screen fill/clear");
	demo_core_screen(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: core: screen pixel");
	demo_core_pixel(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: gfx: line");
	demo_gfx_line(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: gfx: hline");
	demo_gfx_hline(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: gfx: vline");
	demo_gfx_vline(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: gfx: rect");
	demo_gfx_rect(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);

	log_debug("demo: gfx: fill rect");
	demo_gfx_fill_rect(disp);
	sh1106_set_screen(disp, SH1106_BLACK);
	sh1106_flush(disp);
}
