#include<SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape button_shape;
    sf::Vector2f button_position;
    sf::Vector2f button_size;
    sf::Color button_color;
    sf::Text label;
    sf::String button_label;
    sf::Font button_label_font;
    int button_label_size;
    sf::Vector2f button_label_position;
    sf::Color button_label_color;

public:
    Button(sf::Vector2f button_position, sf::Vector2f button_size, sf::Color button_color, sf::String button_label, sf::Font button_label_font, int button_label_size, sf::Vector2f button_label_position, sf::Color button_label_color);

    bool ButtonClicked(sf::Vector2i mouse_position);

    sf::RectangleShape& getShape();
    sf::Text& getLabel();
};