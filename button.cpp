#include "button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::String llabel, sf::Font lfont, int lsize, sf::Vector2f lposition, sf::Color lcolor) {
    button_position = position, button_size = size, button_color = color, button_label = llabel, button_label_font = lfont, button_label_size = lsize, button_label_position = lposition, button_label_color = lcolor;
    button_shape.setPosition(button_position);
    button_shape.setSize(button_size);
    button_shape.setFillColor(button_color);
    label.setString(button_label);
    label.setFont(button_label_font);
    label.setCharacterSize(button_label_size);
    label.setPosition(button_label_position);
    label.setFillColor(button_label_color);
}

bool Button::ButtonClicked(sf::Vector2i mouse_position) {
    if (mouse_position.x >= button_position.x && mouse_position.x <= button_position.x + button_size.x && mouse_position.y >= button_position.y && mouse_position.y <= button_position.y + button_size.y) return 1;
    return 0;
}

sf::RectangleShape& Button::getShape() {
    return button_shape;
}

sf::Text& Button::getLabel() {
    return label;
}