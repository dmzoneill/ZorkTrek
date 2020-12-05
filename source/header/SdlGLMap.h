#ifndef SDLGLMAP_H_
#define SDLGLMAP_H_

#include <stdlib.h>
#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_opengl.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#endif

#include "SDL_mixer.h"
#include "SDL_image.h"

#include "SDL/SDL_ttf.h" 
#include <math.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>


#include "ZorkTrek.h";
#include "SolarSystem.h";
#include "PVEEntity.h";

// 2 dimensional map 
typedef map<int, SolarSystem*> Cols;
typedef map<int, Cols> Rows;


using std::string;
using std::stringstream;
using std::vector;
using std::map;


enum textquality {solid, shaded, blended};

class SdlGLMap
{
    private:

        SolarSystem* currentSystem;

        int gameOver;

        // battle sound has played
        bool battleStarted;

        // mouse click regions
        vector <SDL_Rect> enemyPositions;
        vector <SDL_Rect> moonPositions;
        vector <SDL_Rect> planetPositions;

        // ship position
        unsigned int shipX;
        unsigned int shipY;

        // scope (used in conjunction with polling keyboard events)
        bool galaxyScope;
        bool solarScope;
        bool hasCelestialTarget;

        // fix for moon target not being updated
        bool lastTargetMoon;
        int planetTarget;
        int moonTarget;
        int enemyTarget;

        // intro sound played
        bool playedInto;

        // the galaxy
        Rows Galaxy;

        /* surfaces and fonts */

        TTF_Font* font;
        TTF_Font* font2;
        TTF_Font* font3;

        SDL_Surface* screen;
        SDL_Surface* bg;
        SDL_Surface* bg1;
        SDL_Surface* introbg;
        SDL_Surface* temp;
        SDL_Surface* gameover;

        // planets
        SDL_Surface* planet1;
        SDL_Surface* planet2;
        SDL_Surface* planet3;
        SDL_Surface* planet4;
        SDL_Surface* planet5;
        SDL_Surface* moon;

        // borgvessels
        SDL_Surface* cube;
        SDL_Surface* tacticalcube;
        SDL_Surface* sphere;
        SDL_Surface* probe;

        // player ship
        SDL_Surface* ship;
        SDL_Surface* battleResponce;

        // weapons
        SDL_Surface* photons;
        SDL_Surface* quantums;
        SDL_Surface* lasers;

        // beam and scanner
        SDL_Surface* scanner;
        SDL_Surface* beam;

        // beam types
        SDL_Surface* bFood;
        SDL_Surface* bWater;
        SDL_Surface* bDilithium;
        SDL_Surface* bTrianium;
        SDL_Surface* bPlasma;

        // exits
        SDL_Surface* power;
        SDL_Surface* cargo;
        SDL_Surface* shields;
        SDL_Surface* armour;

        // exits
        SDL_Surface* up;
        SDL_Surface* down;
        SDL_Surface* left;
        SDL_Surface* right;

        // wrecks
        SDL_Surface* borgwreck;
        SDL_Surface* wreck;

        // target
        SDL_Surface* targetIndicator;

        //sounds
        Mix_Chunk * themetune;
        Mix_Chunk * torpedo1;
        Mix_Chunk * torpedo2;
        Mix_Chunk * warp;
        Mix_Chunk * phasers;
        Mix_Chunk * explosion;
        Mix_Chunk * borg;

        /* constructors and methods */
        void initVideo(Uint32 flags);
        void run();

        void drawGalaxy();
        void drawSolarSystem();
        void drawEnemies();
        void drawCelestials();
        void drawToolbar();
        void drawBattleRant();
        void drawShip();
        void drawIntro();
        void drawShipIndicators();
        void drawGameOver();

        void handleMouseClick(SDL_Event event);
        void moveShip(unsigned int l, unsigned int r, unsigned int u, unsigned int d);
        void drawImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh, SDL_Surface *dstimg, int dx, int dy, int alpha);

        SDL_Surface* loadImage(char *file, bool transparency);
        TTF_Font* loadfont(char* file, int ptsize);
        SDL_Surface *drawtext(TTF_Font *fonttodraw, char fgR, char fgG, char fgB, char fgA, char bgR, char bgG, char bgB, char bgA, char text[], textquality quality);


    public:
        SdlGLMap();
        ~SdlGLMap();

};

#endif /*SDLGLMAP_H_*/
