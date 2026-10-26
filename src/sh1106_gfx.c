#include "sh1106_gfx.h"

#include <stdlib.h>

void sh1106_draw_line(sh1106_t *disp, int x0, int y0, int x1, int y1, sh1106_color_t color) {
	if (!disp) {
		return;
	}

	/* This function follows a generalised Breneham's Line Algorithm.
	 * Altough, I understand it for all 8 octants individually, putting it in one generalised algorithms was not
	 * something for me :(
	 *  Therefore, I used ChatGPT's help to implement this.
	 */

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	int dir_x = (x0 < x1) ? 1 : -1;
	int dir_y = (y0 < y1) ? 1 : -1;

	int err = dx - dy;
	int x = x0, y = y0;
	while (true) {
		sh1106_set_pixel(disp, x, y, color);
		if ((x == x1) && (y == y1)) {
			break;
		}

		int e2 = 2 * err;
		if (-dy < e2) {
			err -= dy;
			x += dir_x;
		}
		if (e2 < dx) {
			err += dx;
			y += dir_y;
		}
	}
}
