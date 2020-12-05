#include "SdlGLMap.h"

#define COLORKEY 0, 0, 0 // Transparent colour

/**
* Circular dependency work around
*/
extern ZorkTrek* OPENGL_ZORKTREK_INTERFACE;


/**
* Constructor
*
* Loads Surface Bitmaps, Mix_chunk Sounds
*
*/

SdlGLMap::SdlGLMap()
{	  	
    /* start video audio font support */
    Uint32 flags = SDL_DOUBLEBUF | SDL_SWSURFACE;
    this->initVideo(flags);
    /* end start, note this will stop well before here if there is a problem */


    /* all is good */
    this->shipX = 80;
    this->shipY = 570;  
    this->solarScope = false;
    this->galaxyScope = true;
    this->font = loadfont("/usr/share/fonts/truetype/msttcorefonts/arial.ttf", 12);
    this->font2 = loadfont("/usr/share/fonts/truetype/msttcorefonts/arial.ttf", 24);
    this->font3 = loadfont("/usr/share/fonts/truetype/msttcorefonts/arial.ttf", 11);
    this->Galaxy = OPENGL_ZORKTREK_INTERFACE->getGalaxy();
    this->currentSystem = OPENGL_ZORKTREK_INTERFACE->getSystem();

    this->bg1 = this->loadImage("data/solarsystem.bmp",false);
    this->introbg = this->loadImage("data/nsignia.bmp",false);
    this->planet1 = this->loadImage("data/planet1.bmp",true);
    this->planet2 = this->loadImage("data/planet2.bmp",true);
    this->planet3 = this->loadImage("data/planet3.bmp",true);
    this->planet4 = this->loadImage("data/planet4.bmp",true);
    this->planet5 = this->loadImage("data/planet5.bmp",true);
    this->moon = this->loadImage("data/moon.bmp",true);

    this->cube = this->loadImage("data/cube.bmp",true);
    this->tacticalcube = this->loadImage("data/tacticalcube.bmp",true);
    this->sphere = this->loadImage("data/sphere.bmp",true);
    this->probe = this->loadImage("data/probe.bmp",true);
    this->ship = this->loadImage("data/defiant.bmp",true);
    this->battleResponce = this->loadImage("data/battle.bmp",true);

    this->lasers = this->loadImage("data/lasers.bmp",false);
    this->photons = this->loadImage("data/photon.bmp",false);
    this->quantums = this->loadImage("data/quantum.bmp",false);
    this->targetIndicator = this->loadImage("data/target.bmp",true);
    this->up = this->loadImage("data/up.bmp",true);
    this->down = this->loadImage("data/down.bmp",true);
    this->left = this->loadImage("data/left.bmp",true);
    this->right = this->loadImage("data/right.bmp",true);

    this->power = this->loadImage("data/power.bmp",true);
    this->cargo = this->loadImage("data/cargo.bmp",true);
    this->shields = this->loadImage("data/shields.bmp",true);
    this->armour = this->loadImage("data/armour.bmp",true);

    this->bFood = this->loadImage("data/food.bmp",true);
    this->bWater = this->loadImage("data/water.bmp",true);
    this->bPlasma = this->loadImage("data/plasma.bmp",true);
    this->bTrianium = this->loadImage("data/trianium.bmp",true);
    this->bDilithium = this->loadImage("data/dilithium.bmp",true);

    this->beam = this->loadImage("data/transporter.bmp",true);
    this->scanner = this->loadImage("data/scan.bmp",true);

    this->wreck = this->loadImage("data/wreck.bmp",true);
    this->borgwreck = this->loadImage("data/borgwreck.bmp",true);

    this->gameover = this->loadImage("data/gameover.bmp",false);

    this->lastTargetMoon = false;
    this->playedInto = false;

    this->themetune = Mix_LoadWAV("data/tng.wav");
    this->warp = Mix_LoadWAV("data/warp.wav");
    this->torpedo1 = Mix_LoadWAV("data/torpedo1.wav");
    this->torpedo2 = Mix_LoadWAV("data/torpedo2.wav");
    this->phasers = Mix_LoadWAV("data/phasers.wav");
    this->explosion = Mix_LoadWAV("data/explosion.wav");
    this->borg = Mix_LoadWAV("data/borg.wav");

    this->battleStarted = false;
    this->hasCelestialTarget = false;

    this->drawIntro();
    this->run();
}


/**
* Destructor
*
* Releases Surfaces, Mix_Chunks
* Releases Audio & Video subsystem
*
*/

SdlGLMap::~SdlGLMap()
{		
    TTF_CloseFont(this->font);
    TTF_CloseFont(this->font2);
    TTF_CloseFont(this->font3);

    SDL_FreeSurface(this->screen); // note using delete after this will cuase a c++ double free courption (sdl_free deletes the piinter??)
    SDL_FreeSurface(this->bg);
    SDL_FreeSurface(this->bg1);
    SDL_FreeSurface(this->introbg);
    SDL_FreeSurface(this->temp);
    SDL_FreeSurface(this->gameover);

    // planets
    SDL_FreeSurface(this->planet1);
    SDL_FreeSurface(this->planet2);
    SDL_FreeSurface(this->planet3);
    SDL_FreeSurface(this->planet4);
    SDL_FreeSurface(this->planet5);
    SDL_FreeSurface(this->moon);

    // borgvessels
    SDL_FreeSurface(this->cube);
    SDL_FreeSurface(this->tacticalcube);
    SDL_FreeSurface(this->sphere);
    SDL_FreeSurface(this->probe);

    // player ship
    SDL_FreeSurface(this->ship);
    SDL_FreeSurface(this->battleResponce);

    // weapons
    SDL_FreeSurface(this->photons);
    SDL_FreeSurface(this->quantums);
    SDL_FreeSurface(this->lasers);

    // beam and scanner
    SDL_FreeSurface(this->scanner);
    SDL_FreeSurface(this->beam);
    SDL_FreeSurface(this->bFood);
    SDL_FreeSurface(this->bWater);
    SDL_FreeSurface(this->bPlasma);
    SDL_FreeSurface(this->bTrianium);
    SDL_FreeSurface(this->bDilithium);

    // exits
    SDL_FreeSurface(this->power);
    SDL_FreeSurface(this->cargo);
    SDL_FreeSurface(this->shields);
    SDL_FreeSurface(this->armour);

    // exits
    SDL_FreeSurface(this->up);
    SDL_FreeSurface(this->down);
    SDL_FreeSurface(this->left);
    SDL_FreeSurface(this->right);

    // wrecks
    SDL_FreeSurface(this->borgwreck);
    SDL_FreeSurface(this->wreck);
    SDL_FreeSurface(this->targetIndicator);

    //sounds
    Mix_FreeChunk(this->themetune);
    Mix_FreeChunk(this->torpedo1);
    Mix_FreeChunk(this->torpedo2);
    Mix_FreeChunk(this->warp);
    Mix_FreeChunk(this->borg);
    Mix_FreeChunk(this->phasers);

    /* quit Audio SubSystem and video Subsystem	*/
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_Quit();
}


/**
* I have set the flag SDL_SWSURFACE for a window :)
*
* Double buffer or
* SDL_SWSURFACE to ensure compatibility with you graphics hardware
*
* Check for TTF font support
* Initialise video
* Initialise Audio
* Specifically a mixer
* Set window Caption
*
* Draw Starting surface
* and enable SDL repeat keys
*
* @param UNIT32 valid surface (memory)
*
* @return void
*/

void SdlGLMap::initVideo(Uint32 flags = SDL_DOUBLEBUF | SDL_SWSURFACE) 
{
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s \n", TTF_GetError());
        fflush(stderr);
        exit(1);
    }

    // Load SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        fflush(stderr);
        exit(1);
    }

    /* set the title bar */
    SDL_WM_SetCaption("ZorkTrek SDL OpenGL", "ZorkTrek SDL OpenGL");
    // fullscreen can be toggled at run time :) any you might want to change the flags with params?
    //set the main screen to SCREEN_WIDTHxSCREEN_HEIGHT with a colour depth of 16:
    this->screen = SDL_SetVideoMode(1024, 700, 16, flags);
    if (this->screen == NULL)
    {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        fflush(stderr);
        exit(1);
    }

    /* Initialization */
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1){
        fprintf(stderr, "Unable to set audio mode: %s\n", SDL_GetError());
        fflush(stderr);
        exit(1);
    }


    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 65536) == -1)
    {
        fprintf(stderr, "mixer could not be started: %s\n", SDL_GetError());
        fflush(stderr);
        exit(1);
    }

    this->bg = this->loadImage("data/galaxy.bmp",false);
    this->drawImage(this->bg, 0,0, this->bg->w, this->bg->h, this->screen, 0, 0, 255);
    // repeat keys
    SDL_EnableKeyRepeat(500,100);   	

    return;
}


/**
* Draw battle
* If a battle begins
* play We are borg sound clip
* Show battle taunt image (picard)
*
* @return void
*/

void SdlGLMap::drawBattleRant()
{
    SDL_Rect dest;
    if(OPENGL_ZORKTREK_INTERFACE->getBattle()!=NULL)
    {
        dest.x = 710;
        dest.y = 470;
        this->drawImage(this->battleResponce, 0,0, this->battleResponce->w, this->battleResponce->h, this->screen, dest.x, dest.y, 255);
        if(this->battleStarted == false)
        {
            this->battleStarted = true;
            Mix_PlayChannel(-1, this->borg, 0); // play theme tune (-1 let subsystem select channel,
        }
    }   
    else
    {
        this->battleStarted = false;
    }	
}


/**
* Game over (quit sdl interface)
* Draw Gates assimilated
*
* @return void
*/

void SdlGLMap::drawGameOver()
{
    this->drawImage(this->gameover, 0,0, this->gameover->w, this->gameover->h, this->screen, 0, 0, 255);
}


/**
* Initiates the main loop for the SDL opengl interface
* Handle Window Scope and ship movement
*
* @return void
*/

void SdlGLMap::run()
{  	
    SDL_Event event;
    this->gameOver = 0;

    /* message pump */
    while (!this->gameOver)
    {
        /* look for an event */
        if (SDL_PollEvent(&event)) // Conditional jump or move depends on uninitialised value(s) (WELL SORRY!)
        {
            /* an event was found */
            switch (event.type)
            {
                /* close button clicked */
                case SDL_QUIT:
                    this->gameOver = 1;
                    break;

                    // http://falconpl.org/project_docs/sdl/class_SDLK.html
                    /* handle the keyboard */
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            /* escape key or q is pressed */
                            this->gameOver = 1;
                            break;
                        case SDLK_F3:
                            this->drawSolarSystem();
                            break;
                        case SDLK_F2:
                            this->drawGalaxy();
                            break;
                        case SDLK_F1:
                            this->drawIntro();
                            break;
                        case SDLK_LEFT:
                            /* see what scope were in and act accordingly */
                            if(this->galaxyScope==true)
                            {
                                if(this->currentSystem->nextSolarSystem("ahead")!=NULL)
                                {
                                    this->shipX = 80;
                                    this->shipY = 570;
                                    OPENGL_ZORKTREK_INTERFACE->openGLwarpSolarSystem("port");
                                    Mix_PlayChannel(-1, this->warp, 0); // play theme tune (-1 let subsystem select channel,
                                    this->drawGalaxy();
                                }
                            }
                            else
                            {
                                this->moveShip(25,0,0,0);
                            }
                            break;
                        case SDLK_RIGHT:
                            /* see what scope were in and act accordingly */
                            if(this->galaxyScope==true)
                            {
                                if(this->currentSystem->nextSolarSystem("back")!=NULL)
                                {
                                    this->shipX = 80;
                                    this->shipY = 570;
                                    OPENGL_ZORKTREK_INTERFACE->openGLwarpSolarSystem("starboard");
                                    Mix_PlayChannel(-1, this->warp, 0); // play theme tune (-1 let subsystem select channel,
                                    this->drawGalaxy();
                                }
                            }
                            else
                            {
                                this->moveShip(0,25,0,0);
                            }
                            break;
                        case SDLK_UP:
                            /* see what scope were in and act accordingly */
                            if(this->galaxyScope==true)
                            {
                                if(this->currentSystem->nextSolarSystem("port")!=NULL)
                                {
                                    this->shipX = 80;
                                    this->shipY = 570;
                                    OPENGL_ZORKTREK_INTERFACE->openGLwarpSolarSystem("ahead");
                                    Mix_PlayChannel(-1, this->warp, 0); // play theme tune (-1 let subsystem select channel,
                                    this->drawGalaxy();
                                }
                            }
                            else
                            {
                                this->moveShip(0,0,25,0);
                            }
                            break;
                        case SDLK_DOWN:
                            /* see what scope were in and act accordingly */
                            if(this->galaxyScope==true)
                            {
                                if(this->currentSystem->nextSolarSystem("starboard")!=NULL)
                                {
                                    this->shipX = 80;
                                    this->shipY = 570;
                                    OPENGL_ZORKTREK_INTERFACE->openGLwarpSolarSystem("back");
                                    Mix_PlayChannel(-1, this->warp, 0); // play theme tune (-1 let subsystem select channel,
                                    this->drawGalaxy();
                                }
                            }
                            else
                            {
                                this->moveShip(0,0,0,25);
                            }
                            break;
                    }
                    break;

                        case SDL_MOUSEMOTION:
                            //printf("Mouse moved by %d,%d to (%d,%d)\n", event.motion.xrel, event.motion.yrel, event.motion.x, event.motion.y);
                            //fflush(stdout);
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            this->handleMouseClick(event);
                            break;

            }
        }

        /* update the screen */
        SDL_UpdateRect(this->screen, 0, 0, 0, 0);
    }

    this->drawGameOver();
    /* update the screen */
    SDL_UpdateRect(this->screen, 0, 0, 0, 0);
    SDL_Delay(5000);
    this->~SdlGLMap();

}


/**
* Handle Mouse Click Events
*
* @param SDL event
*
* @return void
*
*/

void SdlGLMap::handleMouseClick(SDL_Event event)
{
    if(OPENGL_ZORKTREK_INTERFACE->getPlayer()->getIsWreck()==true)
    {
        this->gameOver = 1;
    }

    /* target enemy */
    for(unsigned int t = 0; t < this->enemyPositions.size(); t++)
    {
        SDL_Rect temp = this->enemyPositions[t];
        // love the magic numbers
        // the size of the images 60 * 60
        if((event.button.x > temp.x) && (event.button.x < temp.x + 60) && (event.button.y > temp.y) && (event.button.y < temp.y + 60))
        {
            OPENGL_ZORKTREK_INTERFACE->openGLTargetShip(t);
            this->enemyTarget = t;
            this->moonTarget = -1;
            this->planetTarget = -1;
            this->hasCelestialTarget = false;
            if(this->lastTargetMoon = true)
            {
                this->drawSolarSystem();
                this->lastTargetMoon = false;
            }
            else
            {
                this->drawEnemies();
                this->drawCelestials();
                this->drawBattleRant();
            }
            return;
        }
    }

    /* target planet */
    for(unsigned int t = 0; t < this->planetPositions.size(); t++)
    {
        SDL_Rect temp = this->planetPositions[t];
        // love the magic numbers
        // the size of the images 60 * 60
        if((event.button.x > temp.x) && (event.button.x < temp.x + 60) && (event.button.y > temp.y) && (event.button.y < temp.y + 60))
        {
            OPENGL_ZORKTREK_INTERFACE->openGLTargetPlanet(t);
            this->enemyTarget = -1;
            this->moonTarget = -1;
            this->planetTarget = t;
            this->hasCelestialTarget = true;
            if(this->lastTargetMoon = true)
            {
                this->drawSolarSystem();
                this->lastTargetMoon = false;
            }
            else
            {
                this->drawEnemies();
                this->drawCelestials();
                this->drawBattleRant();
            }
            return;
        }
    }

    /* target moon */
    for(unsigned int t = 0; t < this->moonPositions.size(); t++)
    {
        SDL_Rect temp = this->moonPositions[t];
        // love the magic numbers
        // the size of the images 60 * 60
        if((event.button.x > temp.x) && (event.button.x < temp.x + 60) && (event.button.y > temp.y) && (event.button.y < temp.y + 60))
        {
            OPENGL_ZORKTREK_INTERFACE->openGLTargetMoon(t);
            this->enemyTarget = -1;
            this->moonTarget = t;
            this->planetTarget = -1;
            this->hasCelestialTarget = true;
            if(this->lastTargetMoon = true)
            {
                this->drawSolarSystem();
                this->lastTargetMoon = true;
            }
            else
            {
                this->drawEnemies();
                this->drawCelestials();
                this->drawBattleRant();
                this->lastTargetMoon = true;
            }
            return;
        }
    }

    /* clicked on phasers */
    if((event.button.x > 20) && (event.button.x < 60) && (event.button.y > 640) && (event.button.y < 680))
    {
        OPENGL_ZORKTREK_INTERFACE->openGLPhaser();
        if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()!=NULL)
        {
            if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()->getIsWreckPVE()==true)
            {
                Mix_PlayChannel(-1, this->explosion, 0); // play theme tune (-1 let subsystem select channel,
                this->drawEnemies();
            }
            else
            {
                Mix_PlayChannel(-1, this->phasers, 0); // play theme tune (-1 let subsystem select channel,
            }
        }

        this->drawToolbar();
        this->drawShipIndicators();
        this->drawBattleRant();
        return;
    }

    /* clicked on scanner */
    if((event.button.x > 65) && (event.button.x < 105) && (event.button.y > 640) && (event.button.y < 680))
    {
        if(OPENGL_ZORKTREK_INTERFACE->getMoonTarget()!=NULL)
        {
            OPENGL_ZORKTREK_INTERFACE->openGLScanMoon(this->moonTarget);
        }
        if(OPENGL_ZORKTREK_INTERFACE->getPlanetTarget()!=NULL)
        {
            OPENGL_ZORKTREK_INTERFACE->openGLScanPlanet(this->planetTarget);
        }
        if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()!=NULL)
        {
            OPENGL_ZORKTREK_INTERFACE->openGLScanShip(this->enemyTarget);
        }
        return;
    }

    /* clicked on photons */
    if((event.button.x > 20) && (event.button.x < 60) && (event.button.y > 550) && (event.button.y < 590))
    {
        OPENGL_ZORKTREK_INTERFACE->openGLPhoton();
        if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()!=NULL)
        {
            if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()->getIsWreckPVE()==true)
            {
                Mix_PlayChannel(-1, this->explosion, 0); // play theme tune (-1 let subsystem select channel,
                this->drawEnemies();
            }
            else
            {
                Mix_PlayChannel(-1, this->torpedo2, 0); // play theme tune (-1 let subsystem select channel,
            }
        }
        this->drawToolbar();
        this->drawShipIndicators();
        this->drawBattleRant();
        return;
    }

    /* clicked on quantums */
    if((event.button.x > 20) && (event.button.x < 60) && (event.button.y > 595) && (event.button.y < 635))
    {
        OPENGL_ZORKTREK_INTERFACE->openGLQuantum();
        if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()!=NULL)
        {
            if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()->getIsWreckPVE()==true)
            {
                Mix_PlayChannel(-1, this->explosion, 0); // play theme tune (-1 let subsystem select channel,
                this->drawEnemies();
            }
            else
            {
                Mix_PlayChannel(-1, this->torpedo1, 0); // play theme tune (-1 let subsystem select channel,
            }
        }
        this->drawToolbar();
        this->drawShipIndicators();
        this->drawBattleRant();
        return;
    }

    /* clicked on food */
    if((event.button.x > 155) && (event.button.x < 195) && (event.button.y > 595) && (event.button.y < 635))
    {
        printf("food\n");
        fflush(stdout);
        this->drawToolbar();
        return;
    }

    /* clicked on water */
    if((event.button.x > 155) && (event.button.x < 195) && (event.button.y > 640) && (event.button.y < 680))
    {
        printf("water\n");
        fflush(stdout);
        this->drawToolbar();
        return;
    }

    /* clicked on dilithium */
    if((event.button.x > 200) && (event.button.x < 240) && (event.button.y > 550) && (event.button.y < 590))
    {
        printf("dilthium\n");
        fflush(stdout);
        this->drawToolbar();
        return;
    }

    /* clicked on trianium */
    if((event.button.x > 200) && (event.button.x < 240) && (event.button.y > 595) && (event.button.y < 635))
    {
        printf("trianium\n");
        fflush(stdout);
        this->drawToolbar();
        return;
    }

    /* clicked on plasma */
    if((event.button.x > 200) && (event.button.x < 240) && (event.button.y > 640) && (event.button.y < 680))
    {
        printf("plasma\n");
        fflush(stdout);
        this->drawToolbar();
        return;
    }
}


/**
* Ships moves linearly up, down left right
* Handles moving into a hotspot (warp out)
*
* @param l (move left by)
* @param r (move right by)
* @param u (move up by)
* @param d (move down by)
*
* @return void
*
*/

void SdlGLMap::moveShip(unsigned int l = 0, unsigned int r = 0, unsigned int u = 0, unsigned int d = 0)
{
    // window dimensions 1024 * 700
    // lots of magic numbers woot!
    // screen dimensions lad
    // draw a surface outside the screen area, will result in a major hickup
    // we should probably just try move the surface later!

    if(OPENGL_ZORKTREK_INTERFACE->getPlayer()->getIsWreck()==true)
    {
        this->gameOver = 1;
    }

    if((this->shipX > 0) && (this->shipX < 30) && (this->shipY > 270) && (this->shipY < 320))
    {
        if(this->currentSystem->nextSolarSystem("port")!=NULL)
        {
            this->shipX = 80;
            this->shipY = 570;
            OPENGL_ZORKTREK_INTERFACE->openGLwarpSolarSystem("ahead");
            Mix_PlayChannel(-1, this->warp, 0); // play theme tune (-1 let subsystem select channel,
            this->drawSolarSystem();
        }
        return;
    }

    if((this->shipX > 920) && (this->shipX < 1024) && (this->shipY > 270) && (this->shipY < 320))
    {
        if(this->currentSystem->nextSolarSystem("back")!=NULL)
        {
            this->shipX = 80;
            this->shipY = 570;
            OPENGL_ZORKTREK_INTERFACE->openGLwarpSolarSystem("starboard");
            Mix_PlayChannel(-1, this->warp, 0); // play theme tune (-1 let subsystem select channel,
            this->drawSolarSystem();
        }
        return;
    }

    if((this->shipX > 470) && (this->shipX < 530) && (this->shipY > 0) && (this->shipY < 40))
    {
        if(this->currentSystem->nextSolarSystem("port")!=NULL)
        {
            this->shipX = 80;
            this->shipY = 570;
            OPENGL_ZORKTREK_INTERFACE->openGLwarpSolarSystem("ahead");
            Mix_PlayChannel(-1, this->warp, 0); // play theme tune (-1 let subsystem select channel,
            this->drawSolarSystem();
        }
        return;
    }

    if((this->shipX > 470) && (this->shipX < 530) && (this->shipY > 608) && (this->shipY < 708))
    {
        if(this->currentSystem->nextSolarSystem("starboard")!=NULL)
        {
            this->shipX = 80;
            this->shipY = 570;
            OPENGL_ZORKTREK_INTERFACE->openGLwarpSolarSystem("back");
            Mix_PlayChannel(-1, this->warp, 0); // play theme tune (-1 let subsystem select channel,
            this->drawSolarSystem();
        }
        return;
    }


    if(l>0 && this->shipX > 10)
    {
        this->shipX -= l;
        this->drawSolarSystem();
        return;
    }

    if(r>0 && this->shipX < 954)
    {
        this->shipX += r;
        this->drawSolarSystem();
        return;
    }

    if(u>0 && this->shipY > 10)
    {
        this->shipY -= u;
        this->drawSolarSystem();
        return;
    }

    if(d>0 && this->shipY < 638)
    {
        this->shipY += d;
        this->drawSolarSystem();
        return;
    }
}


/**
* Draws ship at current location
*
* @return void
*/

void SdlGLMap::drawShip()
{	
    SDL_Rect dest;
    dest.x = this->shipX;
    dest.y = this->shipY;    

    this->drawImage(this->ship, 0,0, this->ship->w, this->ship->h, this->screen, dest.x, dest.y, 255);		
}


/**
* Calls procedural redraw of the entire solar system
*
* @see drawCelestials
* @see drawEnemies
* @see drawToolbar
* @see drawBattleRant
* @see drawShip
* @see drawShipIndicators
*
* @return void
*
*/

void SdlGLMap::drawSolarSystem()
{
    this->currentSystem = OPENGL_ZORKTREK_INTERFACE->getSystem();

    this->solarScope = true;
    this->galaxyScope = false;

    this->drawImage(this->bg1, 0,0, this->bg1->w, this->bg1->h, this->screen, 0, 0, 255);

    this->drawCelestials();
    this->drawEnemies();  
    this->drawToolbar(); 
    this->drawBattleRant();  
    this->drawShip();
    this->drawShipIndicators();

    textquality quality;
    quality = shaded;

    SDL_Surface* TxtSurface;
    SDL_Rect dest;

    /* draw the system name in the top right */
    char *systemName;

    systemName = new char[this->currentSystem->getName().size() + 1];
    systemName[this->currentSystem->getName().size()] = 0;
    memcpy(systemName, this->currentSystem->getName().c_str(), this->currentSystem->getName().size());

    dest.x = 800;
    dest.y = 30;   	
    TxtSurface = this->drawtext(this->font2, 255, 255, 255, 99, 0, 0, 0, 99, systemName, quality);   
    this->drawImage(TxtSurface, 0,0, TxtSurface->w, TxtSurface->h, this->screen, dest.x, dest.y, 255);
    SDL_FreeSurface(TxtSurface);

    delete systemName;
}


/**
* Draws Boxes for user to see ship status
* armour, power etc
*
* @return void
*/

void SdlGLMap::drawShipIndicators()
{	
    SDL_Rect dest;
    SDL_Rect fontDest;

    textquality quality;
    quality = shaded;    

    stringstream out, out1, out2, out3;
    out << OPENGL_ZORKTREK_INTERFACE->getPlayer()->getArmour();
    out1 << OPENGL_ZORKTREK_INTERFACE->getPlayer()->getPower();
    out2 << OPENGL_ZORKTREK_INTERFACE->getPlayer()->getShieldStrenght();
    out3 << OPENGL_ZORKTREK_INTERFACE->getPlayer()->getCargoWeight();

    char *armour = new char[5];   
    armour[0] = out.str()[0];
    armour[1] = out.str()[1];
    armour[2] = out.str()[2];
    armour[3] = out.str()[3];
    armour[4] = 0;

    char *power = new char[5];
    power[0] = out1.str()[0];
    power[1] = out1.str()[1];
    power[2] = out1.str()[2];
    power[3] = out1.str()[3];
    power[4] = 0;

    char *shields = new char[5];
    shields[0] = out2.str()[0];
    shields[1] = out2.str()[1];
    shields[2] = out2.str()[2];
    shields[3] = out2.str()[3];
    shields[4] = 0;

    char *cargo = new char[5];
    cargo[0] = out3.str()[0];
    cargo[1] = out3.str()[1];
    cargo[2] = out3.str()[2];
    cargo[3] = out3.str()[3];
    cargo[4] = 0;

    char *shiledstxt = "Shields";
    char *armourtxt = "Armour";
    char *powertxt = "Power";
    char *cargotxt = "Cargo";


    /* armour area */
    dest.x = 300;
    dest.y = 665;   
    this->drawImage(this->armour, 0,0, this->armour->w, this->armour->h, this->screen, dest.x, dest.y, 255);
    /* draw text indicator */
    fontDest = dest;
    fontDest.x += 0;
    fontDest.y -= 20;	
    this->temp = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, armourtxt, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);
    /* write the quantity over the image */   	
    fontDest = dest;
    fontDest.x += 2;
    fontDest.y += 2;	
    this->temp = this->drawtext(this->font3, 0, 0, 0, 99, 232, 176, 112, 99, armour, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);    


    /* power area */
    dest.x = 300;
    dest.y = 620;   
    this->drawImage(this->armour, 0,0, this->armour->w, this->armour->h, this->screen, dest.x, dest.y, 255);
    /* draw text indicator */
    fontDest = dest;
    fontDest.x += 0;
    fontDest.y -= 20;	
    this->temp = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, powertxt, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);
    /* write the quantity over the image */   	
    fontDest = dest;
    fontDest.x += 2;
    fontDest.y += 2;	
    this->temp = this->drawtext(this->font3, 0, 0, 0, 99, 232, 176, 112, 99, power, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);


    /* shields area */
    dest.x = 370;
    dest.y = 665;    
    this->drawImage(this->shields, 0,0, this->shields->w, this->shields->h, this->screen, dest.x, dest.y, 255);
    /* draw text indicator */
    fontDest = dest;
    fontDest.x += 0;
    fontDest.y -= 20;	
    this->temp = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, shiledstxt, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);
    /* write the quantity over the image */   	
    fontDest = dest;
    fontDest.x += 2;
    fontDest.y += 2;	
    this->temp = this->drawtext(this->font3, 0, 0, 0, 99, 0, 144, 216, 99, shields, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);


    /* cargo area */
    dest.x = 370;
    dest.y = 620;    
    this->drawImage(this->shields, 0,0, this->shields->w, this->shields->h, this->screen, dest.x, dest.y, 255);
    /* draw text indicator */
    fontDest = dest;
    fontDest.x += 0;
    fontDest.y -= 20;	
    this->temp = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, cargotxt, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);
    /* write the quantity over the image */   	
    fontDest = dest;
    fontDest.x += 2;
    fontDest.y += 2;	
    this->temp = this->drawtext(this->font3, 0, 0, 0, 99, 0, 144, 216, 99, cargo, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);


    delete shields;
    delete armour; 
}


/**
* Draws the introduction Screen
* Plays intro music
*
* @return void
*/

void SdlGLMap::drawIntro()
{

    this->solarScope = false;
    this->galaxyScope = false;

    this->drawImage(this->introbg, 0,0, this->introbg->w, this->introbg->h, this->screen, 0, 0, 255);

    if(this->playedInto == false)
    {
        this->playedInto = true;
        Mix_PlayChannel(-1, this->themetune, 0); // play theme tune (-1 let subsystem select channel,
    }

    textquality quality;
    quality = shaded;

    SDL_Surface* TxtSurface;
    SDL_Rect dest;

    char *intro = "INTRO          (F1)";    
    char *map =   "GALAXY         (F2)";
    char *solar = "SOLARSYSTEM    (F3)";

    dest.x = 450;
    dest.y = 310;   	
    TxtSurface = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, intro, quality);   
    this->drawImage(TxtSurface, 0,0, TxtSurface->w, TxtSurface->h, this->screen, dest.x, dest.y, 255);
    SDL_FreeSurface(TxtSurface);

    dest.x = 450;
    dest.y = 350;   	
    TxtSurface = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, map, quality);   
    this->drawImage(TxtSurface, 0,0, TxtSurface->w, TxtSurface->h, this->screen, dest.x, dest.y, 255);
    SDL_FreeSurface(TxtSurface);

    dest.x = 450;
    dest.y = 390;   	
    TxtSurface = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, solar, quality);   
    this->drawImage(TxtSurface, 0,0, TxtSurface->w, TxtSurface->h, this->screen, dest.x, dest.y, 255);
    SDL_FreeSurface(TxtSurface);

}


/**
* Draws the galaxy map
*
* @return void
*
*/

void SdlGLMap::drawGalaxy()
{
    this->solarScope = false;
    this->galaxyScope = true;
    this->battleStarted = false;

    this->drawImage(this->bg, 0,0, this->bg->w, this->bg->h, this->screen, 0, 0, 255);

    this->Galaxy = OPENGL_ZORKTREK_INTERFACE->getGalaxy();
    this->currentSystem = OPENGL_ZORKTREK_INTERFACE->getSystem();

    map<int, Cols>::const_iterator it;
    map<int, SolarSystem*>::const_iterator it2;

    textquality quality;
    quality = shaded;

    SDL_Surface* newTxtSurface;
    SDL_Surface* newTxtSurface2;
    SDL_Rect dest;
    SDL_Rect dest2;

    char *a;

    unsigned int x = 60;
    unsigned int y = 60;

    char r = 255;
    char g = 255;
    char b = 255;
    char rb = 255;
    char gb = 255;
    char bb = 255;

    char *emy = ".";
    char *legendEnemy = "enemy";
    char *legendPlanet = "planet";

    dest2.x = 460;
    dest2.y = 10;   	
    newTxtSurface2 = this->drawtext(this->font, 255, 255, 255, 99, 50, 100, 150, 99, legendEnemy, quality);   
    this->drawImage(newTxtSurface2, 0,0, newTxtSurface2->w, newTxtSurface2->h, this->screen, dest2.x, dest2.y, 255);
    SDL_FreeSurface(newTxtSurface2);

    dest2.x = 520;
    dest2.y = 10;    	
    newTxtSurface2 = this->drawtext(this->font, 255, 255, 255, 99, 150, 100, 50, 99, legendPlanet, quality);   
    this->drawImage(newTxtSurface2, 0,0, newTxtSurface2->w, newTxtSurface2->h, this->screen, dest2.x, dest2.y, 255);
    SDL_FreeSurface(newTxtSurface2);

    for ( it = this->Galaxy.begin(); it != this->Galaxy.end(); ++it )
    {
        for ( it2 = it->second.begin(); it2 != it->second.end(); ++it2 )
        {
            //std::string s
            a = new char[it2->second->getName().size() + 1];
            a[it2->second->getName().size()] = 0;
            memcpy(a, it2->second->getName().c_str(), it2->second->getName().size());

            if(it2->second->nextSolarSystem("port")==NULL && it2->second->nextSolarSystem("starboard")==NULL && it2->second->nextSolarSystem("back")==NULL && it2->second->nextSolarSystem("ahead")==NULL)
            {
                r = 80;
                g = 80;
                b = 80;
                rb = 150;
                gb = 150;
                bb = 150;
            }
            else
            {
                r = 0;
                g = 255;
                b = 0;
                rb = 0;
                gb = 100;
                bb = 100;
            }

            if(this->currentSystem->getName().compare(it2->second->getName()) == 0)
            {
                r = 255;
                g = 0;
                b = 0;
                rb = 1;
                gb = 1;
                bb = 1;
            }


            newTxtSurface = this->drawtext(this->font, r, g, b, 99, rb, gb, bb, 99, a, quality);

            a = NULL;

            dest.x = x;
            dest.y = y;

            this->drawImage(newTxtSurface, 0,0, newTxtSurface->w, newTxtSurface->h, this->screen, dest.x, dest.y, 255);
            SDL_FreeSurface(newTxtSurface);

            if(it2->second->getPVEEntity().size()>0)
            {
                for(unsigned int h = 0; h < it2->second->getPVEEntity().size(); h++)
                {
                    dest2.x = dest.x + (10 * h);
                    dest2.y = dest.y - 20;
                    newTxtSurface2 = this->drawtext(this->font, 50, 100, 150, 99, 50, 100, 150, 99, emy, quality);
                    this->drawImage(newTxtSurface2, 0,0, newTxtSurface2->w, newTxtSurface2->h, this->screen, dest2.x, dest2.y, 255);
                    SDL_FreeSurface(newTxtSurface2);
                }
            }

            if(it2->second->getSystemPlanets().size()>0)
            {
                for(unsigned int h = 0; h < it2->second->getSystemPlanets().size(); h++)
                {
                    dest2.x = dest.x + (10 * h);
                    dest2.y = dest.y + 20;
                    newTxtSurface2 = this->drawtext(this->font, 150, 100, 50, 99, 150, 100, 50, 99, emy, quality);
                    this->drawImage(newTxtSurface2, 0,0, newTxtSurface2->w, newTxtSurface2->h, this->screen, dest2.x, dest2.y, 255);
                    SDL_FreeSurface(newTxtSurface2);
                }
            }

            x += 120;
        }
        y += 80;
        x = 60;
    }

    emy = NULL;
    legendEnemy = NULL;
    legendPlanet = NULL;
    delete a;
}


/**
* Draws the toolbar icons
*
* @return void
*/

void SdlGLMap::drawToolbar()
{
    SDL_Rect dest;
    SDL_Rect fontDest;

    textquality quality;
    quality = shaded;    

    stringstream out, out1;
    out << OPENGL_ZORKTREK_INTERFACE->getPlayer()->getPhotons();
    out1 << OPENGL_ZORKTREK_INTERFACE->getPlayer()->getQuantums();

    char *buf = new char[5];
    buf[0] = out.str()[0];
    buf[1] = out.str()[1];
    buf[2] = out.str()[2];
    buf[3] = 0;

    char *buf2 = new char[5];
    buf2[0] = out1.str()[0];
    buf2[1] = out1.str()[1];
    buf2[2] = 0;

    /* photon button area */
    dest.x = 20;
    dest.y = 550;   
    this->drawImage(this->photons, 0,0, this->photons->w, this->photons->h, this->screen, dest.x, dest.y, 255);
    /* write the quantity over the image */   	
    fontDest = dest;
    fontDest.x += 6;
    fontDest.y += 6;	
    this->temp = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, buf, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);

    /* quantum area */
    dest.x = 20;
    dest.y = 595;    
    this->drawImage(this->quantums, 0,0, this->quantums->w, this->quantums->h, this->screen, dest.x, dest.y, 255);
    /* write the quantity over the image */   	
    fontDest = dest;
    fontDest.x += 6;
    fontDest.y += 6;	
    this->temp = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, buf2, quality);
    this->drawImage(this->temp, 0, 0, this->temp->w, this->temp->h, this->screen, fontDest.x, fontDest.y, 255);

    /* laser area */
    dest.x = 20;
    dest.y = 640;  
    this->drawImage(this->lasers, 0,0, this->lasers->w, this->lasers->h, this->screen, dest.x, dest.y, 255);  

    /* scanner area */
    dest.x = 65;
    dest.y = 640;    
    this->drawImage(this->scanner, 0,0, this->scanner->w, this->scanner->h, this->screen, dest.x, dest.y, 255); 

    /* tansporter area     
    dest.x = 110;
    dest.y = 640;  
    this->drawImage(this->beam, 0,0, this->beam->w, this->beam->h, this->screen, dest.x, dest.y, 255);   
     */

    if(this->hasCelestialTarget == true)
    {
        dest.x = 155;
        dest.y = 595;
        this->drawImage(this->bFood, 0,0, this->beam->w, this->beam->h, this->screen, dest.x, dest.y, 255);

        dest.x = 155;
        dest.y = 640;
        this->drawImage(this->bWater, 0,0, this->beam->w, this->beam->h, this->screen, dest.x, dest.y, 255);

        dest.x = 200;
        dest.y = 550;
        this->drawImage(this->bDilithium, 0,0, this->beam->w, this->beam->h, this->screen, dest.x, dest.y, 255);

        dest.x = 200;
        dest.y = 595;
        this->drawImage(this->bTrianium, 0,0, this->beam->w, this->beam->h, this->screen, dest.x, dest.y, 255);

        dest.x = 200;
        dest.y = 640;
        this->drawImage(this->bPlasma, 0,0, this->beam->w, this->beam->h, this->screen, dest.x, dest.y, 255);
    }


    dest.x = 10;
    dest.y = 309;
    if(this->currentSystem->nextSolarSystem("ahead")!=NULL)
        this->drawImage(this->left, 0,0, this->left->w, this->left->h, this->screen, dest.x, dest.y, 255);
    dest.x = 992;
    dest.y = 309;
    if(this->currentSystem->nextSolarSystem("back")!=NULL)
        this->drawImage(this->right, 0,0, this->right->w, this->right->h, this->screen, dest.x, dest.y, 255);
    dest.x = 502;
    dest.y = 10;
    if(this->currentSystem->nextSolarSystem("port")!=NULL)
        this->drawImage(this->up, 0,0, this->up->w, this->up->h, this->screen, dest.x, dest.y, 255);
    dest.x = 502;
    dest.y = 670;
    if(this->currentSystem->nextSolarSystem("starboard")!=NULL)
        this->drawImage(this->down, 0,0, this->down->w, this->down->h, this->screen, dest.x, dest.y, 255);

    delete buf;
    delete buf2;
}


/**
* Draws the plants and moons
*
* @return void
*/

void SdlGLMap::drawCelestials()
{	
    SDL_Surface* planetSurface;
    SDL_Surface* planetTxtSurface;
    SDL_Rect dest;
    SDL_Rect targetDest;
    SDL_Rect mdest1, mdest2, mdest3;
    SDL_Rect fontDest;

    dest.x = 900;
    dest.y = 120;  

    mdest1 = dest;
    mdest2 = dest;
    mdest3 = dest;    

    fontDest.x = dest.x -100;
    fontDest.y = dest.y + 15;

    char *planetName;

    textquality quality;
    quality = shaded;

    this->planetPositions.clear();
    this->moonPositions.clear();

    for(unsigned int j = 0; j < this->currentSystem->getSystemPlanets().size(); j++)
    {     	  	    
        if(j==0) planetSurface = this->planet1;
        else if(j==1) planetSurface = this->planet2;
        else if(j==2) planetSurface = this->planet3;
        else if(j==3) planetSurface = this->planet4;
        else planetSurface = this->planet5;

        for(unsigned int g = 0; g < this->currentSystem->getSystemPlanets()[j]->getMoons().size(); g++)
        {
            if(g==0)
            {
                mdest1.y -= 40;
                mdest1.x += 40;
                this->drawImage(this->moon, 0,0, this->moon->w, this->moon->h, this->screen, mdest1.x, mdest1.y, 255);
                this->moonPositions.push_back(mdest1);

                if(OPENGL_ZORKTREK_INTERFACE->getMoonTarget()!=NULL)
                {
                    if(OPENGL_ZORKTREK_INTERFACE->getMoonTarget()==this->currentSystem->getSystemPlanets()[j]->getMoons()[g])
                    {
                        targetDest = mdest1;
                        this->drawImage(this->targetIndicator, 0,0, this->targetIndicator->w, this->targetIndicator->h, this->screen, targetDest.x, targetDest.y, 255);
                    }
                }
            }
            else
            {
                mdest2.y += 80;
                mdest2.x += 40;
                this->drawImage(this->moon, 0,0, this->moon->w, this->moon->h, this->screen, mdest2.x, mdest2.y, 255);
                this->moonPositions.push_back(mdest2);

                if(OPENGL_ZORKTREK_INTERFACE->getMoonTarget()!=NULL)
                {
                    if(OPENGL_ZORKTREK_INTERFACE->getMoonTarget()==this->currentSystem->getSystemPlanets()[j]->getMoons()[g])
                    {
                        targetDest = mdest2;
                        this->drawImage(this->targetIndicator, 0,0, this->targetIndicator->w, this->targetIndicator->h, this->screen, targetDest.x, targetDest.y, 255);
                    }
                }
            }
        }

        this->drawImage(planetSurface, 0,0, planetSurface->w, planetSurface->h, this->screen, dest.x, dest.y, 255);
        this->planetPositions.push_back(dest);

        /* draw the name of the planet */
        char *buf = new char[this->currentSystem->getSystemPlanets()[j]->getName().size() + 1];
        for(unsigned int p = 0; p < this->currentSystem->getSystemPlanets()[j]->getName().size(); p++)
            buf[p] = this->currentSystem->getSystemPlanets()[j]->getName()[p];

        buf[this->currentSystem->getSystemPlanets()[j]->getName().size()] = 0;
        planetName = buf;
        planetTxtSurface = this->drawtext(this->font, 255, 255, 255, 99, 0, 0, 0, 99, planetName, quality);
        this->drawImage(planetTxtSurface, 0,0, planetTxtSurface->w, planetTxtSurface->h, this->screen, fontDest.x, fontDest.y, 255);
        delete []buf;
        /* end name */

        if(OPENGL_ZORKTREK_INTERFACE->getPlanetTarget()!=NULL)
        {
            if(OPENGL_ZORKTREK_INTERFACE->getPlanetTarget()==this->currentSystem->getSystemPlanets()[j])
            {
                targetDest = dest;
                targetDest.x += 20;
                targetDest.y += 20;
                this->drawImage(this->targetIndicator, 0,0, this->targetIndicator->w, this->targetIndicator->h, this->screen, targetDest.x, targetDest.y, 255);
            }
        }

        dest.x -= 110;
        dest.y += 100;

        mdest1 = dest;
        mdest2 = dest;
        mdest3 = dest;

        fontDest.x = dest.x - 100;
        fontDest.y = dest.y + 15;
    }
}


/**
* Draws the borg ships
*
* @return void
*/

void SdlGLMap::drawEnemies()
{
    SDL_Rect dest;
    SDL_Rect targetDest;
    SDL_Rect fontDest;

    SDL_Surface* vessel;	
    SDL_Surface* vesselTxtSurface;

    dest.x = 350;
    dest.y = 50;  

    fontDest.x = dest.x;
    fontDest.y = dest.y;

    textquality quality;
    quality = shaded;

    this->enemyPositions.clear();

    for(unsigned int j = 0; j < this->currentSystem->getPVEEntity().size(); j++)
    {     	  	    
        if(this->currentSystem->getPVEEntity()[j]->getName().compare("Borg cube")==0) vessel = this->cube;
        else if(this->currentSystem->getPVEEntity()[j]->getName().compare("Borg tactical cube")==0) vessel = this->tacticalcube;
        else if(this->currentSystem->getPVEEntity()[j]->getName().compare("Borg probe")==0) vessel = this->probe;
        else if(this->currentSystem->getPVEEntity()[j]->getName().compare("Borg sphere")==0) vessel = this->sphere;
        else vessel = this->cube;

        if(this->currentSystem->getPVEEntity()[j]->getIsWreckPVE() == true)
            vessel = this->borgwreck;

        this->enemyPositions.push_back(dest);
        this->drawImage(vessel, 0,0, vessel->w, vessel->h, this->screen, dest.x, dest.y, 255);

        if(OPENGL_ZORKTREK_INTERFACE->getBattle()!=NULL)
        {
            if(OPENGL_ZORKTREK_INTERFACE->getBattle()->getEnemy()==this->currentSystem->getPVEEntity()[j])
            {
                fontDest.x = dest.x - 10;
                fontDest.y = dest.y - 10;
                char *buf = "*";
                vesselTxtSurface = this->drawtext(this->font, 255, 0, 0, 99, 0, 0, 0, 99, buf, quality);
                this->drawImage(vesselTxtSurface, 0,0, vesselTxtSurface->w, vesselTxtSurface->h, this->screen, fontDest.x, fontDest.y, 255);
            }
        }
        if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()!=NULL)
        {
            if(OPENGL_ZORKTREK_INTERFACE->getEnemyTarget()==this->currentSystem->getPVEEntity()[j])
            {
                targetDest = dest;
                targetDest.x += 20;
                targetDest.y += 20;
                this->drawImage(this->targetIndicator, 0,0, this->targetIndicator->w, this->targetIndicator->h, this->screen, targetDest.x, targetDest.y, 255);
            }
        }

        if(j==1 || j==3)
        {
            if(j==3)
            {
                dest.x = 350;
                dest.y = 290;
            }
            else
            {
                dest.x = 350;
                dest.y = 170;
            }
        }
        else
        {
            dest.x += 120;
        }
    }	
}


/**
* Load a font
*
* @param file (the font)
* @param ptsize (the size of the font you would like)
*
* @return TTF_Font* the font with size
*
*/

TTF_Font* SdlGLMap::loadfont(char* file, int ptsize)
{
    TTF_Font* tmpfont;
    tmpfont = TTF_OpenFont(file, ptsize);
    if (tmpfont == NULL){
        printf("Unable to load font: %s %s \n", file, TTF_GetError());
        // Handle the error here.
    }
    return tmpfont;
}


/**
* Creates a SDL surface with text (font applied)
*
* @param fonttodraw (pointer to the previously made font)
* @param fgR (foreground Red)
* @param fgG (foreground green)
* @param fgB (foreground blue)
* @param fgA (foreground alpha)
*
* @param bgR (background Red)
* @param bgG (background green)
* @param bgB (background blue)
* @param bgA (background alpha)
*
* @param text[] the string to apply to the surface
*
* @param enum texture quality
*
* @return SDL_surface (the newly created surface)
*
*/

SDL_Surface* SdlGLMap::drawtext(TTF_Font *fonttodraw, char fgR, char fgG, char fgB, char fgA, char bgR, char bgG, char bgB, char bgA, char text[], textquality quality)
{
    SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
    SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
    SDL_Surface *resulting_text;

    if (quality == solid)
    {
        resulting_text = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
    }
    else if (quality == shaded)
    {
        resulting_text = TTF_RenderText_Shaded(fonttodraw, text, tmpfontcolor, tmpfontbgcolor);
    }
    else if (quality == blended)
    {
        resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);
    }
    return resulting_text;
}


/**
* Draws a surface on top of another surface
*
* @param srcimg* the surface to draw
*
* @param sx x position
* @param sy y position
* @param sw width
* @param sh height
*
* @param dstimg* the surface to draw onto
*
* @param dx x position
* @param dy y position
*
* @param alpha the color which has going to be transparent
*
* @return void
*/

void SdlGLMap::drawImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh, SDL_Surface *dstimg, int dx, int dy, int alpha = 255) 
{
    if ((srcimg == NULL) || (alpha == 0)) return; //If theres no image, or its 100% transparent.
    SDL_Rect src, dst;

    src.x = sx;  src.y = sy;  src.w = sw;  src.h = sh;
    dst.x = dx;  dst.y = dy;  dst.w = src.w;  dst.h = src.h;
    if (alpha != 255) SDL_SetAlpha(srcimg, SDL_SRCALPHA, alpha);

    SDL_BlitSurface(srcimg, &src, dstimg, &dst);
}


/**
* Load an image as an SDL surface
*
* @param file "the file name to load"
* @param transparency bool apply transparency or not
*
*/

SDL_Surface* SdlGLMap::loadImage(char *file, bool transparency) 
{
    SDL_Surface *tmp;
    tmp = IMG_Load(file);

    if (tmp == NULL)
    {
        fprintf(stderr, "Error: '%s' could not be opened: %s\n", file, IMG_GetError());
    }
    else
    {
        if(transparency == true)
        {
            if(SDL_SetColorKey(tmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tmp->format, COLORKEY)) == -1)
                fprintf(stderr, "Warning: colorkey will not be used, reason: %s\n", SDL_GetError());
        }
    }
    return tmp;
}
