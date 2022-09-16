#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include"Animation.h"


class AnimationComponent
{
private:

	sf::Sprite& sprite;
	std::map<std::string, Animation*> animations;
	std::map<std::string, Animation*>::iterator it_animations = animations.begin();
	Animation* lastAnimation;
	Animation* priorityAnimation;

	const bool & playSingle(const std::string key, const float& dt, const bool priority = false);

public:
	AnimationComponent(sf::Sprite& sprite);
	virtual ~AnimationComponent();

	//Accessor
	const bool& isDone(const std::string key);

	//Functions
	void addAnimation(sf::Texture& textureSheet,const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

#endif // ANIMATIONCOMPONENT_H
