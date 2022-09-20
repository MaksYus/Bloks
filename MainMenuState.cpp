#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states):
     State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initAnimations();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

}

MainMenuState::~MainMenuState()
{
    for (int i = 0; this->it != this->buttons.end(); this->it++, i++)
        delete this->it->second;
   // delete this->gamestate_btn;
   delete this->animationComponent;
}

void MainMenuState::updateAnimation(const float& dt, std::string key){
        this->animationComponent->play(key, dt);
}

void MainMenuState::initAnimations(){
    this->animationComponent = new AnimationComponent(this->bgSprite);
    this->animationComponent->addAnimation(this->bgTextureSheet,"NEXTMENU",20.f,0,0, 8,0,64,64);
}

void MainMenuState::initVariables(){

}

void MainMenuState::initBackground(){
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

    if(this->bgTexture.loadFromFile("ResourceFiles/Images/Backgrounds/MainMenu.png")){
        this->background.setTexture(&this->bgTexture);
    }
    else {
        std::cout << "ERROR! �� ������� ��������� ������ �������� ����" << std::endl;
    }


    //� �������� ���������
    //Animation(sf::Sprite& ������� ������, sf::Texture& ���� �� ����� ���������,
    //            float animation_timer,
    //            int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);
}

void MainMenuState::initFonts(){
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf")){
        throw("ERROR::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initKeybinds(){
    std::ifstream ifs("Config/MainMenu_Keybinds.ini");

    if(ifs.is_open()){
            std::string key = "";
            std::string key2 = "";

            while (ifs >> key >> key2){
                this->keybinds[key] = this->supportedKeys->at(key2);
            }
    }
    else{
        std::cout << "ERROR! �� ������� ������� Config/MainMenu_Keybinds.ini" << std::endl;
    }
    ifs.close();
}

void MainMenuState::initButtons(){
    this->buttons["GAME_STATE"] = new Button(
                                             1600.f, 100.f, 150.f, 50.f,
                                             &this->font, "New Game", 30,
                                             sf::Color(255,255,255,200), sf::Color(255,255,255,200), sf::Color(255, 255, 255, 200),
                                             sf::Color(70, 70, 70, 200),
                                             sf::Color(150,150,150,200),
                                             sf::Color(20, 20, 20, 255));
    this->buttons["SETTINGS_STATE"] = new Button(1600.f, 160.f, 150.f, 50.f,
                                     &this->font, "Settings",30,
                                             sf::Color(255,255,255,200), sf::Color(255,255,255,200), sf::Color(255, 255, 255, 200),
                                      sf::Color(70, 70, 70, 200),
                                     sf::Color(150,150,150,200),
                                     sf::Color(20, 20, 20, 255));
    this->buttons["TEST_STATE"] = new Button(1600.f, 220.f, 150.f, 50.f,
                                     &this->font, "TEST",30,
                                             sf::Color(255,255,255,200), sf::Color(255,255,255,200), sf::Color(255, 255, 255, 200),
                                      sf::Color(70, 70, 70, 200),
                                     sf::Color(150,150,150,200),
                                     sf::Color(20, 20, 20, 255));
     this->buttons["EXIT_STATE"] = new Button(1600.f, 950.f, 150.f, 50.f,
                                     &this->font, "Quit",30,
                                             sf::Color(255,255,255,200), sf::Color(255,255,255,200), sf::Color(255, 255, 255, 200),
                                      sf::Color(70, 70, 70, 200),
                                     sf::Color(150,150,150,200),
                                     sf::Color(20, 20, 20, 255));

}

void MainMenuState::update(const float& dt){
    this->updateMousePosition();
    this->updateInput(dt);

    this->updateButtons();

}

void MainMenuState::updateButtons(){

    this->it = this->buttons.begin();
    for (int i = 0; this->it != this->buttons.end(); this->it++, i++)
        this->it->second->update(this->mousePosView);

    if(this->buttons["EXIT_STATE"]->isPressed()){
        this->endState();
    }

    if(this->buttons["GAME_STATE"]->isPressed()){
        this->states->push(new GameState("Map0",this->window, this->supportedKeys, this->states));
    }

    if(this->buttons["TEST_STATE"]->isPressed()){
    //    ������ ������������ ��������
    }
}

void MainMenuState::renderButtons(sf::RenderTarget& target){
    this->it = this->buttons.begin();
    for (int i = 0; this->it != this->buttons.end(); this->it++, i++)
        this->it->second->render(target);
}

void MainMenuState::render(sf::RenderTarget* target){
    if (!target)
        target = this->window;
    target->draw(this->background);
    this->renderButtons(*target);

    //TODO Remove
    sf::Text mouseText;
    mouseText.setPosition(this-> mousePosView.x, this->mousePosView.y-20);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);
}

void MainMenuState::updateInput(const float& dt){

   // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
   //         this->endState();
  //  if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))

}
