#include "graphics.hpp"
#include "widgets.hpp"
#include "amobagrid.hpp"
#include <vector>

using namespace genv;
using namespace std;

int main() {
    gout.open(400, 400);
    gout << font("LiberationSans-Regular.ttf", 20);

    bool show_grid = false;
    AmobaGrid* grid = nullptr;

    event ev;
    while(gin >> ev) {
        // Háttérszín: világos lila (RGB: 230, 204, 255)
        gout << color(230, 204, 255) << move_to(0, 0) << box(400, 400);

        if (!show_grid) {
            // Start gomb rajzolása (sötét lila: RGB 75, 0, 130)
            gout << color(75, 0, 130)
                 << move_to(150, 180)
                 << box(100, 40);

            // Szöveg rajzolása (fehér)
            gout << color(255, 255, 255)
                 << move_to(170, 190)
                 << text("START");

            // Kattintás kezelése
            if (ev.type == ev_mouse && ev.button == btn_left) {
                if (ev.pos_x >= 150 && ev.pos_x <= 250 &&
                    ev.pos_y >= 180 && ev.pos_y <= 220) {
                    show_grid = true;
                    grid = new AmobaGrid(5, 5, 390, 390); // Pálya létrehozása
                }
            }
        } else {
            // Játék kezelése és rajzolása
            grid->handle(ev);
            grid->draw();
        }

        gout << refresh;
    }

    delete grid; // Memóriafelszabadítás
    return 0;
}
