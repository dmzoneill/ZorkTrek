#ifndef PARSER_H_
#define PARSER_H_

#include "Command.h"
#include "CommandWords.h"

#include <string>
#include <sstream> // string stream 

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Parser 
{
    private:
        CommandWords *commands;
        string RemoveMultipleWhiteSpaces(string s);

    public:
        Parser();
        ~Parser();
        Command* getCommand(string prefix);
        void showCommands();
};

#endif /*PARSER_H_*/
