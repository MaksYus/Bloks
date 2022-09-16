#ifndef ANIMATION_H
#define ANIMATION_H

#include<iostream>
#include<map>
#include<list>
#include<fstream>
#include<sstream>
#include<vector>

#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

class Animation
{
    public:
        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
                float animation_timer,
                int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);
        virtual ~Animation();



		const bool& isDone() const;
		const bool& play(const float& dt);
		const bool& play(const float& dt, float mod_percent);
		void reset();

    protected:

    private:
        bool done;
        float animationTimer;
		float timer;

		int width;
		int height;

		sf::Sprite& sprite;
		sf::Texture& textureSheet;

		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;
};

#endif // ANIMATION_H
