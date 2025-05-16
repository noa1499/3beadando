#include "widgets.hpp"

using namespace genv;

Widget::Widget(int x, int y, int sx, int sy)
    : _x(x), _y(y), _size_x(sx), _size_y(sy) {}

Button::Button(int x, int y, int sx, int sy, const std::string& text)
    : Widget(x, y, sx, sy), _text(text), _pressed(false) {}

void Button::draw() {
    gout << move_to(_x, _y) << color(200,200,200);
    gout << box(_size_x, _size_y);
    gout << color(0,0,0);
    gout << move_to(_x + 15, _y + _size_y / 2 - 10) << text(_text);
}

void Button::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (ev.pos_x >= _x && ev.pos_x < _x + _size_x &&
            ev.pos_y >= _y && ev.pos_y < _y + _size_y) {
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
