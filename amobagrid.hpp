#ifndef AMOBAGRID_HPP
#define AMOBAGRID_HPP

#include "widgets.hpp"
#include <vector>

using namespace std;
using namespace genv;

class AmobaGrid : public Widget {
private:
    vector<vector<char>> _grid;
    int _cell_size;
    char _currentPlayer;
    char _winner;
    bool _gameOver;
public:
    AmobaGrid(int x, int y, int sx, int sy);
    virtual void draw() override;
    virtual void handle(event ev) override;
    bool checkWin(int x, int y); // Győzelem ellenőrzése
    bool checkDraw(); // Döntetlen ellenőrzése
};

#endif
