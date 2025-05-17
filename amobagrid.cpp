#include "amobagrid.hpp"
#include "graphics.hpp"

using namespace std;

AmobaGrid::AmobaGrid(int x, int y, int sx, int sy)
    : Widget(x, y, sx, sy),
      _cell_size(sx / 15),
      _grid(15, vector<char>(15, ' ')),
      _currentPlayer('X'),
      _winner(' '),
      _gameOver(false) {}

bool AmobaGrid::checkWin(int x, int y) {
    char player = _grid[y][x];
    if (player == ' ') return false;

    int dx[] = {1, 0, 1, 1};
    int dy[] = {0, 1, 1, -1};

    for (int dir = 0; dir < 4; ++dir) {
        int count = 1;
        for (int step = 1; step < 5; ++step) {
            int nx = x + dx[dir] * step;
            int ny = y + dy[dir] * step;
            if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) break;
            if (_grid[ny][nx] != player) break;
            count++;
        }
        for (int step = 1; step < 5; ++step) {
            int nx = x - dx[dir] * step;
            int ny = y - dy[dir] * step;
            if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) break;
            if (_grid[ny][nx] != player) break;
            count++;
        }
        if (count >= 5) {
            _winner = player;
            return true;
        }
    }
    return false;
}

bool AmobaGrid::checkDraw() {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (_grid[i][j] == ' ') return false;
        }
    }
    return true;
}

void AmobaGrid::draw() {
    // Háttér: középső lila (RGB: 153, 102, 204)
    gout << color(153, 102, 204)
         << move_to(_x, _y)
         << box(_size_x, _size_y);

    // Rács vonalak (fekete)
    gout << color(0, 0, 0);
    for (int i = 0; i <= 15; ++i) {
        gout << move_to(_x, _y + i * _cell_size)
             << line_to(_x + _size_x, _y + i * _cell_size);
        gout << move_to(_x + i * _cell_size, _y)
             << line_to(_x + i * _cell_size, _y + _size_y);
    }

    // Jelölések (X: arany, O: ezüst)
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (_grid[i][j] == 'X') {
                gout << color(255, 215, 0)
                     << move_to(_x + j*_cell_size + 5, _y + i*_cell_size + 5)
                     << text("X");
            } else if (_grid[i][j] == 'O') {
                gout << color(192, 192, 192)
                     << move_to(_x + j*_cell_size + 5, _y + i*_cell_size + 5)
                     << text("O");
            }
        }
    }

    // Győzelem/döntetlen üzenet
    if (_gameOver) {
        gout << font("LiberationSans-Regular.ttf", 40);
        if (_winner != ' ') {
            gout << color(0, 0, 0)
                 << move_to(_x + 100, _y + 200)
                 << text("Győztes: ") << text(string(1, _winner));
        } else {
            gout << color(0, 0, 0)
                 << move_to(_x + 100, _y + 200)
                 << text("Döntetlen!");
        }
    }
}

void AmobaGrid::handle(event ev) {
    if (!_gameOver && ev.type == ev_mouse && ev.button == btn_left) {
        int cell_x = (ev.pos_x - _x) / _cell_size;
        int cell_y = (ev.pos_y - _y) / _cell_size;
        if (cell_x >= 0 && cell_x < 15 && cell_y >= 0 && cell_y < 15 && _grid[cell_y][cell_x] == ' ') {
            _grid[cell_y][cell_x] = _currentPlayer;
            if (checkWin(cell_x, cell_y) || checkDraw()) {
                _gameOver = true;
            } else {
                _currentPlayer = (_currentPlayer == 'X') ? 'O' : 'X';
            }
        }
    }
}

// Új metódusok a játék állapotának lekérdezéséhez
bool AmobaGrid::isGameOver() const {
    return _gameOver;
}

char AmobaGrid::getWinner() const {
    return _winner;
}
