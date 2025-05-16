#include "graphics.hpp"
#include "widgets.hpp"

using namespace genv;

int main() {
    gout.open(400, 400);
    gout << font("LiberationSans-Regular.ttf", 20);

    Button start_btn(150, 180, 100, 40, "START");

    event ev;
    while(gin >> ev) {
        start_btn.handle(ev);

        gout << move_to(0,0) << color(255,255,255) << box(400,400);

        start_btn.draw();

        gout << refresh;

        if (start_btn.is_pressed()) {
            break;
        }
    }

    return 0;
}
