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
public:
    AmobaGrid(int x, int y, int sx, int sy);
    virtual void draw() override;
    virtual void handle(event ev) override;
};

#endif
