#include "Entity.h"

Entity::Entity(sf::Vector2i position,int(&arrMap)[11][19]):
    position(position)
{
    for(int i = 0; i < 11; i++){
        for(int j = 0;j < 19; j++){
            this->arrMap[j][i] = arrMap[i][j];
            std::cout << arrMap[i][j] << " ";
        }
        std::cout << std::endl;
    }

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

    //std::cout << this->position.x <<" "<< this->position.y<<std::endl;

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

void Entity::setSpritePosition(const float x, const float y){
           this->sprite.setPosition(x, y);
}

bool Entity::setPosition(const int x, const int y){
    if (this->checkMap(x,y)){
        this->setSpritePosition(x*100 + 10, y*100 + 27);
        this->position = sf::Vector2i(x,y);
        return true;
    }
    else return false;
}

sf::Vector2i Entity::getPosition(){
    return this->position;
}

bool Entity::checkMap(int i, int j){
    return this->arrMap[i][j];
}

void Entity::move(const float dir_x, const float dir_y, const float& dt){
    this->moveTimer++;
    if (this->moveTimer >= 11 ){
        if((this->position.x == 18 & dir_x > 0) || (this->position.y == 10 & dir_y > 0) || (this->position.y == 0 & dir_y < 0) || (this->position.x == 0 & dir_x < 0)) {}
        else{
            if(this->checkMap(this->position.x+dir_x,this->position.y+dir_y)){
                this->position += sf::Vector2i(dir_x*1,dir_y*1);
                this->sprite.move(dir_x*100, dir_y*100);
                this->moveTimer = 0;
            }
        }
    }
}


