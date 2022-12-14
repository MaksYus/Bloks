#ifndef ENTITY_H
#define ENTITY_H

#include<AnimationComponent.h>

class Entity
{
    public:
        Entity(sf::Vector2i position,int(&arrMap)[11][19], int moveCooldown);
        virtual ~Entity();

        virtual sf::Vector3f lookingAt();

        void setTexture(sf::Texture& texture);
        void createAnimationComponent();

        virtual void update(const float& dt );
        virtual void render(sf::RenderTarget& target);

        virtual void setSpritePosition(const float x, const float y);
        virtual sf::Vector2i getPosition();
        virtual bool setPosition(const int x, const int y);
        virtual void move(const float x, const float y, const float& dt);
        bool checkMap(int i, int j);

        int moveTimer;
        int moveCooldown;
        sf::Vector2i position;

    protected:
        sf::Sprite sprite;

        AnimationComponent* animationComponent;

    private:
        void initVariables();
        int arrMap[19][11];
};

#endif // ENTITY_H
