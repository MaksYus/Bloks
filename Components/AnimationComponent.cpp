#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite):
    sprite(sprite), lastAnimation(NULL), priorityAnimation(NULL)
{
    //ctor
}

AnimationComponent::~AnimationComponent()
{
    this->it_animations = this->animations.begin();
    for (int i = 0; this->it_animations != this->animations.end(); this->it_animations++, i++)
        delete this->it_animations->second;
}

const bool & AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

void AnimationComponent::addAnimation(sf::Texture& textureSheet, const std::string key,
                                      float animationTimer,
                                      int start_x, int start_y, int end_x, int end_y, int width, int height){
    this->animations[key] = new Animation(this->sprite, textureSheet,
                                      animationTimer,
                                      start_x, start_y,end_x,end_y, width, height);
}

const bool & AnimationComponent::playSingle(const std::string key, const float& dt, const bool priority){
if (this->priorityAnimation) //If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(std::string key, const float& dt, const bool priority){
    bool done = true;
        done = done && this->playSingle(key,dt,priority);

	return done;
}

