#include "Player.h"

Player::Player(float x, float y, std::map<std::string, sf::Texture>  texture_sheets):
    textureSheets(texture_sheets), animationCut(0)
{
    this->setPosition(x, y);

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

    this->plaingAnimation = !this->animationComponent->play(this->getMovingState(this->moveToKey), dt);
    }
}

void Player::startAnimation(std::string key){
    this->moveToKey = key;
    this->plaingAnimation = true;
}

sf::Vector3f Player::lookingAt(){
    return this->look;
}

std::string Player::getMovingState(std::string key){

    if (key == "UP" || "DOWN"){
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
    else if(key == "RIGHT" || "LEFT"){
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
