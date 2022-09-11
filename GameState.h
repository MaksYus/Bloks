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
        sf::Vector2i playerPosition;
        int playerSpeed;
        std::map<std::string,sf::Vector2i> eventsPosition;
        std::map<std::string,sf::Vector2i>::iterator it_eventsPosition = eventsPosition.begin();
        //std::map<std::string,std::li> eventsPosition;
        //std::map<std::string,sf::Vector2i>::iterator it_eventsPosition = eventsPosition.begin();

        void initKeybinds();
        void initTextures();
        void initPlayers();
        void initMap(std::string mapName);
        void drawMap(sf::RenderTarget* target);
        void createEventStep(std::string key, std::string eventKey, int row);
        void initEvents(std::string mapName);
        void initBackground();

        void startEvent(std::string key);
        void eventOnPosition();
        void eventTeleport(const int x, const int y);
        void eventQuit();
        void eventLoadMap(std::string mapName);
        int arrMap[11][19];
};

#endif // GAMESTATE_H
