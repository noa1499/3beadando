#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include "graphics.hpp"
#include <string>

using namespace std;

class Widget {
protected:
    int _x, _y, _sx, _sy;
public:
    Widget(int x, int y, int sx, int sy);
    virtual ~Widget() {}
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
};

class Button : public Widget {
    string _text;
    bool _pressed;
public:
    Button(int x, int y, int sx, int sy, const string& text);
    void draw() override;
    void handle(genv::event ev) override;
    bool is_pressed() const;
    void reset();
};

#endif
