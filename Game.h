#ifndef GAME_H
#define GAME_H

//#include "State.h"
#include "MainMenuState.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void endAplication();
        void render();

        void updateDt();
        void updateSFMLEvent();
        void update();

        void run();

    protected:

    private:
        sf::RenderWindow *window;
        sf::Event sfEvent;
        std::vector<sf::VideoMode> videoModes;
        sf::ContextSettings windowSettings;
        bool fullscreen;

        sf::Clock dtClock;
        float dt;

        std::stack<State*> states;


        std::map<std::string, int> supportedKeys;

        void initVariables();
        void initWindow();
        void initKeys();
        void initStates();
};

#endif // GAME_H
