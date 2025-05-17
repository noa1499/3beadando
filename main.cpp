#include "graphics.hpp"
#include "widgets.hpp"
#include "amobagrid.hpp"
#include <vector>

using namespace genv;
using namespace std;

int main() {
    gout.open(400, 400);
    gout << font("LiberationSans-Regular.ttf", 20); // Alapértelmezett betűméret

    bool show_grid = false;
    bool gameOver = false;
    char winner = ' ';
    AmobaGrid* grid = nullptr;

    event ev;
    while(gin >> ev) {
        // Háttér
        gout << color(230, 204, 255) << move_to(0, 0) << box(400, 400);

        if (!show_grid) {
            // Start gomb
            gout << color(75, 0, 130) << move_to(150, 180) << box(100, 40);
            gout << font("LiberationSans-Regular.ttf", 20); // Explicit méret a Start szöveghez
            gout << color(255, 255, 255) << move_to(170, 190) << text("START");

            // Játék vége üzenet
            if (gameOver) {
                gout << font("LiberationSans-Regular.ttf", 30);
                if (winner != ' ') {
                    gout << color(0, 0, 0) << move_to(120, 100)
                         << text("Győztes: ") << text(string(1, winner));
                } else {
                    gout << color(0, 0, 0) << move_to(140, 100)
                         << text("Döntetlen!");
                }
                gout << font("LiberationSans-Regular.ttf", 20); // Visszaállítás
                gout << move_to(130, 250) << text("Új játékhoz kattints!");
            }

            // Kattintás kezelése
            if (ev.type == ev_mouse && ev.button == btn_left) {
                if (ev.pos_x >= 150 && ev.pos_x <= 250 &&
                    ev.pos_y >= 180 && ev.pos_y <= 220) {
                    show_grid = true;
                    gameOver = false;
                    winner = ' ';
                    delete grid;
                    grid = new AmobaGrid(5, 5, 390, 390);
                }
            }
        } else {
            grid->handle(ev);
            grid->draw();
            if (grid->isGameOver()) {
                winner = grid->getWinner();
                gameOver = true;
                show_grid = false;
                delete grid;
                grid = nullptr;
            }
        }

        gout << refresh;
    }

    delete grid;
    return 0;
}
