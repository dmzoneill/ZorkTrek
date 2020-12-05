#ifndef COMMANDWORDS_H_
#define COMMANDWORDS_H_

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;
using std::endl;

class CommandWords 
{
    private:

        static vector<string> validCommands;
        static vector<string> descriptions;

    public:

        CommandWords();
        ~CommandWords();
        bool isCommand(string aString);
        void showAll();
};


#endif /*COMMANDWORDS_H_*/
