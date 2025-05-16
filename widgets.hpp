#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include "graphics.hpp"
#include <string>

using namespace std;
using namespace genv;

class Widget {
protected:
    int _x, _y, _size_x, _size_y;
public:
    Widget(int x, int y, int sx, int sy);
    virtual ~Widget() {}
    virtual void draw() = 0;
    virtual void handle(event ev) = 0;
};

class Button : public Widget {
    string _text;
    bool _pressed;
public:
    Button(int x, int y, int sx, int sy, const string& text);
    void draw() override;
    void handle(event ev) override;
    bool is_pressed() const;
    void reset();
};

#endif
