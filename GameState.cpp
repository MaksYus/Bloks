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
    //this->logEvents();
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))){
        this->player->move(0.f, -1.f, dt);
        this->checkEvent(this->player->getPosition());
        this->checkEvent(this->player->getSecondPosition());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))){
        this->player->move(0.f, 1.f, dt);
        this->checkEvent(this->player->getPosition());
        this->checkEvent(this->player->getSecondPosition());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))){
        this->player->move(-1.f, 0.f, dt);
        this->checkEvent(this->player->getPosition());
        this->checkEvent(this->player->getSecondPosition());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))){
        this->player->move(1.f, 0.f, dt);
        this->checkEvent(this->player->getPosition());
        this->checkEvent(this->player->getSecondPosition());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))){
        this->endState();
        this->checkEvent(this->player->getPosition());
        this->checkEvent(this->player->getSecondPosition());
    }
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

void GameState::initEvents(std::string mapName){
    std::ifstream ifs("Maps/Events/" + mapName + ".txt");
    std::string title = "None";
    if(ifs.is_open()){
        std::getline(ifs,title);
        std::string elemIfs = "";
        ifs >> elemIfs;
        while(elemIfs != "EVENTS_END"){
            std::string stepKey = "";
            int lineEvent = 0;
            int rowEvent = 0;
            Event eve = Event();
            while(true){
                Step step = Step();
                while (true){
                    if(elemIfs == ";"|| elemIfs == "EVENT_END") {if(lineEvent > 2){eve.steps.push_back(step);} break;}
                    if(lineEvent == 0) eve.eventType = elemIfs;
                    if(lineEvent == 1) eve.name = elemIfs;
                    if(lineEvent == 2 && rowEvent == 0) eve.position.x = std::stoi(elemIfs);
                    if(lineEvent == 2 && rowEvent == 1) eve.position.y = std::stoi(elemIfs);
                    if(lineEvent >= 3 && rowEvent == 0) stepKey = elemIfs;
                    if(lineEvent >= 3) step.createEventStep(elemIfs, stepKey, rowEvent);
                    ifs >> elemIfs;
                    rowEvent++;
                }
                ifs >> elemIfs;
                if(elemIfs == "EVENT_END" || elemIfs == "EVENTS_END") {
                    this->events[eve.name] = eve;
                    break;
                }
                rowEvent = 0;
                lineEvent++;
            }

            ifs >> elemIfs;
            if(elemIfs == "EVENTS_END"){break;}
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
    std::cout << key << std::endl;
    std::list<Step> eventSteps = this->events[key].steps;
    for(std::list<Step>::iterator it_steps = eventSteps.begin(); it_steps != eventSteps.end(); it_steps++){
        Step step = *it_steps;
        if(step.stepName == "teleport") this->eventTeleport(step.positionToTp);
        if(step.stepName == "loadMap") this->eventLoadMap(step.mapNameToLoad);
        if(step.stepName == "endState") this->eventQuit();
    }
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

void GameState::logEvents(){
    for(this->it_events = this->events.begin(); this->it_events != this->events.end(); this->it_events++){
        std::cout << this->it_events->second.eventType<< " " << this->it_events->second.name<<" position: "<<this->it_events->second.position.x<<" "<< this->it_events->second.position.y<< " count steps: " << this->it_events->second.steps.size()<<std::endl;
    }
}

void GameState::logSteps(std::string eventName){
    std::list<Step> steps = this->events[eventName].steps;
    for(std::list<Step>::iterator it_steps = steps.begin(); it_steps != steps.end();it_steps++){
        std::cout << it_steps->stepName << " "<< it_steps->positionToTp.x << " "<<it_steps->positionToTp.y << " " <<it_steps->mapNameToLoad << " "<<it_steps->endState << std::endl;
    }
}
