#include "Button.h"

Button::Button(float x, float y, float width, float height,
                sf::Font* font, std::string text, unsigned character_size,
                sf::Color text_tdle_color, sf::Color text_hover_colot, sf::Color text_active_color,
                 sf::Color idle_color,sf::Color hover_color ,sf::Color active_color)
{
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->shape.setFillColor(idle_color);

    this->buttonState = BTN_IDLE;

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_tdle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
    this->shape.getPosition().x + (width / 2.f) - this->text.getGlobalBounds().width /2.f ,
    this->shape.getPosition().y +(height / 2.f) - this->text.getGlobalBounds().height /2.f
    );

    this->textIdleColor = text_tdle_color;
    this->textActiveColor = text_active_color;
    this->textHoverColor = text_hover_colot;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;
}

Button::~Button()
{

}

const bool Button::isPressed() const{
    return this->buttonState == BTN_ACTIVE;
}

void Button::render(sf::RenderTarget& target){
    target.draw(this->shape);
    target.draw(this->text);
}

void Button::update(const sf::Vector2f mousePos){
    this->buttonState = BTN_IDLE;
    if(this->shape.getGlobalBounds().contains(mousePos)){
        this->buttonState = BTN_HOVER;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch(this->buttonState){
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        this->text.setFillColor(this->textIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}
