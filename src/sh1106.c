#include "sh1106.h"

#include <assert.h>
#include <string.h>

/* The chip's RAM is 132 columns wide; the 128-pixel panel starts at column 2. */
#define SH1106_COL_OFFSET 2

/* First byte of every I2C transfer: tells the chip what follows. */
typedef enum {
	WRITE_CMD_STREAM = 0x00,  /* All following are commands. */
	WRITE_DATA_STREAM = 0x40, /* All following are data. */
} sh1106_write_mode_t;

/* Command bytes. */
typedef enum {
	SET_DISPLAY_ON = 0xAE,
	SET_DISPLAY_OFF = 0xAF,
	SET_PAGE_ADDR = 0xB0,
	SET_LOWER_COL_ADDR = 0x00,
	SET_HIGHER_COL_ADDR = 0x10,
	SET_CONTRAST = 0x81
} sh1106_cmd_t;

/* Position of a pixel in buffer. `valid` is false if out-of-range. */
typedef struct {
	uint8_t page;
	uint8_t byte;
	uint8_t bit;
	bool valid;
} sh1106_display_pos_t;

/* Converts `x` and `y` to `sh1106_display_pos_t` representaion.
 * Sets `valid` as false if out-of-range.
 */
static sh1106_display_pos_t sh1106_get_pos(uint8_t x, uint8_t y) {
	sh1106_display_pos_t pos = {0};

	bool out_of_bound = (SH1106_WIDTH <= x) || (SH1106_HEIGHT <= y);
	if (out_of_bound) {
		pos.valid = false;
		return pos;
	}

	pos.page = y / 8;
	pos.byte = x;
	pos.bit = y % 8;
	pos.valid = true;

	return pos;
}

/* Writes data to the display over I2C.
 * Only point-of-contact with the I2C connection.
 * Returns I2C write status.
 */
static int sh1106_write(const sh1106_t *disp, sh1106_write_mode_t mode, const uint8_t *data, size_t len) {
	assert(disp);
	assert(data);
	assert(len <= SH1106_WIDTH);

	uint8_t tmp[SH1106_WIDTH + 1]; /* Upto SH1106_WIDTH bytes + Control byte */
	tmp[0] = mode;
	memcpy(&tmp[1], data, len);

	int write_status = i2c_write_blocking(disp->i2c, disp->address, tmp, (len + 1), false);
	return write_status;
}

/* Write one `command` byte to the display chip. */
static int sh1106_write_cmd(const sh1106_t *disp, uint8_t command) {
	return sh1106_write(disp, WRITE_CMD_STREAM, &command, 1);
}

/* Write multiple `command` bytes to the display chip. */
static int sh1106_write_cmd_stream(const sh1106_t *disp, const uint8_t *commands, size_t len) {
	return sh1106_write(disp, WRITE_CMD_STREAM, commands, len);
}

/* Write one `data` byte to the display chip. */
static int sh1106_write_data(const sh1106_t *disp, uint8_t data) {
	return sh1106_write(disp, WRITE_DATA_STREAM, &data, 1);
}

/* Write multiple `data` bytes to the display chip. */
static int sh1106_write_data_stream(const sh1106_t *disp, const uint8_t *data, size_t len) {
	return sh1106_write(disp, WRITE_DATA_STREAM, data, len);
}

bool sh1106_init(sh1106_t *disp, i2c_inst_t *i2c, uint8_t address) {
	assert(disp);
	assert(i2c);

	disp->i2c = i2c;
	disp->address = address;
	memset(disp->buffer, 0, sizeof(disp->buffer));

	sleep_ms(100); /* Give some time for display to setup. */

	// TODO: change this after understanding them.
	const uint8_t sh1106_init_seq[] = {
	    0xAE,	// Display OFF (sleep mode)
	    0xD5, 0x80, // Set display clock divide ratio/oscillator frequency (default 0x80)
	    0xA8, 0x3F, // Set multiplex ratio (1/64 duty cycle -> 0x3F)
	    0xD3, 0x00, // Set display offset (0x00 = no offset)
	    0x40,	// Set display start line (0x40 = line 0)
	    0xAD, 0x8B, // DC-DC control / Charge Pump setting (0x8B = enable internal charge pump)
	    0x33,	// Set VPP (0x33 = 9.0V)
	    0xA1,	// Set segment re-map (column address 127 is mapped to SEG0)
	    0xC8,	// Set COM output scan direction (remapped mode / normal scan)
	    0xDA, 0x12, // Set COM pins hardware configuration
	    0x81, 0xCF, // Set contrast control register
	    0xD9, 0xF1, // Set pre-charge period
	    0xDB, 0x40, // Set VCOMH deselect level
	    0xA4,	// Entire display on/off -> resume RAM content display
	    0xA6,	// Set normal (not inverted) display
	};
	int status = sh1106_write_cmd_stream(disp, sh1106_init_seq, sizeof(sh1106_init_seq));

	sh1106_write_cmd(disp, 0xAF); /* Display ON */
	sh1106_flush(disp);

	return 0 < status;
}

void sh1106_flush(const sh1106_t *disp) {
	assert(disp);

	for (uint8_t page_idx = 0; page_idx < SH1106_PAGES; page_idx++) {
		uint8_t cmds[3] = {SET_PAGE_ADDR | page_idx, SET_LOWER_COL_ADDR | SH1106_COL_OFFSET,
				   SET_HIGHER_COL_ADDR | 0};
		sh1106_write_cmd_stream(disp, cmds, sizeof(cmds));
		sh1106_write_data_stream(disp, disp->buffer[page_idx], SH1106_WIDTH);
	}
}

void sh1106_display_on(const sh1106_t *disp) {
	assert(disp);
	sh1106_write_cmd(disp, SET_DISPLAY_ON);
}

void sh1106_display_off(const sh1106_t *disp) {
	assert(disp);
	sh1106_write_cmd(disp, SET_DISPLAY_OFF);
}

void sh1106_set_contrast(const sh1106_t *disp, uint8_t level) {
	assert(disp);

	uint8_t cmds[2] = {SET_CONTRAST, level};
	sh1106_write_cmd_stream(disp, cmds, sizeof(cmds));
}

void sh1106_fill_screen(sh1106_t *disp) {
	assert(disp);
	memset(disp->buffer, 0xFF, sizeof(disp->buffer));
}

void sh1106_clear_screen(sh1106_t *disp) {
	assert(disp);
	memset(disp->buffer, 0, sizeof(disp->buffer));
}

void sh1106_draw_pixel(sh1106_t *disp, uint8_t x, uint8_t y) {
	assert(disp);

	sh1106_display_pos_t pos = sh1106_get_pos(x, y);
	if (!pos.valid) {
		return;
	}
	disp->buffer[pos.page][pos.byte] |= (1 << pos.bit);
}

void sh1106_clear_pixel(sh1106_t *disp, uint8_t x, uint8_t y) {
	assert(disp);

	sh1106_display_pos_t pos = sh1106_get_pos(x, y);
	if (!pos.valid) {
		return;
	}
	disp->buffer[pos.page][pos.byte] &= ~(1 << pos.bit);
}

void sh1106_invert_pixel(sh1106_t *disp, uint8_t x, uint8_t y) {
	assert(disp);

	sh1106_display_pos_t pos = sh1106_get_pos(x, y);
	if (!pos.valid) {
		return;
	}
	disp->buffer[pos.page][pos.byte] ^= (1 << pos.bit);
}
