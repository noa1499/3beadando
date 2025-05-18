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
    bool gameOver = false;
    char winner = ' ';
    AmobaGrid* grid = nullptr;

    event ev;
    while(gin >> ev) {
        gout << color(230, 204, 255) << move_to(0, 0) << box(400, 400);

        if (!show_grid) {
            gout << color(75, 0, 130) << move_to(150, 180) << box(100, 40);
            gout << color(255, 255, 255) << move_to(170, 190) << text("START");

            if (gameOver) {
                gout << font("LiberationSans-Regular.ttf", 30);
                gout << color(0, 0, 0);
                if (winner != ' ') {
                    gout << move_to(140, 120)
                         << text("Győztes: ") << text(string(1, winner));
                } else {
                    gout << move_to(160, 120)
                         << text("Döntetlen!");
                }

                gout << font("LiberationSans-Regular.ttf", 20);
                gout << move_to(50, 250)
                     << text("Új játékhoz kattints a START gombra!");
            }

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
