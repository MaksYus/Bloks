#ifndef BUTTON_H
#define BUTTON_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>

#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
    public:
        Button(float x, float y, float width, float height,
                sf::Font* font, std::string text,unsigned character_size,
                sf::Color text_tdle_color, sf::Color text_hover_colot, sf::Color text_active_color,
                 sf::Color idle_color,sf::Color hover_color, sf::Color active_color);
        virtual ~Button();

        const bool isPressed() const;

        void update(const sf::Vector2f mousePos);
        void render(sf::RenderTarget& target);

    protected:

    private:
        short unsigned buttonState;

        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;


};

#endif // BUTTON_H
