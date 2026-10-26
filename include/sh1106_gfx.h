#ifndef PI_PICO_SH1106_GFX_H
#define PI_PICO_SH1106_GFX_H

#include "sh1106_core.h"

/* Draws a line from `(x0, y0)` to `(x1, y1)` of `color`.
 * Out-of-bound line is clipped.
 */
void sh1106_draw_line(sh1106_t *disp, int x0, int y0, int x1, int y1, sh1106_color_t color);

/* Draws a horizontal line from `(x0, y0)` with `width` of `color`.
 * Out-of-bound line is clipped.
 * Negative width is ignored.
 */
void sh1106_draw_hline(sh1106_t *disp, int x0, int y0, int width, sh1106_color_t color);

/* Draws a vertical line from `(x0, y0)` with `height` of `color`.
 * Out-of-bound line is clipped.
 * Negative height is ignored.
 */
void sh1106_draw_vline(sh1106_t *disp, int x0, int y0, int height, sh1106_color_t color);

/* Draws an empty rectangle from `(x0, y0)` with `width` and `height` of `color`. */
void sh1106_draw_rect(sh1106_t *disp, int x0, int y0, int width, int height, sh1106_color_t color);

void sh1106_fill_rect(sh1106_t *disp, int x0, int y0, int width, int height, sh1106_color_t color);

#endif /* PI_PICO_SH1106_GFX_H */
