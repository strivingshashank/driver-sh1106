#ifndef PI_PICO_SH1106_GFX_H
#define PI_PICO_SH1106_GFX_H

#include "sh1106_core.h"

/* Draws a line from `(x0, y0)` to `(x1, y1)` of `color`.
 * Out-of-bound line is clipped.
 */
void sh1106_draw_line(sh1106_t *disp, int x0, int y0, int x1, int y1, sh1106_color_t color);

#endif /* PI_PICO_SH1106_GFX_H */
