#ifndef ENTITY_H
#define ENTITY_H

#include<AnimationComponent.h>

class Entity
{
    public:
        Entity();
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
        void initVariables();
};

#endif // ENTITY_H
