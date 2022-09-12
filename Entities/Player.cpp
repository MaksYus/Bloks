#include "Player.h"

Player::Player( sf::Vector2i position, std::map<std::string, sf::Texture>  texture_sheets, int(&arrMap)[11][19], int moveCooldown):
    textureSheets(texture_sheets), animationCut(0), Entity(position,arrMap,moveCooldown)
{
    this->setSpritePosition(position.x*100 + 10, position.y*100 + 27);
    this->secondPosition = sf::Vector2i(position.x + 1, position.y);

    this->initVariables();
    this->initComponents();
    this->initAnimations();
}

Player::~Player()
{
    //dtor
}

void Player::initVariables(){
    this->look = sf::Vector3f(1,0,0);
}

void Player::initComponents(){
    this->createAnimationComponent();
}

void Player::initAnimations(){
    std::cout << "TODO: PLAYER ANIMATION" << std::endl;

    //S - small
    //B - big
    //U - up
    //D - down
    //R - right
    //L - left
    this->animationComponent->addAnimation(this->textureSheets["PLAYER_SHEET"],"ROTATEBBU",20.f,0,0, 8,0,64,64);
    this->animationComponent->addAnimation(this->textureSheets["PLAYER_SHEET"],"ROTATEBBR",20.f,0,0, 8,0,64,64);
    this->animationComponent->addAnimation(this->textureSheets["PLAYER_SHEET"],"ROTATEBSU",3.5,0,1, 5,1,64,64);
    this->animationComponent->addAnimation(this->textureSheets["PLAYER_SHEET"],"ROTATEBSR",3.5,0,1, 5,1,64,64);
    this->animationComponent->addAnimation(this->textureSheets["PLAYER_SHEET"],"ROTATESBU",2.5,0,2,4,2,64,64);
    this->animationComponent->addAnimation(this->textureSheets["PLAYER_SHEET"],"ROTATESBR",2.5,0,2,4,2,64,64);
}

void Player::update(const float&dt){
    this->updateAnimation(dt);
    if (this->moveTimer > 0) {this->moveTimer--;}
}

void Player::updateAnimation(const float & dt)
{
    if(this->plaingAnimation){

    if(this->moveToKey == "UP" || "RIGHT"){//
        this->sprite.setOrigin(0.f,0.f);
        this->sprite.setScale(1.f,1.f);
    }
    else{//reverse
        this->sprite.setOrigin(55.f,0.f);
        this->sprite.setScale(-1.f,1.f);
    }

    //this->plaingAnimation = !this->animationComponent->play(this->getMovingState(this->moveToKey), dt);
    }
}

void Player::startAnimation(std::string key){
    this->moveToKey = key;
    this->plaingAnimation = true;
}

sf::Vector3f Player::lookingAt(){
    return this->look;
}

void Player::move(const float dir_x, const float dir_y, const float& dt){

    if (this->moveTimer <= 0 ){
        if((this->position.x == 18 & dir_x > 0) || (this->position.y == 10 & dir_y > 0) || (this->position.y == 0 & dir_y < 0) || (this->position.x == 0 & dir_x < 0)) {}//проверка на границы карты
        else{
                std::string direction = "";
                if(dir_x > 0) direction = "RIGHT";
                if(dir_x < 0) direction = "LEFT";
                if(dir_y < 0) direction = "UP";
                if(dir_y > 0) direction = "DOWN";
                std::string movingState = this->getMovingState(direction);
               // std::cout << dir_x << " " << dir_y << " "<< movingState << std::endl;
                //std::cout << "TODOTODOTODOTODO" << std::endl;
                if(movingState == "ROTATEBBU") {
                        //проверка возможности перемещения в точку
                        if(this->checkMap(this->secondPosition.x+dir_x,this->secondPosition.y+dir_y) && this->checkMap(this->position.x+dir_x,this->position.y+dir_y)){ //второстепенная && основная
                                this->move1(dir_x,dir_y);
                                this->secondPosition = sf::Vector2i(this->secondPosition.x + dir_x,this->secondPosition.y + dir_y);
                                //look не меняется
                        }
                }
                else if(movingState == "ROTATESBU"){
                        if( this->checkMap(this->secondPosition.x+dir_x*2,this->secondPosition.y+dir_y*2) && this->checkMap(this->position.x+dir_x,this->position.y+dir_y)){ // второстепенная + основная
                            if(direction == "UP"){
                                this->move1(dir_x*2,dir_y*2);
                                this->secondPosition = sf::Vector2i(this->secondPosition.x + dir_x,this->secondPosition.y + dir_y);
                            }
                            else{
                                this->move1(dir_x,dir_y);
                                this->secondPosition = sf::Vector2i(this->secondPosition.x+dir_x*2,this->secondPosition.y+dir_y*2);
                            }
                            this->look = sf::Vector3f(0,0,1);
                        }
                }
                else if(movingState == "ROTATEBSU"){
                        if(direction == "UP"){
                            if(this->checkMap(this->position.x+dir_x,this->position.y+dir_y)){ //основная
                                this->move1(dir_x,dir_y);
                                this->secondPosition = sf::Vector2i(this->position);
                                this->look = sf::Vector3f(0,1,0);
                            }
                        }
                        else{
                            if(this->checkMap(this->position.x+dir_x*2,this->position.y+dir_y*2)){ //основная
                                this->move1(dir_x*2,dir_y*2);
                                this->secondPosition = sf::Vector2i(this->position);
                                this->look = sf::Vector3f(0,1,0);
                            }
                        }

                }
                else if(movingState == "ROTATEBSR"){
                        if(direction == "RIGHT"){
                            if(this->checkMap(this->position.x+dir_x*2,this->position.y+dir_y*2)){//основная
                                this->move1(dir_x*2,dir_y*2);
                                this->secondPosition = sf::Vector2i(this->position);
                                this->look = sf::Vector3f(0,1,0);
                            }
                        }
                        else{
                            if(this->checkMap(this->position.x+dir_x,this->position.y+dir_y)){//основная
                                this->move1(dir_x,dir_y);
                                this->secondPosition = sf::Vector2i(this->position);
                                this->look = sf::Vector3f(0,1,0);
                            }
                        }

                }
                else if(movingState == "ROTATESBR"){
                        if(this->checkMap(this->position.x+dir_x*2,this->position.y+dir_y*2) && this->checkMap(this->position.x+dir_x,this->position.y+dir_y)){//второстепенная && основная
                            if(direction == "RIGHT"){
                                this->move1(dir_x,dir_y);
                                this->secondPosition = sf::Vector2i(this->secondPosition.x+dir_x*2,this->secondPosition.y+dir_y*2);
                            }
                            else{
                                this->move1(dir_x*2,dir_y*2);
                                this->secondPosition = sf::Vector2i(this->secondPosition.x+dir_x,this->secondPosition.y+dir_y);
                            }
                            this->look = sf::Vector3f(1,0,0);
                        }
                }
                else if(movingState == "ROTATEBBR"){
                        if(this->checkMap(this->position.x+dir_x,this->position.y+dir_y) && this->checkMap(this->secondPosition.x+dir_x,this->secondPosition.y+dir_y)){ //основная + второстепенная
                            this->move1(dir_x,dir_y);
                            this->secondPosition = sf::Vector2i(this->secondPosition.x + dir_x,this->secondPosition.y + dir_y);
                            //look не меняется
                            }
                }

                //std::cout << std::endl << "pos: " << this->position.x << " " << this->position.y << std::endl << " secpos: " << this->secondPosition.x << " " << this->secondPosition.y<< std::endl << "look: " << this->look.x << " " << this->look.y << " " << this->look.z<< std::endl;
        }
    }
}

bool Player::setPosition(const int x, const int y){
    if(this->checkMap(x,y)){
        this->position = sf::Vector2i(x,y);
        this->secondPosition = sf::Vector2i(x,y);
        this->setSpritePosition(position.x*100 + 10, position.y*100 + 27);
        this->look = sf::Vector3f(0,1,0);
    }
}

void Player::move1(const float dir_x, const float dir_y){
    this->position += sf::Vector2i(dir_x*1,dir_y*1);
    this->sprite.move(dir_x*100, dir_y*100);
    this->moveTimer = this->moveCooldown;
}

std::string Player::getMovingState(std::string key){
    //std::cout << this->look.x << " " << this->look.y << " "<<this->look.z << " "<< key << std::endl;
    if (key == "UP" || key == "DOWN"){
       if((this->look.x > this->look.y) && (this->look.x > this->look.z)){
            return "ROTATEBBU";
        }
        else if((this->look.y > this->look.x) && (this->look.y > this->look.z)){
            return "ROTATESBU";
        }
        else if((this->look.z > this->look.y) && (this->look.x < this->look.z)){
            return "ROTATEBSU";
        }
    }
    else if(key == "RIGHT" || key == "LEFT"){
        if((this->look.x > this->look.y) && (this->look.x > this->look.z)){
            return "ROTATEBSR";
        }
        else if((this->look.y > this->look.x) && (this->look.y > this->look.z)){
            return "ROTATESBR";
        }
        else if((this->look.z > this->look.y) && (this->look.x < this->look.z)){
            return "ROTATEBBR";
        }
    }
}


sf::Vector2i Player::getSecondPosition(){
    return this->secondPosition;
}
