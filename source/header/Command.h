#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <iostream>

using std::string;

class Command 
{
    private:

        string commandWord;
        string secondWord;
        string thirdWord;

    public:

        Command(string firstWord, string secondWord, string thirdWord);
        ~Command();

        string getCommandWord();
        string getSecondWord();
        string getThirdWord();

        bool isUnknown();
        bool hasSecondWord();
        bool hasThirdWord();
};

#endif /*COMMAND_H_*/
