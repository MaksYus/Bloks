#include "Entity.h"

Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->animationComponent;
}

void Entity::update(const float& dt){
    std::cout << "entity update" << std::endl;
}

void Entity::render(sf::RenderTarget& target){
    target.draw(this->sprite);
}

void Entity::initVariables(){
    this->animationComponent = NULL;
    this->position = sf::Vector2f(0,0);
}

sf::Vector3f Entity::lookingAt(){
    return sf::Vector3f(1,0,0);
}

void Entity::setTexture(sf::Texture& texture){
    this->sprite.setTexture(texture);
}

void Entity::createAnimationComponent(){
    this->animationComponent = new AnimationComponent(this->sprite);
}

void Entity::setPosition(const float x, const float y){
           this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt){
    this->position += sf::Vector2f(dir_x,dir_y);
    this->sprite.move(dir_x*dt*10, dir_y*dt*10);
}


