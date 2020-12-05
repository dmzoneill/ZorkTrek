#include "ZorkTrek.h"


/**
* Circular dependency work around
* SdlGLMap.cpp extern ZorkTrek* OPENGL_ZORKTREK_INTERFACE;
*/

ZorkTrek* OPENGL_ZORKTREK_INTERFACE;

/**
* Constructor
*/

ZorkTrek::ZorkTrek() 
{	
    this->currentBattle = NULL;
    this->planetTarget = NULL;
    this->moonTarget = NULL;
    this->enemyTarget = NULL;
    this->targetChanged = false;
    this->gameCompleted = false;
    this->threadRunning = false;

    OPENGL_ZORKTREK_INTERFACE = this;
}


/**
* Destructor destroys the galaxy map
* destructs player, battle
* kills the opengl thread if running
*/

ZorkTrek::~ZorkTrek() 
{	
    // http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=/com.ibm.xlcpp8a.doc/language/ref/cplr380.htm
    // You can use a destructor explicitly to destroy objects, although this practice is not recommended.
    // However to destroy an object created with the placement new operator,

    // delete any stuff on the heap ( stack is cleared automatically for us )

    delete this->player;
    delete this->currentBattle;

    map<int, Cols>::const_iterator it;
    map<int, SolarSystem*>::const_iterator it2;

    // note recursive / iterative deconstruct,
    // solar systems will destruct, pve entities, planets, and planets will detruct moon
    // pointers to current targets (moon, planet enemy) will also be destructed as a result!

    for ( it = this->Galaxy.begin(); it != this->Galaxy.end(); ++it )
    {
        for ( it2 = it->second.begin(); it2 != it->second.end(); ++it2 )
        {
            --(*it2->second); // dirt implementation of operator overloading
            // delete it2->second;
        }
    }

    /* kill the open gl thread if its running */
    if(this->threadRunning==true)
    {
        int y = pthread_kill(this->openGlMapThread, 0);
    }
}


/**
* Entry point for the openGl thread
*
* @param void pointer (can be pointed at anything)
*
* @return void
*/

void *ZorkTrek::glThread(void *ptr)
{
    SdlGLMap *glMap = new SdlGLMap();
}



/**
* creates the game platform
* map for the game, by creating solar system and adding the to the <map> galaxy
*
* @return void
*/

void ZorkTrek::createGalaxy() 
{
    // to expand the game will can use this in conjunction with Star trek entities to create a bigger map
    int galaxyHeight = 4;
    int galaxyWidth = 4;

    // instantiate a new instace of the bitmaze creator to cross reference with our solar system pointers later
    BitMaze *maze = new BitMaze(galaxyWidth, galaxyHeight);

    galaxyHeight = (galaxyHeight * 2) + 1;
    galaxyWidth = (galaxyWidth * 2) + 1;

    // instantiate the Star trek entities class to build a list of solar systems, planets and moons
    this->stePointer = new StarTrekEntities();

    // numeber of solar system avaiable
    int numSystems = this->stePointer->getNumSolarSystems();
    // square root of the avialble systems
    int dimensions = this->stePointer->getGalaxyMatrixDimensions() -1;

    // poluate the galaxy 2 dimensional map
    for(int iterRows = 1; iterRows < galaxyWidth; iterRows++)
    {
        for(int iterCols = 1; iterCols < galaxyHeight; iterCols++)
        {
            if(this->stePointer->getNumSolarSystems()==0)
            {
                continue; // were out of solar systems
            }
            else
            {
                SolarSystem *newSys = new SolarSystem(this->stePointer->popSolarSystem(), this->stePointer, this->gameDifficulty);
                newSys->setExits(NULL, NULL, NULL, NULL);
                this->Galaxy.insert (make_pair (iterRows, Cols ()));
                this->Galaxy[iterRows].insert (make_pair (iterCols, newSys));
            }
        }
    }

    // set up the pointers, for the glaxy solar system exists
    // for example 0 represents rooms or solar system that you cannot enter
    // 1 are solar system that you can enter
    // 0 0 0 0 0 0
    // 0 1 0 1 1 0
    // 0 1 1 0 1 0
    // 0 0 1 1 1 0
    // 0 1 0 1 0 0
    // 0 1 1 1 0 0

    SolarSystem *ahead, *port, *back, *starboard;
    char mazeVal;

    // set up iterators to be use for slecting the pointers which reside around the pointer currently selected
    map<int, Cols>::iterator itAheadx; // X   (x , ( y - 1 ))
    map<int, Cols>::iterator itBackx; // X   (x , ( y + 1 ))
    map<int, Cols>::iterator itPortx; // X  ( ( x - 1 ), y)
    map<int, Cols>::iterator itStarboardx; // X   ( ( x + 1 ), y)

    map<int, SolarSystem*>::iterator itAheady; // Y  (x , (y - 1))
    map<int, SolarSystem*>::iterator itBacky; // Y  (x , (y + 1))
    map<int, SolarSystem*>::iterator itPorty; // Y  ( ( x - 1 ), y)
    map<int, SolarSystem*>::iterator itStarboardy; // Y  ( ( x + 1 ), y)

    map<int, Cols>::const_iterator it;
    map<int, SolarSystem*>::const_iterator it2;

    // iterate through each solar system in the map
    for ( it = this->Galaxy.begin(); it != this->Galaxy.end(); ++it )
    {
        for ( it2 = it->second.begin(); it2 != it->second.end(); ++it2 )
        {
            // get the bit from the bitmap whih corresponds to the current x,y position in the galaxy map
            mazeVal = maze->getQuandrantLocationVal(it->first, it2->first);

            // if the corresponding bit is not 0 then we will continue with setting up the exits for this solarsystem
            if(mazeVal!='0')
            {
                // get the exit up, exit down
                itAheadx = this->Galaxy.find ( it->first );
                itBackx = this->Galaxy.find ( it->first );

                // we cant go to the left if were at the beginning, otherwise try get the solarsytem to the left
                if(it != this->Galaxy.begin())
                    itPortx = this->Galaxy.find ( it->first - 1 );
                else
                    itPortx = this->Galaxy.end();

                // we cant go to the right if were at the end, otherwise try get the solarsytem to the right
                if(it != this->Galaxy.end())
                    itStarboardx = this->Galaxy.find ( it->first + 1 );
                else
                    itStarboardx = this->Galaxy.end();

                // we cant go to the above if were at the top, otherwise try get the solarsytem above
                if(it2 != it->second.begin())
                    itAheady = itAheadx->second.find ( it2->first - 1 );
                else
                    itAheady = itAheadx->second.end();

                // we cant go to the below if were at the bottom, otherwise try get the solarsytem below
                if(it2 != it->second.end())
                    itBacky = itBackx->second.find ( it2->first + 1 );
                else
                    itBacky = itBackx->second.end();

                // check to see if the left system is valid then try to get the mathcing y coordinate
                if(itPortx!=this->Galaxy.end())
                    itPorty = itPortx->second.find ( it2->first );
                else
                    itPorty = itPortx->second.end();

                // check to see if the right system is valid then try to get the mathcing y coordinate
                if(itStarboardx!=this->Galaxy.end())
                    itStarboardy = itStarboardx->second.find ( it2->first );
                else
                    itStarboardy = itStarboardx->second.end();


                ahead = itAheady->second;
                port = itPorty->second;
                back = itBacky->second;
                starboard = itStarboardy->second;

                // cross reference the exits with the bitmap and assign exits depeding on the bitmap (x, y - 1)
                if(itAheady!=itAheadx->second.end())
                {
                    if(maze->getQuandrantLocationVal(it->first, it2->first - 1)=='1')
                    {
                        ahead = itAheady->second;
                    }
                    else
                    {
                        ahead = NULL;
                    }
                }
                else
                {
                    ahead = NULL;
                }

                // cross reference the exits with the bitmap and assign exits depeding on the bitmap (x, y + 1)
                if(itBacky!=itBackx->second.end())
                {
                    if(maze->getQuandrantLocationVal(it->first, it2->first + 1)=='1')
                    {
                        back = itBacky->second;
                    }
                    else
                    {
                        back = NULL;
                    }
                }
                else
                {
                    back = NULL;
                }

                // cross reference the exits with the bitmap and assign exits depeding on the bitmap (x -1, y)
                if(itPorty!=itPortx->second.end())
                {
                    if(maze->getQuandrantLocationVal(it->first - 1, it2->first)=='1')
                    {
                        port = itPorty->second;
                    }
                    else
                    {
                        port = NULL;
                    }
                }
                else
                {
                    port = NULL;
                }

                // cross reference the exits with the bitmap and assign exits depeding on the bitmap (x +1, y)
                if(itStarboardy!=itStarboardx->second.end())
                {
                    if(maze->getQuandrantLocationVal(it->first + 1, it2->first)=='1')
                    {
                        starboard = itStarboardy->second;
                    }
                    else
                    {
                        starboard = NULL;
                    }
                }
                else
                {
                    starboard = NULL;
                }

                it2->second->setExits(ahead, port, back, starboard);
            }
            else
            {
                continue;
            }
        }
    }

    int randX;
    int randY;

    this->currentSolarSystem = NULL;

    // find a random accessible solar system for the entry point of the game
    while(this->currentSolarSystem==NULL)
    {
        seedMicroPrecision();
        randX = int((double(rand())/RAND_MAX)*dimensions); // random between 0 & dimensions
        randY = int((double(rand())/RAND_MAX)*dimensions); // random between 0 & dimensions
        map<int, Cols>::iterator it = this->Galaxy.find ( randX );
        if(it==this->Galaxy.end())
        {
            continue;
        }
        else
        {
            map<int, SolarSystem*>::iterator it2 = it->second.find ( randY );
            if(it2==it->second.end())
            {
                continue;
            }
            else
            {
                if(it2->second->nextSolarSystem("port")==NULL && it2->second->nextSolarSystem("starboard")==NULL && it2->second->nextSolarSystem("back")==NULL && it2->second->nextSolarSystem("ahead")==NULL)
                {
                    continue;
                }
                else
                {
                    // set the current solar system and setup xpos and ypos for use in the CIN input pefix
                    this->currentSolarSystem = it2->second;
                    this->xPos = randX;
                    this->yPos = randY;
                }
            }
        }
    }

    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                     Stellar Cartography                                \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << "                                     Scanning the known Galaxy                                       " << endl;
    cout << "                         Yours scanners have detected \033[31;1m" << numSystems << "\033[0m solar systems.            " << endl;
    cout <<  endl;

    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                         Navigation                                     \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << "                       Sir,  we've arrived in sector \033[31;1m" << randX << "-" << randY << "\033[0m the \033[31;1m" << this->currentSolarSystem->getName() << "\033[0m System" << endl;
    cout << endl;

    // start the sysstem scanner to show the player the enrty point solary system information
    this->currentSolarSystem->scanSystem();

    // create the prefix used for the command interface
    ostringstream buffer;
    buffer << "        [ \033[31;1m";
    buffer << this->xPos;
    buffer << "-";
    buffer << this->yPos;
    buffer << "\033[0m ";
    buffer << this->currentSolarSystem->getName();
    buffer << " ] ";

    this->prefix = buffer.str();

    // clear up the reources that will no longer be used by the game
    // maze creator
    delete maze;
    // star trek entity names
    delete this->stePointer;
}


/**
* sets up the players ship and game difficulty for the game
*
* @return void
*/

void ZorkTrek::playerSetup()
{
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                         Player Setup                                   \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;

    string buffer;
    bool validName = false;

    // take the input from the user for the ship name
    while(validName == false)
    {
        cout << "          Enter Ship name > ";
        getline(cin, buffer, '\n');

        if(buffer.length()!=0)
        {
            validName = true;
        }
    }

    cout << endl;
    cout << "                Enter a game difficulty of 1 (lowest) 5 (Highest)  " << endl;
    cout << "                This will affect the amount of resources and ingame enemies and their strenghts   " << endl;
    cout << endl;

    string buffer2;
    bool validDifficulty = false;

    unsigned int i;

    // take the input from the user for the game difficulty
    while(validDifficulty == false)
    {
        cout << "          Difficulty [ 1 - 5 ] > ";
        getline(cin, buffer2, '\n');

        if(buffer2.length()!=0)
        {
            istringstream dif(buffer2);

            dif >> i;
            if(i>0 && i <6)
            {
                validDifficulty = true;
            }
        }
    }

    this->gameDifficulty = i;
    this->player = new StarShip(buffer,this->gameDifficulty);
}


/**
* entry point for the game and start the pre game setup, followed by the main game LOOP
*
* @return void
*/

void ZorkTrek::play() 
{
    this->printWelcome();
    this->playerSetup();
    this->createGalaxy();

    bool finished = false;
    // wait until command returns true and then exit the main loop
    while (!finished)
    {
        Command* command = this->parser.getCommand(this->prefix);
        finished = this->processCommand(*command);
        delete command;
        // if your ship has been destroyed then game over!
        if(this->player->getIsWreck()==true)
            finished = true;
    }
    // print the end of game message
    this->exitGameMessage();
}


/**
* process the command and compares the command word to initiate the in game functions
* returns true if the user quits, otherwise false
*
* @param command
*
* @return bool
*/

bool ZorkTrek::processCommand(Command command) 
{
    if (command.isUnknown())
    {
        cout << endl << "               Sir? please repeat the order!" << endl;
        return false;
    }

    // check to see if the players ship has been destroyed
    if(this->player->getIsWreck())
    {
        return true;
    }

    string commandWord = command.getCommandWord();

    if (commandWord.compare("help") == 0)
    {
        this->printHelp();
    }
    else if (commandWord.compare("warp") == 0)
    {
        this->warpSolarSystem(command);
    }
    else if (commandWord.compare("map") == 0)
    {
        this->showMap();
    }
    else if (commandWord.compare("back") == 0)
    {
        this->goBack();
    }
    else if (commandWord.compare("scan") == 0)
    {
        this->scanner(command);
    }
    else if (commandWord.compare("target") == 0)
    {
        this->target(command);
    }
    else if (commandWord.compare("beam") == 0)
    {
        this->transporter(command);
    }
    else if (commandWord.compare("status") == 0)
    {
        this->status();
    }
    else if (commandWord.compare("phaser") == 0)
    {
        this->phaser();
    }
    else if (commandWord.compare("launch") == 0)
    {
        this->launch(command);
    }
    else if (commandWord.compare("transwarp") == 0)
    {
        if(this->transwarp()==true)
        {
            this->printFinished();
            cin.clear(); // just to ensure there's no junk in the stream which
            cout << "                             Press Enter / Return to continue...\n";
            cin.ignore(1,0);

            return true;
        }
        else
        {
            cout << endl << "             Sir, the transwarp drive is still offline, try 'repair' first" << endl;
        }
    }
    else if (commandWord.compare("use") == 0)
    {
        this->use(command);
    }
    else if (commandWord.compare("repair") == 0)
    {
        this->player->repair();
    }
    else if (commandWord.compare("startgui") == 0)
    {
        /**
        * thread (Output) Pthread handle to the created thread
        * attr (Input) The thread attributes object containing the attributes to be associated with the newly created thread. If NULL, the default thread attributes are used.
        * start_routine (Input) The function to be run as the new threads start routine
        * arg * (Input) An address for the argument for the threads start routine
        */

        this->threadRunning = true;
        pthread_create( &this->openGlMapThread, NULL, &ZorkTrek::glThread, NULL );
    }
    else if (commandWord.compare("quit") == 0)
    {
        return true;
    }

    return false;

}


/**
* interates through the solar system map and prints out a legend of accessible rooms, visited history etc
*
* @return void
*/

void ZorkTrek::showMap()
{

    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                     Stellar Cartography                                \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << "                                     Scanning the known Galaxy                                       " << endl;
    cout << endl;
    cout << "                      Legend :  \033[31;31;4mCurrent System\033[0m  \033[31;32;2mAccessible\033[0m  \033[31;32;9mVisited\033[0m  \033[31;37;0mBorg Swarm\033[0m " << endl;
    cout <<  endl;
    cout <<  endl;

    map<int, Cols>::const_iterator it;
    map<int, SolarSystem*>::const_iterator it2;

    // colors for the different inspections
    string red = "\033[31;31;4m";
    string green = "\033[31;32;2m";
    string greenVisit = "\033[31;32;9m";
    string black = "\033[31;37;0m";
    string colorUsed = "";
    string ColorEnd = "\033[0m";

    const short nameLen = 11;

    for ( it = this->Galaxy.begin(); it != this->Galaxy.end(); ++it )
    {
        cout << "      ";
        for ( it2 = it->second.begin(); it2 != it->second.end(); ++it2 )
        {
            if(it2->second->nextSolarSystem("port")==NULL && it2->second->nextSolarSystem("starboard")==NULL && it2->second->nextSolarSystem("back")==NULL && it2->second->nextSolarSystem("ahead")==NULL)
            {
                colorUsed = black;
            }
            else
            {
                colorUsed = green;
            }

            if(this->currentSolarSystem->getName().compare(it2->second->getName()) == 0)
            {
                colorUsed = red;
            }

            if(this->isVisited(it2->second))
            {
                colorUsed = greenVisit;
            }

            cout << colorUsed << it2->second->getName() << ColorEnd;

            for(int s = it2->second->getName().length(); s < nameLen; s++)
            {
                cout << " ";
            }
        }
        cout << endl << endl;
    }

    // update the players energy, using ship functions costs energy
    cout << endl;
    this->player->setPower(this->player->getPower() -2);
    cout << "               Stellar Cartography has used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
    cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
    cout << this->player->getPower() << endl;
    cout << endl;
}


/**
* called when the player enters into a solar system and initiates a random battle of PVE players exists
* random depending on game difficulty
*
* @return void
*/

void ZorkTrek::beginRandomBattle() 
{
    if(this->currentBattle!=NULL)
    {
        delete this->currentBattle;
        this->currentBattle = NULL;
    }

    PVEEntity *attackingEnemy = this->currentSolarSystem->randomAttack(this->gameDifficulty);

    if(attackingEnemy!=NULL)
    {
        this->currentBattle = new Battle(this->player, attackingEnemy);
    }
}


/**
* goes back to the previous solar system
* pops the pointer to the last system in the sequence from the history vector
*
* @return void
*/

void ZorkTrek::goBack() 
{
    if(this->history.size() > 0)
    {
        SolarSystem* p = this->history[this->history.size() - 1];
        this->currentSolarSystem = p;
        this->history.pop_back();
        // were now in a new system so scan it for the player
        this->currentSolarSystem->scanSystem();

        cout << endl;
        this->player->setPower(this->player->getPower() -3);
        cout << "               Warp engines have used up '\033[31;31;1m3\033[0m' points of your energy reserves" << endl;
        cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
        cout << this->player->getPower() << endl;
        cout << endl;
    }
    else
    {
        cout << endl << "               Sir,  we're back to where we started" << endl;
    }
}


/**
* holds and updates the list to the visited history vector
* to be used by the map printed out of visited solar systems
*
* @param p* the current system
*
* @return void
*/

void ZorkTrek::visit(SolarSystem *p) 
{	
    bool visited = false;
    unsigned int visits = this->visitedHistory.size();
    unsigned int u = 0;

    while(u < visits && visited == false)
    {
        if(this->visitedHistory[u]->getName().compare(p->getName()) == 0)
        {
            u = this->visitedHistory.size() + 1;
            visited = true;
        }
        u++;
    }

    if(visited==false)
    {
        this->visitedHistory.push_back(p);
    }
}


/**
* accesses the visited history and retusn weather a system has been visited
*
* @param p* system to check for
*
* @return bool
*/

bool ZorkTrek::isVisited(SolarSystem *p) 
{	
    for(unsigned int u = 0; u < this->visitedHistory.size(); u++)
    {
        if(this->visitedHistory[u]->getName().compare(p->getName()) == 0)
        {
            return true;
        }
    }
    return false;
}


/**
* completes the game if you have successfully repaired and refueled your engines to escape
*
* @param command
*
* @return void
*/

bool ZorkTrek::transwarp() 
{	
    if(this->player->isRepaired())
    {
        this->gameCompleted = true;
        return true;
    }
    else
    {
        return false;
    }
}


/**
* used to change the pointer to the current solar system
*
* @param command
*
* @return void
*/

void ZorkTrek::warpSolarSystem(Command command) 
{	
    if(this->currentBattle!=NULL)
    {
        if(this->currentBattle->enemyHasTractor())
        {
            cout << endl;
            cout << "               Sir,  the enemy ship '\033[31;1m" << this->currentBattle->getEnemyName() << "\033[0m' has '\033[31;1m" << this->player->getName() << "\033[0m' in a tractor lock" << endl;
            cout << "               We can't warp away " << endl;
            this->currentBattle->enemyMove();
            return;
        }
    }

    if (!command.hasSecondWord() && !command.hasThirdWord())
    {
        cout << "               Go where?"<< endl;
        return;
    }

    string direction = command.getSecondWord();

    // transpose the command to work with our map (90 degrees)
    if(direction.compare("ahead")==0)
        direction = "port";
    else if(direction.compare("back")==0)
        direction = "starboard";
    else if(direction.compare("port")==0)
        direction = "ahead";
    else
        direction = "back";

    // request the pointer to the next system
    SolarSystem* nextSolarSystem = this->currentSolarSystem->nextSolarSystem(direction);

    if (nextSolarSystem == NULL)
    {
        // that solar system cannot be entered so tell the user
        int rnda = int((double(rand())/RAND_MAX)*50) + 10; // generator number between 10 & 60
        cout << endl << "                         Your helmsman challenges your order," << endl << "                         it might have something to do with the " << rnda <<  " borg cubes!"<< endl;

        // if were in a battle then enemy is going to keep attacking
        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }
    }
    else
    {
        // update the x,y position from the map to be used in the prefix
        if(direction.compare("port")==0)
            this->xPos--;
        if(direction.compare("starboard")==0)
            this->xPos++;
        if(direction.compare("ahead")==0)
            this->yPos--;
        if(direction.compare("back")==0)
            this->yPos++;

        // update the visited history
        // and the sequence of history to be used in the back sequence
        this->visit(this->currentSolarSystem);
        this->history.push_back(this->currentSolarSystem);

        /* execute random enemy movement */
        this->enemyMovement();

        this->currentSolarSystem = nextSolarSystem;

        this->player->setPower(this->player->getPower() -3);
        cout << endl;
        cout << "               Warp engines have used up '\033[31;31;1m3\033[0m' points of your energy reserves" << endl;
        cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
        cout << this->player->getPower() << endl;
        cout << endl;

        // scan the system
        this->currentSolarSystem->scanSystem();

        ostringstream buffer;
        buffer << "        [ \033[31;1m";
        buffer << this->xPos;
        buffer << "-";
        buffer << this->yPos;
        buffer << "\033[0m ";
        buffer << this->currentSolarSystem->getName();
        buffer << " ] ";

        // update the prefix for the new system
        this->prefix = buffer.str();

        // reset targetting
        this->planetTarget = NULL;
        this->moonTarget = NULL;
        this->enemyTarget = NULL;

        // we've arrived in a new system, create a new battle based on game difficulty (random)
        this->beginRandomBattle();
    }
}


/**
* used to scan planets, moon and ships to retrieve information about the encapsulated information in these objects
*
* @param command
*
* @return void
*/

void ZorkTrek::scanner(Command command)
{
    if (!command.hasSecondWord() && !command.hasThirdWord())
    {
        // if there are no arguments after the command word scan the current system,
        // also initiate an enemy move if you are currently in a battle
        this->currentSolarSystem->scanSystem();

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }
    else if (command.hasSecondWord() && !command.hasThirdWord())
    {
        // scan planet
        istringstream iss(command.getSecondWord());
        unsigned int i;
        iss>>i;
        this->currentSolarSystem->scanPlanet(i);

        cout << endl;
        this->player->setPower(this->player->getPower() -1);
        cout << "               Short range sensors have used up '\033[31;31;1m1\033[0m' points of your energy reserves" << endl;
        cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
        cout << this->player->getPower() << endl;
        cout << endl;

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }
    else if (command.hasSecondWord() && command.hasThirdWord())
    {
        if (command.getSecondWord().compare("ship")==0)
        {
            // scan ship
            istringstream iss1(command.getThirdWord());
            unsigned int i;
            iss1>>i;
            this->currentSolarSystem->scanPVEEntity(i);

            cout << endl;
            this->player->setPower(this->player->getPower() -1);
            cout << "               Short range sensors have used up '\033[31;31;1m1\033[0m' points of your energy reserves" << endl;
            cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
            cout << this->player->getPower() << endl;
            cout << endl;

            if(this->currentBattle!=NULL)
            {
                this->currentBattle->enemyMove();
            }

            return;
        }
        else
        {
            // scan planet moon
            istringstream iss1(command.getSecondWord());
            unsigned int i;
            iss1>>i;
            istringstream iss2(command.getThirdWord());
            unsigned int j;
            iss2>>j;
            this->currentSolarSystem->scanPlanetMoon(i,j);

            cout << endl;
            this->player->setPower(this->player->getPower() -1);
            cout << "               Short range sensors have used up '\033[31;31;1m1\033[0m' points of your energy reserves" << endl;
            cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
            cout << this->player->getPower() << endl;
            cout << endl;

            if(this->currentBattle!=NULL)
            {
                this->currentBattle->enemyMove();
            }

            return;
        }
        return;
    }
}


/**
* launches torpedos
* note target must be locked first
*
* @param command
*
* @see target
*
* @return void
*/

void ZorkTrek::launch(Command command)
{
    cout << endl;

    // if the target has been changed close the old battle
    if(this->targetChanged == true)
    {
        this->targetChanged = false;
        this->currentBattle = NULL;
    }

    if(this->enemyTarget==NULL && this->planetTarget==NULL && this->moonTarget==NULL)
    {
        cout << "               \033[31;1mTactical Officer\033[0m : sir? i dont have a target! " << endl;

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }

    if(this->currentBattle==NULL && this->enemyTarget!=NULL)
    {
        this->currentBattle = new Battle(this->player, this->enemyTarget);

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }
    }

    if(this->enemyTarget==NULL && (this->planetTarget!=NULL || this->moonTarget!=NULL))
    {
        cout << "               \033[31;1mTactical Officer\033[0m : sir? the prime directive prohibits me\n                                   from firing at a habitated planet! " << endl;
        return;
    }

    if (!command.hasSecondWord() && !command.hasThirdWord())
    {
        cout << "               \033[31;1mTactical Officer\033[0m : sir? what would you like me to launch? " << endl;
        this->currentBattle->enemyMove();
        return;
    }

    else if (command.hasSecondWord() && !command.hasThirdWord())
    {
        if (command.getSecondWord().compare("photon")==0)
        {
            if(!this->enemyTarget->getIsWreckPVE())
            {
                this->currentBattle->Photon(false);

                cout << endl;
                this->player->setPower(this->player->getPower() -4);
                cout << "               Torpedo Launchers have used up '\033[31;31;1m4\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;

                this->currentBattle->enemyMove();
            }
            else
            {
                cout << "               \033[31;1mTactical Officer\033[0m : sir? i've belayed that order, target is destroyed " << endl;
                this->currentBattle = NULL;
            }
        }
        else if (command.getSecondWord().compare("quantum")==0)
        {
            if(!this->enemyTarget->getIsWreckPVE())
            {
                this->currentBattle->Quantum(false);

                cout << endl;
                this->player->setPower(this->player->getPower() -4);
                cout << "               Torpedo Launchers have used up '\033[31;31;1m4\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;

                this->currentBattle->enemyMove();
            }
            else
            {
                cout << "               \033[31;1mTactical Officer\033[0m : sir? i've belayed that order, target is destroyed " << endl;
                this->currentBattle = NULL;
            }
        }
        else
        {
            cout << "               \033[31;1mTactical Officer\033[0m : sir? what would you like me to launch? " << endl;
            this->currentBattle->enemyMove();
        }
    }
}


/**
* fires phasers at an enemy
* note target must be locked first
*
* @see target
*
* @return void
*/

void ZorkTrek::phaser()
{
    cout << endl;

    if(this->targetChanged == true)
    {
        this->targetChanged = false;
        this->currentBattle = NULL;
    }

    if(this->enemyTarget==NULL && this->planetTarget==NULL && this->moonTarget==NULL)
    {
        cout << "               \033[31;1mTactical Officer\033[0m : sir? i dont have a target! " << endl;

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }

    if(this->currentBattle==NULL && this->enemyTarget!=NULL)
    {
        this->currentBattle = new Battle(this->player, this->enemyTarget);

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }
    }

    if(!this->enemyTarget->getIsWreckPVE())
    {
        this->currentBattle->Phaser(false);

        cout << endl;
        this->player->setPower(this->player->getPower() -3);
        cout << "               Phasers have used up '\033[31;31;1m3\033[0m' points of your energy reserves" << endl;
        cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
        cout << this->player->getPower() << endl;
        cout << endl;

        this->currentBattle->enemyMove();
    }
    else
    {
        cout << "               \033[31;1mTactical Officer\033[0m : sir? i've belayed that order, target is destroyed " << endl;
        this->currentBattle = NULL;
    }
}


/**
* prints information about the players ships complements of resources weaponary and defensive
*
* @return void
*/

void ZorkTrek::status()
{
    cout << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                        Ship Report                                     \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << "                                      Ship Report For : '\033[34;1m" << this->player->getName() << "\033[0m'   " << endl;
    cout << endl;
    cout << "                 \033[34;1mDefence\033[0m :" << endl;
    cout << "               ----------------------------------------------------------------------" << endl;
    cout << "                             Shield Strenght             : \033[31;1m" << this->player->getShieldStrenght() << "\033[0m / " << MAX_SHIELDS <<  endl;
    cout << "                             Shield Regenerative Rate    : \033[31;1m" << this->player->getShieldRegenerativeRate() << "\033[0m" << endl;
    cout << "                             Armour                      : \033[31;1m" << this->player->getArmour() << "\033[0m / " << MAX_ARMOUR  << endl;
    cout << "                 \033[34;1mAttack\033[0m  :" << endl;
    cout << "               ----------------------------------------------------------------------" << endl;
    cout << "                             Phasers                     : \033[31;1moperational\033[0m " << endl;
    cout << "                             Photons                     : \033[31;1m" << this->player->getPhotons() << "\033[0m" << endl;
    cout << "                             Quantums                    : \033[31;1m" << this->player->getQuantums() << "\033[0m" << endl;
    cout << "                 \033[34;1mPower\033[0m   :" << endl;
    cout << "               ----------------------------------------------------------------------" << endl;
    cout << "                             Power                       : \033[31;1m" << this->player->getPower() << "\033[0m / " << MAX_POWER << " Teradyne"  << endl;
    cout << "                 \033[34;1mCargo\033[0m   : " << endl;
    cout << "               ----------------------------------------------------------------------" << endl;
    cout << "                             Food                        : \033[31;1m" << this->player->getFood() << "\033[0m ( " << (FOOD_WEIGHT * this->player->getFood()) << " Kellipate ) " << endl;
    cout << "                             Water                       : \033[31;1m" << this->player->getWater() << "\033[0m ( " << (WATER_WEIGHT * this->player->getWater()) << " Kellipate ) " << endl;
    cout << "                             Plasma                      : \033[31;1m" << this->player->getPlasma() << "\033[0m ( " << (PLASMA_WEIGHT * this->player->getPlasma()) << " Kellipate ) " << endl;
    cout << "                             Trianium                    : \033[31;1m" << this->player->getTrianium() << "\033[0m ( " << (TRIANIUM_WEIGHT * this->player->getTrianium()) << " Kellipate ) " << endl;
    cout << "                             Dilithium                   : \033[31;1m" << this->player->getDilithium() << "\033[0m ( " << (DILITHIUM_WEIGHT * this->player->getDilithium()) << " Kellipate ) " << endl;
    cout << "                           ----------------------------------------------------------" << endl;
    cout << "                             Total                       : \033[31;1m" << this->player->getCargoWeight() << "\033[0m / " << CARGOHOLD_MAX_WEIGHT << " Kellipate " << endl;

    if(this->currentBattle!=NULL)
    {
        this->currentBattle->enemyMove();
    }
}


/**
* transports or transfers quantities from target objects to the player object
*
* @param command
*
* @return void
*/

void ZorkTrek::transporter(Command command)
{
    cout << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                  Transporter Room Report                               \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;

    if(this->enemyTarget==NULL && this->planetTarget==NULL && this->moonTarget==NULL)
    {
        cout << "               \033[31;1mTransporter Officer\033[0m : sir? i dont have a target! " << endl;

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }

    if (!command.hasSecondWord() && !command.hasThirdWord())
    {
        cout << "               \033[31;1mTransporter Officer\033[0m : sir? what would you like me to transport? " << endl;

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }

    else if (command.hasSecondWord() && command.hasThirdWord() && this->enemyTarget!=NULL)
    {
        if(this->enemyTarget->getShieldStrenght() <= 0)
        {
            if (command.getSecondWord().compare("torpedos")==0)
            {
                // beam up enemy torpedos and retrofit to our launchers
                if(this->currentBattle!=NULL)
                {
                    this->currentBattle->enemyMove();
                }
            }
        }
        else
        {
            cout << "          \033[31;1mTransporter Officer\033[0m : sir? the enemies shields are still up, i cannot transport ! " << endl;

            if(this->currentBattle!=NULL)
            {
                this->currentBattle->enemyMove();
            }
        }
    }
    else if (command.hasSecondWord() && command.hasThirdWord() && this->planetTarget!=NULL)
    {
        istringstream iss(command.getThirdWord());
        int quantity;
        iss >> quantity;
        // beem stuff up from the planet
        if(command.getSecondWord().compare("water") == 0)
        {
            if(this->planetTarget->getWater() > 0)
            {
                if(quantity > this->planetTarget->getWater())
                    quantity = this->planetTarget->getWater();

                this->player->setWater(this->player->getWater() + quantity);
                this->planetTarget->setWater(this->planetTarget->getWater() - quantity);

                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;

            }
            else
            {
                cout << "             Sir, the planet doesn't have any water!";
            }
        }
        else if(command.getSecondWord().compare("trianium") == 0)
        {
            if(this->planetTarget->getTrianium() > 0)
            {
                if(quantity > this->planetTarget->getTrianium())
                    quantity = this->planetTarget->getTrianium();

                this->player->setTrianium(this->player->getTrianium() + quantity);
                this->planetTarget->setTrianium(this->planetTarget->getTrianium() - quantity);

                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;

            }
            else
            {
                cout << "             Sir, the planet doesn't have any trianium!";
            }
        }
        else if(command.getSecondWord().compare("dilithium") == 0)
        {
            if(this->planetTarget->getDilithium() > 0)
            {
                if(quantity > this->planetTarget->getDilithium())
                    quantity = this->planetTarget->getDilithium();

                this->player->setDilithium(this->player->getDilithium() + quantity);
                this->planetTarget->setDilithium(this->planetTarget->getDilithium() - quantity);
                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;
            }
            else
            {
                cout << "             Sir, the planet doesn't have any dilithium!";
            }
        }
        else if(command.getSecondWord().compare("food") == 0)
        {
            if(this->planetTarget->getFood() > 0)
            {
                if(quantity > this->planetTarget->getFood())
                    quantity = this->planetTarget->getFood();

                this->player->setFood(this->player->getFood() + quantity);
                this->planetTarget->setFood(this->planetTarget->getFood() - quantity);
                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;
            }
            else
            {
                cout << "             Sir, the planet doesn't have any food!";
            }
        }
        else if(command.getSecondWord().compare("plasma") == 0)
        {
            if(this->planetTarget->getPlasma() > 0)
            {
                if(quantity > this->planetTarget->getPlasma())
                    quantity = this->planetTarget->getPlasma();

                this->player->setPlasma(this->player->getPlasma() + quantity, true);
                this->planetTarget->setPlasma(this->planetTarget->getPlasma() - quantity);
                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;
            }
            else
            {
                cout << "             Sir, the planet doesn't have any plasma!";
            }
        }
        else
        {
            cout << "               \033[31;1mTransporter Officer\033[0m : sir? what would you like to transport from the planet ? " << endl;
        }

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }
    }
    else if (command.hasSecondWord() && command.hasThirdWord() && this->moonTarget!=NULL)
    {
        istringstream iss(command.getThirdWord());
        int quantity;
        iss >> quantity;
        // beem stuff up from the planet
        if(command.getSecondWord().compare("water") == 0)
        {
            if(this->moonTarget->getWater() > 0)
            {
                if(quantity > this->moonTarget->getWater())
                    quantity = this->moonTarget->getWater();

                this->player->setWater(this->player->getWater() + quantity);
                this->moonTarget->setWater(this->moonTarget->getWater() - quantity);
                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;
            }
            else
            {
                cout << "             Sir, the moon doesn't have any water!";
            }
        }
        else if(command.getSecondWord().compare("trianium") == 0)
        {
            if(this->moonTarget->getTrianium() > 0)
            {
                if(quantity > this->moonTarget->getTrianium())
                    quantity = this->moonTarget->getTrianium();

                this->player->setTrianium(this->player->getTrianium() + quantity);
                this->moonTarget->setTrianium(this->moonTarget->getTrianium() - quantity);
                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;
            }
            else
            {
                cout << "             Sir, the moon doesn't have any trianium!";
            }
        }
        else if(command.getSecondWord().compare("dilithium") == 0)
        {
            if(this->moonTarget->getDilithium() > 0)
            {
                if(quantity > this->moonTarget->getDilithium())
                    quantity = this->moonTarget->getDilithium();

                this->player->setDilithium(this->player->getDilithium() + quantity);
                this->moonTarget->setDilithium(this->moonTarget->getDilithium() - quantity);
                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;
            }
            else
            {
                cout << "             Sir, the moon doesn't have any dilithium!";
            }
        }
        else if(command.getSecondWord().compare("food") == 0)
        {
            if(this->moonTarget->getFood() > 0)
            {
                if(quantity > this->moonTarget->getFood())
                    quantity = this->moonTarget->getFood();

                this->player->setFood(this->player->getFood() + quantity);
                this->moonTarget->setFood(this->moonTarget->getFood() - quantity);
                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;
            }
            else
            {
                cout << "             Sir, the moon doesn't have any food!";
            }
        }
        else if(command.getSecondWord().compare("plasma") == 0)
        {
            if(this->moonTarget->getPlasma() > 0)
            {
                if(quantity > this->moonTarget->getPlasma())
                    quantity = this->moonTarget->getPlasma();

                this->player->setPlasma(this->player->getPlasma() + quantity, true);
                this->moonTarget->setPlasma(this->moonTarget->getPlasma() - quantity);
                cout << endl;
                this->player->setPower(this->player->getPower() -2);
                cout << "               Transporters have used up '\033[31;31;1m2\033[0m' points of your energy reserves" << endl;
                cout << "               '\033[31;31;1m" << this->player->getName() << "'s\033[0m' energy is down to ";
                cout << this->player->getPower() << endl;
                cout << endl;
            }
            else
            {
                cout << "             Sir, the moon doesn't have any plasma!";
            }
        }
        else
        {
            cout << "               \033[31;1mTransporter Officer\033[0m : sir? what would you like to transport from the moon ? " << endl;
        }

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }
    }
    else
    {
        cout << "               \033[31;1mTransporter Officer\033[0m : sir? how much would you like to beam up ? " << endl;
    }
}


/**
* targets moons, planets and entities and sets pointers to these targets
*
* @param command
*
* @return void
*/

void ZorkTrek::target(Command command)
{
    cout << endl;

    if (!command.hasSecondWord() && !command.hasThirdWord())
    {
        if(this->planetTarget!=NULL)
            cout << "               Currently targetting planet '\033[34;1m" << this->planetTarget->getName() << "\033[0m'" << endl;

        if(this->moonTarget!=NULL)
            cout << "               Currently targetting planet '\033[34;1m" << this->moonTarget->getName() << "\033[0m'" << endl;

        if(this->enemyTarget!=NULL)
            cout << "               Currently targetting planet '\033[34;1m" << this->enemyTarget->getName() << "\033[0m'" << endl;

        cout << endl;

        cout << "               \033[31;1mTactical Officer\033[0m : sir? what would you like me to target? " << endl;

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }
    else if (command.hasSecondWord() && !command.hasThirdWord())
    {
        // reset targetting
        this->planetTarget = NULL;
        this->moonTarget = NULL;
        this->enemyTarget = NULL;

        istringstream iss(command.getSecondWord());
        unsigned int i;
        iss>>i;

        // target planet
        this->planetTarget = this->currentSolarSystem->targetPlanet(i);

        if(this->planetTarget!=NULL)
            cout << "               \033[31;1mTactical Officer\033[0m : Targetting planet '\033[34;1m" << this->planetTarget->getName() << "\033[0m'" << endl;
        else
            cout << "               \033[31;1mTactical Officer\033[0m : sir? what planet would you like me to target? " << endl;

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }
    else if (command.hasSecondWord() && command.hasThirdWord())
    {
        if (command.getSecondWord().compare("ship")==0)
        {
            // reset targetting
            this->planetTarget = NULL;
            this->moonTarget = NULL;
            this->enemyTarget = NULL;
            this->targetChanged = true;

            istringstream iss(command.getThirdWord());
            unsigned int i;
            iss>>i;

            // target ship
            this->enemyTarget = this->currentSolarSystem->targetPVEEntity(i);

            if(this->enemyTarget!=NULL)
            {
                cout << "               \033[31;1mTactical Officer\033[0m : Targetting ship '\033[34;1m" << this->enemyTarget->getName() << "\033[0m'" << endl;
            }
            else
            {
                cout << "               \033[31;1mTactical Officer\033[0m : sir? what ship would you like me to target? " << endl;
            }

            return;
        }
        else
        {
            // reset targetting
            this->planetTarget = NULL;
            this->moonTarget = NULL;
            this->enemyTarget = NULL;

            istringstream iss1(command.getSecondWord());
            unsigned int i;
            iss1>>i;
            istringstream iss2(command.getThirdWord());
            unsigned int j;
            iss2>>j;

            // target ship
            this->moonTarget = this->currentSolarSystem->targetPlanetMoon(i,j);

            if(this->moonTarget!=NULL)
                cout << "               \033[31;1mTactical Officer\033[0m : Targeting moon '\033[34;1m" << this->moonTarget->getName() << "\033[0m'" << endl;
            else
                cout << "               \033[31;1mTactical Officer\033[0m : sir? what moon would you like me to target? " << endl;

            return;
        }

        if(this->currentBattle!=NULL)
        {
            this->currentBattle->enemyMove();
        }

        return;
    }
}


/**
* use items in your cargohold
*
* @param command
*
* @return void
*/

void ZorkTrek::use(Command command)
{
    cout << endl;

    if (!command.hasSecondWord() && !command.hasThirdWord())
    {
        cout << "               \033[31;1mRequisitions Officer\033[0m : sir? What would you like to use? " << endl;

        return;
    }
    else if (command.hasSecondWord() && !command.hasThirdWord())
    {
        cout << "               \033[31;1mRequisitions Officer\033[0m : sir? how much '\033[34;1m" << command.getSecondWord() <<  "\033[0m' would you like to use? " << endl;

        return;
    }
    else if (command.hasSecondWord() && command.hasThirdWord())
    {
        istringstream iss1(command.getThirdWord());
        unsigned int amount;
        iss1 >> amount;

        if(command.getSecondWord().compare("plasma")==0)
        {
            int plasma = this->player->getPlasma();
            int charge = 0;
            int left = 0;

            if(plasma >= amount)
            {
                charge = amount * 0.2;
                left = plasma - amount;
                this->player->setPower(this->player->getPower() + charge);
                this->player->setPlasma(left, false);
            }
            else
            {
                amount = plasma;
                charge = amount * 0.2;
                left = 0;
                this->player->setPower(this->player->getPower() + charge);
                this->player->setPlasma(left, false);
            }

            cout << "               \033[31;1mEngineering Officer\033[0m : we have gained " << charge << " power" << endl;
        }
        else
        {
            cout << "               \033[31;1mRequisitions Officer\033[0m : sir? What would you like to use? " << endl;
        }

        return;
    }
}


/**
 * Move enemies around map
 *
 * @return void
 */

void ZorkTrek::enemyMovement()
{
    map<int, Cols>::const_iterator it;
    map<int, SolarSystem*>::const_iterator it2;

    for ( it = this->Galaxy.begin(); it != this->Galaxy.end(); ++it )
    {
        cout << "      ";
        for ( it2 = it->second.begin(); it2 != it->second.end(); ++it2 )
        {
            if(it2->second->nextSolarSystem("port")==NULL && it2->second->nextSolarSystem("starboard")==NULL && it2->second->nextSolarSystem("back")==NULL && it2->second->nextSolarSystem("ahead")==NULL)
            {
                // blank system
            }
            else
            {
                // not blank
                it2->second->moveEnemies();
            }
        }
    }
}


/**
* prints out the information about commands and their usage
*
* @return void
*/

void ZorkTrek::printHelp() 
{	
    this->parser.showCommands();
}


/**
* Ran when the user enters the game
* Welcome message
*
* @return void
*/

void ZorkTrek::printWelcome() 
{
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                  Welcome to ZorkTrek!                                  \033[0m |     " << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << "           A sub space anomaly emitting high quatum stresses rips your transwarp nacelle             " << endl;
    cout << "                  from your ship.  Your galaxy class cruiser is sent hurdling                        " << endl;
    cout << "                         into a near by galaxy occupied by the \033[31;1mBORG\033[0m!                " << endl;
    cout << endl;
    cout << "                You need to find enough trianium and to rebuild your transwarp nacelle               " << endl;
    cout << "                   Luckily the galaxy has many solar systems rich in resources                       " << endl;
    cout << endl;
    cout << "                               \033[31;1m Your helmsman is awaiting your commands \033[0m            " << endl;
    cout << endl;
    cout << "                                     Type '\033[31;1mhelp\033[0m' if you need help.                  " << endl;
    cout << endl;
}


/**
* Ran when the user completed the game
*
* @return void
*/

void ZorkTrek::printFinished()
{
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                          You have completed ZorkTrek!                                  \033[0m |     " << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << endl;
}



/**
* Ran when the user quits()
*
* @return void
*/

void ZorkTrek::exitGameMessage()
{
    if(this->gameCompleted==true)
    {
        cout << "    +------------------------------------------------------------------------------------------+     " << endl;
        cout << "    | \033[40;31;1m                                       Game Completed                                   \033[0m |" << endl;
        cout << "    +------------------------------------------------------------------------------------------+     " << endl;
        cout << endl;
        cout << "                       \033[31;1m You activate your transwarp drive and escape to safety\033[0m                      " << endl;
        cout << endl;
    }
    else
    {
        cout << "    +------------------------------------------------------------------------------------------+     " << endl;
        cout << "    | \033[40;31;1m                                         Game Over                                      \033[0m |" << endl;
        cout << "    +------------------------------------------------------------------------------------------+     " << endl;
        cout << endl;
        cout << "                                    \033[31;1m You have been assimulated\033[0m                      " << endl;
        cout << endl;
    }
}


/**
* Public accessor to the scanner private method
* for use in the OpenGL interface
*
* @see scanner
*
* @return void
*/

void ZorkTrek::openGLScanShip(unsigned int x) 
{		
    stringstream out;
    out << x;
    Command* openGLCommand = new Command("scan","ship", out.str());
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the scanner private method
* for use in the OpenGL interface
*
* @see scanner
*
* @return void
*/

void ZorkTrek::openGLScanPlanet(unsigned int x) 
{		
    stringstream out;
    out << x;
    Command* openGLCommand = new Command("scan",out.str(),"");
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the scanner private method
* for use in the OpenGL interface
*
* @see scanner
*
* @return void
*/

void ZorkTrek::openGLScanMoon(unsigned int x) 
{		
    stringstream pout, mout;

    bool found = false;
    unsigned int mnum = 0;
    unsigned int pnum = 0;

    for(unsigned int i = 0; i < this->currentSolarSystem->getSystemPlanets().size(); i++)
    {
        for(unsigned int k = 0; k < this->currentSolarSystem->getSystemPlanets()[i]->getMoons().size(); k++)
        {
            if(x == mnum)
            {
                found = true;
                pout << pnum;
                mout << k;
                break;
            }
            mnum++;
        }
        if(found == true)
            break;

        pnum++;
    }

    Command* openGLCommand = new Command("scan",pout.str(),mout.str());
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the phaser private method
* for use in the OpenGL interface
*
* @see phaser
*
* @return void
*/

void ZorkTrek::openGLPhaser()
{
    Command* openGLCommand = new Command("phaser","", "");
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the launch private method
* for use in the OpenGL interface
*
* @see launch
*
* @return void
*/

void ZorkTrek::openGLPhoton()
{
    Command* openGLCommand = new Command("launch","photon", "");
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the launch private method
* for use in the OpenGL interface
*
* @see launch
*
* @return void
*/

void ZorkTrek::openGLQuantum()
{
    Command* openGLCommand = new Command("launch","quantum", "");
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the targetShip private method
* for use in the OpenGL interface
*
* @param x
* @see targetShip
*
* @return void
*/

void ZorkTrek::openGLTargetShip(unsigned int x) 
{		
    stringstream out;
    out << x;
    Command* openGLCommand = new Command("target","ship", out.str());
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the targetPlanet private method
* for use in the OpenGL interface
*
* @param x
* @see targetPlanet
*
* @return void
*/

void ZorkTrek::openGLTargetPlanet(unsigned int x) 
{		
    stringstream out;
    out << x;
    Command* openGLCommand = new Command("target",out.str(),"");
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the targetMoon private method
* for use in the OpenGL interface
*
* @param x
* @see targetMoon
*
* @return void
*/

void ZorkTrek::openGLTargetMoon(unsigned int x) 
{		
    stringstream pout, mout;

    bool found = false;
    unsigned int mnum = 0;
    unsigned int pnum = 0;

    for(unsigned int i = 0; i < this->currentSolarSystem->getSystemPlanets().size(); i++)
    {
        for(unsigned int k = 0; k < this->currentSolarSystem->getSystemPlanets()[i]->getMoons().size(); k++)
        {
            if(x == mnum)
            {
                found = true;
                pout << pnum;
                mout << k;
                break;
            }
            mnum++;
        }
        if(found == true)
            break;

        pnum++;
    }

    Command* openGLCommand = new Command("target",pout.str(),mout.str());
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}


/**
* Public accessor to the warpSolarSystem private method
* for use in the OpenGL interface
*
* @param direction
* @see warpSolarSystem
*
* @return void
*/

void ZorkTrek::openGLwarpSolarSystem(string direction) 
{		
    Command* openGLCommand = new Command("warp",direction, "");
    bool finished = this->processCommand(*openGLCommand);
    delete openGLCommand;
}
