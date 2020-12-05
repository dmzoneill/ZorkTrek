#include "Command.h"

/**
* Constructor
* @param firstWord (command word)
* @param secondWord
* @param thirdWord
*/

Command::Command(string firstWord, string secondWord, string thirdWord) 
{
    this->commandWord = firstWord;
    this->secondWord = secondWord;
    this->thirdWord = thirdWord;
}


/**
* Destructor for the command word object
*/

Command::~Command() 
{
    // http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=/com.ibm.xlcpp8a.doc/language/ref/cplr380.htm
    // You can use a destructor explicitly to destroy objects, although this practice is not recommended.
    // However to destroy an object created with the placement new operator,

    // delete any stuff on the heap (stack is cleared automatically for us )
}


/**
* returns the command word of the command
*
* @return string
*/

string Command::getCommandWord() 
{
    return this->commandWord;
}


/**
* returns the second word of the command
*
* @return string
*/

string Command::getSecondWord() 
{
    return this->secondWord;
}


/**
* returns the third word of the command
*
* @return string
*/

string Command::getThirdWord() 
{
    return this->thirdWord;
}


/**
* returns true i the command word exists in the vector
*
* @return bool
*/

bool Command::isUnknown() 
{
    return (commandWord.empty());
}


/**
* returns true of the command has a second word
*
* @return bool
*/

bool Command::hasSecondWord() 
{
    return (!secondWord.empty());
}


/**
* returns true of the command has a third word
*
* @return bool
*/

bool Command::hasThirdWord() 
{
    return (!thirdWord.empty());
}

