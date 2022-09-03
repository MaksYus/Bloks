#ifndef ENTITY_H
#define ENTITY_H

#include<AnimationComponent.h>

class Entity
{
    public:
        Entity(int(&arrMap)[11][19]);
        virtual ~Entity();

        virtual sf::Vector3f lookingAt();

        void setTexture(sf::Texture& texture);
        void createAnimationComponent();

        virtual void update(const float& dt );
        virtual void render(sf::RenderTarget& target);

        virtual void setPosition(const float x, const float y);
        virtual void move(const float x, const float y, const float& dt);

    protected:
        sf::Sprite sprite;

        AnimationComponent* animationComponent;

    private:
        sf::Vector2f position;
        int moveTimer;
        void initVariables();
        int arrMap[19][11];
        bool checkMap(int i, int j);
};

#endif // ENTITY_H
