#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include"GameState.h"
//#include"EditorState.h"
#include"Button.h"

class MainMenuState:
    public State
{
     public:
        MainMenuState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
        virtual ~MainMenuState();

        void updateInput(const float& dt);
        void updateButtons();
        void updateAnimation(const float& dt);
        void update(const float& dt);
        void renderButtons(sf::RenderTarget& target);
        void render(sf::RenderTarget* target = NULL);

    protected:

    private:
        sf::RectangleShape background;
        sf::Font font;
        sf::Texture bgTexture;
        sf::Sprite bgSprite;
        sf::Texture bgTextureSheet;

        AnimationComponent* animationComponent;


        std::map<std::string, Button*> buttons;
        std::map<std::string, Button*>::iterator it = buttons.begin();

        bool animationNMPlaing;

        void initAnimations();
        void initVariables();
        void initBackground();
        void initFonts();
        void initKeybinds();
        void initButtons();
};

#endif // MAINMENUSTATE_H
