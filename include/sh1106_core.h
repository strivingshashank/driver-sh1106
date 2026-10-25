/* SH1106 OLED (I2C) driver for the Raspberry Pi Pico. */
#ifndef PI_PICO_SH1106_CORE_H
#define PI_PICO_SH1106_CORE_H

#include <hardware/i2c.h>

#define SH1106_WIDTH 128 			/* Visible columns, in pixels. */
#define SH1106_HEIGHT 64 			/* Visible rows, in pixels. */
#define SH1106_PAGES (SH1106_HEIGHT / 8) 	/* Each page is a row of 8 pixels. */

/* A display instance. Drawing functions only modifies `buffer`;
 * call `sh1106_flush()` to send it to the display.
 */
typedef struct {
	i2c_inst_t *i2c;
	uint8_t address; /* 7-bit I2C address (0x3C or 0x3D). */
	/* In-memory copy of display.
	 * Each byte is 8 vertical pixels, LSB on top.
	 */
	uint8_t buffer[SH1106_PAGES][SH1106_WIDTH];
} sh1106_t;

/* Configures the display and turns it on. `disp` should be zero-initialised.
 * Returns `true` on success, `false` otherwise.
 */
bool sh1106_init(sh1106_t *disp, i2c_inst_t *i2c, uint8_t address);

/* Sends buffer to the display. Blocks until done. */
void sh1106_flush(const sh1106_t *disp);

/* Turns display ON. */
void sh1106_display_on(const sh1106_t *disp);

/* Turns display OFF. */
void sh1106_display_off(const sh1106_t *disp);

/* Set display contrast.
 * Contrast level ranges from 0 to 255.
 */
void sh1106_set_contrast(const sh1106_t *disp, uint8_t level);

/* Turns ON all the pixels in the buffer. */
void sh1106_fill_screen(sh1106_t *disp);

/* Turns OFF all the pixels in the buffer. */
void sh1106_clear_screen(sh1106_t *disp);

/* Turns a pixel ON. Out-of-range coordinates are ignored. */
void sh1106_draw_pixel(sh1106_t *disp, uint8_t x, uint8_t y);

/* Turns a pixel OFF. Out-of-range coordinates are ignored. */
void sh1106_clear_pixel(sh1106_t *disp, uint8_t x, uint8_t y);

/* Inverts a pixel. Out-of-range coordinates are ignored. */
void sh1106_invert_pixel(sh1106_t *disp, uint8_t x, uint8_t y);

#endif /* PI_PICO_SH1106_CORE_H */
