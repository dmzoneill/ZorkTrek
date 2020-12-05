#include "CommandWords.h"

vector<string> CommandWords::validCommands;
vector<string> CommandWords::descriptions;


/**
* Constructor adds valid commands and descriptions to the vectors
*/

CommandWords::CommandWords() 
{
    if (validCommands.empty())
    {
        validCommands.push_back("warp");
        descriptions.push_back("warp <back> go <ahead> go <port> go <starboard>");
        validCommands.push_back("back");
        descriptions.push_back("go back to the previous solarsystem");
        validCommands.push_back("target");
        descriptions.push_back("target <object> - locks onto desired object");
        validCommands.push_back("launch");
        descriptions.push_back("launch <quatum || photon> - fires desired topeedo at target \n                             \033[31;5m* note\033[0m - > lock target first");
        validCommands.push_back("phaser");
        descriptions.push_back("phaser <object> - fires phaser at <object>\n                            \033[31;5m* note\033[0m - > lock target first");
        validCommands.push_back("beam");
        descriptions.push_back("beams <object> into cargohold\n                            beam <object> <amount> beams a quanity of object\n                            \033[31;5m* note\033[0m - > lock target first");
        validCommands.push_back("scan");
        descriptions.push_back("scan <> <> and return information\n                            scan - returns solarsystem information\n                            scan planetid - returns information about planet\n                            scan planetid moonid - returns planet moon information\n                            scan ship shipid - returns enemy ship information");
        validCommands.push_back("map");
        descriptions.push_back("Shows galaxy map");
        validCommands.push_back("status");
        descriptions.push_back("get a report from your chief engineer and tactical officers");
        validCommands.push_back("use");
        descriptions.push_back("use cargohold item\n                            use plasma 100 -> replenishes ships power (5 plasma = 1 unit)\n");
        validCommands.push_back("repair");
        descriptions.push_back("use trianium and dilithium to get the transwarp drive back online and escape\n");
        validCommands.push_back("transwarp");
        descriptions.push_back("Completes the game and you escape\n                            \033[31;5m* note\033[0m - > refuel and repair your transwarp engines first!");
        validCommands.push_back("quit");
        descriptions.push_back("quits the game");
        validCommands.push_back("help");
        descriptions.push_back("your looking at it");
        validCommands.push_back("startgui");
        descriptions.push_back("run the opengl interface");
    }
}


/**
* Destructor for commands
*/

CommandWords::~CommandWords() 
{
    cout << endl << "             \033[30;2m~Destructing command words\033[0m" << endl;
}


/**
* Returns true if it is a valid command
*
* @param aString the command word to test against the valid commands
*
* @return bool is valid command
*/

bool CommandWords::isCommand(string aString) 
{
    for (unsigned int i = 0; i < validCommands.size(); i++)
    {
        if (validCommands[i].compare(aString) == 0)
        {
            return true;
        }
    }
    return false;
}


/**
* Shows all the commands and their descriptions to the user
*
* @return void
*/

void CommandWords::showAll() 
{	
    int commandLen;
    int optionWidth = 10;

    cout << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                          Commands                                      \033[0m |     " << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;

    cout << "          Command    |      \033[31;1mDescription  \033[0m                                             " << endl;
    cout << "        ------------------------------------------------------------------------------------         " << endl;

    for (unsigned int i = 0; i < validCommands.size(); i++)
    {
        commandLen = validCommands[i].length();
        cout << "\033[31;1m          " << validCommands[i];

        for(int y=commandLen;y<optionWidth;y++)
            cout << " ";

        cout << "\033[0m | " << "     " << descriptions[i] << endl;
        cout << "        ------------------------------------------------------------------------------------      " << endl;
    }
    cout << endl;
}
