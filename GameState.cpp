#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states):
     State(window, supportedKeys,states)
{
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState()
{
    delete this->player;
}

void GameState::initKeybinds(){
    std::ifstream ifs("Config/GameState_Keybinds.ini");

    if(ifs.is_open()){
            std::string key = "";
            std::string key2 = "";

            while (ifs >> key >> key2){
                this->keybinds[key] = this->supportedKeys->at(key2);
            }
    }
    else {
        std::cout << "ERROR! cunt open Config/GameState_Keybinds.ini" << std::endl;
    }
    ifs.close();
}

void GameState::update(const float& dt){
        this->updateMousePosition();
        this->updateInput(dt);
        this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target){
    if (!target)
        target = this->window;
    this->player->render(*target);

}


void GameState::updateInput(const float& dt){

    //Update player Input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->endState();
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACT"))))
        this->player->interact(*this->player);*/
}

void GameState::initTextures(){
    sf::Texture temp;
    if(!temp.loadFromFile("ResourceFiles/Images/Sprites/player/Dwarf Left Animation.png"))
        std::cout << "ERROR! cun't load texture player" << std::endl;
    this->textures["PLAYER_SHEET"] = temp;
}

void GameState::initPlayers(){
    this->player = new Player(20, 5, this->textures);
}
