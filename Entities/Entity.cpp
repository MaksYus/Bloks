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

    std::cout << this->position.x <<" "<< this->position.y<<std::endl;

    sf::Text EntityPositionText;
    EntityPositionText.setPosition(this->position.x, this->position.y - 20);
    EntityPositionText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->position.x << " " << this->position.y;
    EntityPositionText.setString(ss.str());

    target.draw(EntityPositionText);
}

void Entity::initVariables(){
    this->animationComponent = NULL;
    this->position = sf::Vector2f(0,0);
    this->moveTimer = 0;
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
    this->moveTimer++;
    if (this->moveTimer >= 11 ){
        if((this->position.x == 18 & dir_x > 0) || (this->position.y == 10 & dir_y > 0) || (this->position.y == 0 & dir_y < 0) || (this->position.x == 0 & dir_x < 0)) {}
        else{
            this->position += sf::Vector2f(dir_x*1,dir_y*1);
            this->sprite.move(dir_x*100, dir_y*100);
            this->moveTimer = 0;
        }
    }
}


