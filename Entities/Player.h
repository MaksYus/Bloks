#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player:
    public Entity
{
    public:
        Player( sf::Vector2i position, std::map<std::string, sf::Texture> texture_sheets, int(&arrMap)[11][19], int moveCooldown);
        virtual ~Player();

        virtual sf::Vector3f lookingAt();
        void startAnimation(std::string key);
        virtual void update(const float&dt);

        virtual void move(const float dir_x, const float dir_y, const float& dt);
        std::string getMovingState(std::string key);

    protected:

    private:
        void initVariables();
        void initComponents();
        void initAnimations();
        void updateAnimation(const float & dt);
        void move1(const float dir_x, const float dir_y);

        bool plaingAnimation;
        bool animationCut;
        std::string moveToKey;
        sf::Vector3f look;
        sf::Vector2i secondPosition;

        std::map<std::string, sf::Texture>  textureSheets;
};

#endif // PLAYER_H
