#include "widgets.hpp"

using namespace genv;

Widget::Widget(int x, int y, int sx, int sy)
    : _x(x), _y(y), _sx(sx), _sy(sy)
{}

Button::Button(int x, int y, int sx, int sy, const std::string& text)
    : Widget(x,y,sx,sy), _text(text), _pressed(false)
{}

void Button::draw() {
    gout << move_to(_x, _y) << color(200,200,200);
    gout << box(_sx, _sy);
    gout << color(0,0,0);
    gout << move_to(_x+15, _y + _sy/2 - 10) << text(_text);
}

void Button::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (ev.pos_x >= _x && ev.pos_x < _x + _sx &&
            ev.pos_y >= _y && ev.pos_y < _y + _sy) {
            _pressed = true;
        }
    }
}
bool Button::is_pressed() const {
    return _pressed;
}

void Button::reset() {
    _pressed = false;
}
