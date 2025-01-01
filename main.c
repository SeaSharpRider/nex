#include "dependencies/lib/falcon.h"
#include <stdio.h>

int main(void) {
    Window* window = window_create(640, 480, "Nex");
    if (!window) {
        fprintf(stderr, "failed to create window: debug - error on line 6\n");
        return -1;
    }

    window_set_icon(window, "dependencies/img/icon.png");
    window_set_maximized(window, true);
    window_set_bg_color(window, 0.0313725f, 0.015686f, 0.0470588f, 1.0f);

    while (!window_should_close(window)) {
        window_update(window);
    }

    window_destroy(window);
    return 0;
}
