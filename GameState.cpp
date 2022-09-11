#include "GameState.h"
#include "Level1.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states):
     State(window, supportedKeys,states)
{
    this->initKeybinds();
    this->initTextures();
    this->initBackground();
    this->initMap("Map0");
    this->initPlayers();
    this->initEvents("Map0");
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
    this->drawMap(target);
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

/*
    sf::Vector2i playerPosition = this->player->getPosition();
    sf::Vector2i playerSecondPosition = this->player->getSecondPosition();
    for (this->it_eventsPosition = this->eventsPosition.begin(); this->it_eventsPosition != this->eventsPosition.end(); this->it_eventsPosition++){
        if((this->it_eventsPosition->second == playerPosition) || (this->it_eventsPosition->second == playerSecondPosition)){
            this->startEvent(this->it_eventsPosition->first);
        }
    }*/
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INTERACT"))))
        this->player->interact(*this->player);*/
}

void GameState::initTextures(){
    sf::Texture temp;
    if(!temp.loadFromFile("ResourceFiles/Images/Sprites/player/Dwarf Left Animation.png"))
        std::cout << "ERROR! cun't load texture player" << std::endl;
    this->textures["PLAYER_SHEET"] = temp;

    if(!temp.loadFromFile("ResourceFiles/Images/Textures/GrassBlock.png"))
        std::cout << "ERROR! cun't load texture GrassBlock" << std::endl;
    this->textures["GRASS_BLOCK"] = temp;
}

void GameState::initPlayers(){
    this->player = new Player(this->playerPosition, this->textures, this->arrMap, this->playerSpeed);
}

void GameState::createEventStep(std::string eventName, std::string key, std::string eventKey, int row){
    if(row == 0 && eventKey != "-") {
        this->events[eventName].steps.push_back(Step(eventKey,sf::Vector2i(-1,-1),"",false));
    }
    if(eventKey == "teleport"){
        if(row == 1) this->events[eventName].steps.back().positionToTp.x = std::stoi(key);
        if(row == 2) this->events[eventName].steps.back().positionToTp.y = std::stoi(key);
    }
    if(eventKey == "loadMap"){
        if(row == 1) this->events[eventName].steps.back().mapNameToLoad = key;
    }
    if(eventKey == "endState"){
        this->events[eventName].steps.back().endState = true;
    }
}

void GameState::initEvents(std::string mapName){
    std::ifstream ifs("Maps/Events/" + mapName + ".txt");
    std::string title = "None";
    if(ifs.is_open()){
        std::getline(ifs,title);
        std::string eventType = "";
        std::string eventName = "";
        std::string elemIfs = "";
        ifs >> elemIfs;
        int lineEvent = 0;
        int rowEvent = 0;
        sf::Vector2i eventPosition = sf::Vector2i(-1,-1);

        while(elemIfs != "EVENT_END"){
            std::string eventKey = "";

            while (elemIfs != ";"){
                if(lineEvent == 0) eventType = elemIfs;
                if(lineEvent == 1) eventName = elemIfs;
                if(lineEvent == 2 && rowEvent == 0) eventPosition.x = std::stoi(elemIfs);
                if(lineEvent == 2 && rowEvent == 1) eventPosition.y = std::stoi(elemIfs);
                if(lineEvent >= 3 && rowEvent == 0) eventKey = elemIfs;
                if(lineEvent >= 3) this->createEventStep(eventName, elemIfs, eventKey, rowEvent);

                ifs >> elemIfs;
                rowEvent++;
            }
            if(eventPosition.x != -1 && eventPosition.y != -1 && lineEvent == 2) {
                this->events.insert(make_pair(eventName,Event(eventType,eventName,eventPosition)));
            }
            ifs >> elemIfs;

            if(elemIfs == "EVENT_END"){ break;}
            rowEvent = 0;
            lineEvent++;
        }
    }
    else{
        std::cout << "ERROR! COULD NOT OPEN Maps/Map0.txt" << std::endl;
    }
    ifs.close();
}

void GameState::initMap(std::string mapName){
    std::ifstream ifs("Maps/" + mapName + ".txt");
    std::string title = "None";
    int arrMap[11][19];
    if(ifs.is_open()){
        std::getline(ifs,title);
        for(int i = 0; i < 11; i++){
            for(int j = 0; j < 19; j++){
                ifs >> arrMap[i][j];
            }
        }
        ifs >> this->playerPosition.x >> this->playerPosition.y >> this->playerSpeed;
    }
    else{
        std::cout << "ERROR! COULD NOT OPEN Maps/Map0.txt" << std::endl;
    }
    ifs.close();

    for(int i = 0; i < 11; i++){
        for(int j = 0; j<19; j++){
            this->arrMap[i][j] = arrMap[i][j];
        }
    }
}

void GameState::drawMap(sf::RenderTarget* target){
    for (int i = 0; i < 11; i++){
        for(int j = 0; j < 19; j++){
            if(this->arrMap[i][j]){
                sf::Sprite temp = sf::Sprite(this->textures["GRASS_BLOCK"]);
                temp.setPosition(sf::Vector2f(j*100 + 10, i*100 + 27));
                target->draw(temp);
            }
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

void GameState::checkEvent(sf::Vector2i position){
    for(this->it_events = this->events.begin(); this->it_events != this->events.end();this->it_events++){
        if(this->it_events->second.position == position) this->startEvent(this->it_events->first);
    }
}

void GameState::startEvent(std::string key){
    std::list<Step> eventSteps = this->events[key].steps;
    std::cout << eventSteps.front().stepName << std::endl;
    /*std::list<Step> it_steps = eventSteps.begin();
    for(std::list<Step> it_steps = eventSteps.begin(); it_steps != eventSteps.end(); it_steps++){
        Step step = it_steps->first;
        if(step.stepName == "QUIT") this->eventQuit();
        if(step.stepName == "teleport") this->eventTeleport(step.positionToTp);
        if(step.stepName == "loadMap") this->eventLoadMap(step.mapNameToLoad);
    }*/
}

void GameState::eventOnPosition(){

}

void GameState::eventTeleport(const sf::Vector2i teleportTo){
    this->player->setPosition(teleportTo.x,teleportTo.y);
}

void GameState::eventQuit(){
    this->endState();
}

void GameState::eventLoadMap(std::string mapName){
    this->player->setPosition(this->playerPosition.x,this->playerPosition.y);
    this->states->push(new Level1(this->window, this->supportedKeys, this->states));
    this->endState();
}
