#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State
{
    public:
        GameState(std::string mapName, sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
        virtual ~GameState();

        void updateInput(const float& dt);
        void update(const float& dt);
        void render(sf::RenderTarget* target = NULL);

        struct Step{
        public:
            std::string stepName;
            sf::Vector2i positionToTp;
            std::string mapNameToLoad;
            bool endState;
            Step(){
                stepName = "NULL";
                positionToTp = sf::Vector2i(-1,-1);
                mapNameToLoad = "";
                endState = false;
            }
            Step(std::string Name, sf::Vector2i PositionToTp, std::string MapNameToLoad, bool EndState){
                stepName = Name;
                positionToTp = PositionToTp;
                mapNameToLoad = MapNameToLoad;
                endState = EndState;
            }
            void createEventStep(std::string key, std::string eventKey, int row){
                if(eventKey != "-"){
                //std::cout << eventName<< " " <<key<< " " <<eventKey << " " << row << std::endl;
                    if(row == 0 ) stepName = eventKey;
                    if(eventKey == "teleport"){
                        if(row == 1) positionToTp.x = std::stoi(key);
                        if(row == 2) positionToTp.y = std::stoi(key);
                    }
                    if(eventKey == "loadMap") if(row == 1) mapNameToLoad = key;
                    if(eventKey == "endState") endState = true;
                }
            }
        };
        struct Event{
        public:
            std::string eventType;
            std::string name;
            sf::Vector2i position;
            std::list<Step> steps;
            Event(){
                eventType = "NULL";
                name = "NULL";
                position = sf::Vector2i(-1,-1);
            }
            Event(std::string EventType,std::string Name,sf::Vector2i Position){
                eventType = EventType;
                name = Name;
                position = Position;
            }
        };

    protected:

    private:


        sf::RectangleShape background;
        sf::Texture bgTexture;
        Player *player;
        sf::Vector2i playerPosition;
        int playerSpeed;

        std::map<std::string,Event> events;
        std::map<std::string,Event>::iterator it_events = events.begin();

        void drawMap(sf::RenderTarget* target);
        void drawMiddle(int x, int y, sf::RenderTarget* target);
        void drawHoleU(int x, int y, sf::RenderTarget* target);
        void drawHoleD(int x, int y, sf::RenderTarget* target);
        void drawHoleR(int x, int y, sf::RenderTarget* target);
        void drawHoleL(int x, int y, sf::RenderTarget* target);
        void drawCornerUL(int x, int y, sf::RenderTarget* target);
        void drawCornerUR(int x, int y, sf::RenderTarget* target);
        void drawCornerDR(int x, int y, sf::RenderTarget* target);
        void drawCornerDL(int x, int y, sf::RenderTarget* target);
        void drawLineL(int x, int y, sf::RenderTarget* target);
        void drawLineR(int x, int y, sf::RenderTarget* target);
        void drawLineD(int x, int y, sf::RenderTarget* target);
        void drawDoubleLineU(int x, int y, sf::RenderTarget* target);
        void drawDoubleLineR(int x, int y, sf::RenderTarget* target);
        void drawLineU(int x, int y, sf::RenderTarget* target);

        void initKeybinds();
        void initTextures();
        void initPlayers();
        void initMap(std::string mapName);
        void initEvents(std::string mapName);
        void initBackground();

        void startEvent(std::string key);
        void checkEvent(sf::Vector2i position);
        void eventOnPosition();
        void eventTeleport(const sf::Vector2i teleportTo);
        void eventQuit();
        void eventLoadMap(std::string mapName);
        void logEvents();
        void logSteps(std::string eventName);
        int arrMap[11][19];
};

#endif // GAMESTATE_H
