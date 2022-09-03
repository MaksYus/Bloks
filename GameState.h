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
        Player *player;

        void initKeybinds();
        void initTextures();
        void initPlayers();
        void initMap();
        int arrMap[11][19]= {
    {1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0}
    };
};

#endif // GAMESTATE_H
