#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player:
    public Entity
{
    public:
        Player( sf::Vector2i position, std::map<std::string, sf::Texture> texture_sheets, int(&arrMap)[11][19]);
        virtual ~Player();

        virtual sf::Vector3f lookingAt();
        void startAnimation(std::string key);
        virtual void update(const float&dt);

        std::string getMovingState(std::string key);

    protected:

    private:
        void initVariables();
        void initComponents();
        void initAnimations();
        void updateAnimation(const float & dt);

        bool plaingAnimation;
        bool animationCut;
        std::string moveToKey;
        sf::Vector3f look;

        std::map<std::string, sf::Texture>  textureSheets;
};

#endif // PLAYER_H
