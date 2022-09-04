#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states):
     State(window, supportedKeys,states)
{
    this->initKeybinds();
    this->initTextures();
    this->initBackground();
    this->initMap();
    this->initPlayers();
    this->initEvents();
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
    target->draw(this->background);
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


    sf::Vector2i playerPosition = this->player->getPosition();
    for (this->it_eventsPosition = this->eventsPosition.begin(); this->it_eventsPosition != this->eventsPosition.end(); this->it_eventsPosition++){
        if(this->it_eventsPosition->second == playerPosition){
            this->startEvent(this->it_eventsPosition->first);
        }
    }
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
    this->player = new Player(sf::Vector2i(5,3), this->textures, this->arrMap);
}

void GameState::initEvents(){
    this->eventsPosition["QUIT"] = sf::Vector2i(5,5);
    this->eventsPosition["MAP1"] = sf::Vector2i(7,5);
    this->eventsPosition["MAP2"] = sf::Vector2i(9,5);
    this->eventsPosition["MAP3"] = sf::Vector2i(11,5);
    this->eventsPosition["MAP4"] = sf::Vector2i(13,5);
}

void GameState::initMap(){
    //Временное решение
    int arrMap[11][19]= {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    for(int i = 0; i < 11; i++){
        for(int j = 0; j<19; j++){
            this->arrMap[i][j] = arrMap[i][j];
        }
    }
}

void GameState::initBackground(){
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

    if(this->bgTexture.loadFromFile("ResourceFiles/Images/Backgrounds/GameState.png")){
        this->background.setTexture(&this->bgTexture);
    }
    else {
        std::cout << "ERROR! cunt load background gamestate" << std::endl;
    }
}

void GameState::startEvent(std::string key){
    if(key == "QUIT"){
        this->endState();
    }
    else if(key == "MAP1"){
        this->player->setPosition(5,3);
    }
    else if(key == "MAP2"){
        this->player->setPosition(5,3);
    }
    else if(key == "MAP3"){
        this->player->setPosition(5,3);
    }
    else if(key == "MAP4"){
        this->player->setPosition(5,3);
    }
}

void GameState::eventOnPosition(){

}
