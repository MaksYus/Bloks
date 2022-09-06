#ifndef LEVEL1_H
#define LEVEL1_H

#include "State.h"

class Level1 : public State
{
    public:
        Level1(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
        virtual ~Level1();

        void updateInput(const float& dt);
        void update(const float& dt);
        void render(sf::RenderTarget* target = NULL);

    protected:

    private:
        sf::RectangleShape background;
        sf::Texture bgTexture;
        Player *player;
        std::map<std::string,sf::Vector2i> eventsPosition;
        std::map<std::string,sf::Vector2i>::iterator it_eventsPosition = eventsPosition.begin();

        void initKeybinds();
        void initTextures();
        void initPlayers();
        void initMap();
        void initEvents();
        void initBackground();

        void startEvent(std::string key);
        void eventOnPosition();
        int arrMap[11][19];
};

#endif // LEVEL1_H
