#include "amobagrid.hpp"
#include "graphics.hpp"

using namespace std;

AmobaGrid::AmobaGrid(int x, int y, int sx, int sy)
    : Widget(x, y, sx, sy),
      _cell_size(sx / 15),
      _grid(15, vector<char>(15, ' ')),
      _currentPlayer('X') {} // Kezdő játékos: X

void AmobaGrid::draw() {
    // Háttér
    gout << color(255, 255, 255)
         << move_to(_x, _y)
         << box(_size_x, _size_y);

    // Rács vonalak
    gout << color(0, 0, 0);
    for (int i = 0; i <= 15; ++i) {
        gout << move_to(_x, _y + i * _cell_size)
             << line_to(_x + _size_x, _y + i * _cell_size);
        gout << move_to(_x + i * _cell_size, _y)
             << line_to(_x + i * _cell_size, _y + _size_y);
    }

    // (X és O)
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (_grid[i][j] == 'X') {
                gout << color(255, 0, 0) // Piros X
                     << move_to(_x + j*_cell_size + 5, _y + i*_cell_size + 5)
                     << text("X");
            } else if (_grid[i][j] == 'O') {
                gout << color(0, 0, 255) // Kék O
                     << move_to(_x + j*_cell_size + 5, _y + i*_cell_size + 5)
                     << text("O");
            }
        }
    }
}

void AmobaGrid::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        int cell_x = (ev.pos_x - _x) / _cell_size;
        int cell_y = (ev.pos_y - _y) / _cell_size;
        if (cell_x >= 0 && cell_x < 15 && cell_y >= 0 && cell_y < 15) {
            if (_grid[cell_y][cell_x] == ' ') {
                _grid[cell_y][cell_x] = _currentPlayer;
                _currentPlayer = (_currentPlayer == 'X') ? 'O' : 'X'; // Játékos váltás
            }
        }
    }
}
