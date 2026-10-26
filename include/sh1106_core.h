/* SH1106 OLED (I2C) driver for the Raspberry Pi Pico. */
#ifndef PI_PICO_SH1106_CORE_H
#define PI_PICO_SH1106_CORE_H

#include <hardware/i2c.h>

#define SH1106_WIDTH 128 			/* Visible columns, in pixels. */
#define SH1106_HEIGHT 64 			/* Visible rows, in pixels. */
#define SH1106_PAGES (SH1106_HEIGHT / 8) 	/* Each page is a row of 8 pixels. */

typedef enum {
	SH1106_BLACK, /* Turn OFF a pixel. */
	SH1106_WHITE, /* Turn ON a pixel. */
	SH1106_INVERT /* Invert a pixel. */
} sh1106_color_t;

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

/* Turns display OFF.
 * Retains display content.
 */
void sh1106_display_off(const sh1106_t *disp);

/* Set display contrast.
 * Contrast level ranges from 0 (dimmest) to 255 (brightest).
 * To turn off the display, use `sh1106_display_off()`.
 */
void sh1106_set_contrast(const sh1106_t *disp, uint8_t level);

/* Set a `sh1106_color_t` for the entire display.
 * Any unknown color is ignored.
 * Writes to buffer, use `sh1106_flush` to send to display.
 */void sh1106_set_screen(sh1106_t *disp, sh1106_color_t color);

/* Set a `sh1106_color_t` for a pixel.
 * If pixel is out of bound, it is ignored.
 * Any out-of-bound index or unknown color is ignored.
 * Writes to buffer, use `sh1106_flush` to send to display.
 */
void sh1106_set_pixel(sh1106_t *disp, int x, int y, sh1106_color_t color);

#endif /* PI_PICO_SH1106_CORE_H */
