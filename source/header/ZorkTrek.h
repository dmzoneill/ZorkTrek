#ifndef ZORKTREK_H_
#define ZORKTREK_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // signals for thread
#include <pthread.h> // posix threading
#include <iostream>
#include <string>
#include <map>
#include <sstream> // string stream 


#include "ZorkTrekLib.h"
#include "PVEEntity.h"
#include "Starship.h"
#include "Battle.h"
#include "SolarSystem.h"
#include "StarTrekEntities.h"
#include "Command.h"
#include "CommandWords.h"
#include "Parser.h"
#include "Maze.h"
#include "SdlGLMap.h"

// 2 dimensional map 
typedef map<int, SolarSystem*> Cols;
typedef map<int, Cols> Rows;

using std::string;
using std::cout;
using std::endl;
using std::ostringstream;
using std::istringstream;
using std::map;
using std::make_pair;

class ZorkTrek 
{
    private:
        Parser parser;
        SolarSystem *currentSolarSystem;

        void createGalaxy();
        bool processCommand(Command command); // Pass by value
        void beginRandomBattle();
        void playerSetup();

        void printWelcome();
        void printFinished();
        void printHelp();
        void exitGameMessage();

        void target(Command command);
        void warpSolarSystem(Command command);
        void scanner(Command command);
        void launch(Command command);
        void use(Command command);
        void transporter(Command command);
        bool transwarp();
        void phaser();
        void showMap();
        void status();
        void goBack();
        void enemyMovement();

        void visit(SolarSystem *p);
        bool isVisited(SolarSystem *p);
        bool gameCompleted;

        // current position in the solar system map
        int xPos;
        int yPos;

        // used as the prefix string for cin > operation
        string prefix;

        // accessor / definer for the type definition of our solar system map
        Rows Galaxy;

        // used in conjunction with enemy behaviour and resiliancy
        unsigned int gameDifficulty;

        Battle *currentBattle;
        StarShip *player;
        StarTrekEntities *stePointer;

        // targets (for locking on)
        CelestialBody *planetTarget;
        CelestialBody *moonTarget;
        PVEEntity *enemyTarget;

        // history of solar systems visited
        vector <SolarSystem*> visitedHistory;
        // used for going back
        vector <SolarSystem*> history;

        bool targetChanged;

        /* gl thread */
        pthread_t openGlMapThread;
        bool threadRunning;
        static void *glThread(void *ptr); // function signature for our gl thread function


    public:

        ZorkTrek();
        ~ZorkTrek();
        void play();

        /* public interface for opengl overlay */

        void openGLwarpSolarSystem(string direction);
        void openGLTargetShip(unsigned int x);
        void openGLTargetPlanet(unsigned int x);
        void openGLTargetMoon(unsigned int x);
        void openGLScanShip(unsigned int x);
        void openGLScanPlanet(unsigned int x);
        void openGLScanMoon(unsigned int x);
        void openGLPhaser();
        void openGLPhoton();
        void openGLQuantum();

        Battle* getBattle() { return this->currentBattle; };
        CelestialBody* getMoonTarget() { return this->moonTarget; };
        CelestialBody* getPlanetTarget() { return this->planetTarget; };
        PVEEntity* getEnemyTarget() { return this->enemyTarget; };
        StarShip* getPlayer() { return this->player; };
        Rows getGalaxy() { return this->Galaxy; };
        SolarSystem *getSystem() { return this->currentSolarSystem; };
};

#endif /*ZORKTREK_H_*/
