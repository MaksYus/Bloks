#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State
{
    public:
        GameState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
        virtual ~GameState();

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
        void drawMap(sf::RenderTarget* target);
        void initEvents();
        void initBackground();

        void startEvent(std::string key);
        void eventOnPosition();
        int arrMap[11][19];
};

#endif // GAMESTATE_H
