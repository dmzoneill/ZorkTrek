#include "Parser.h"

/**
* constructor
*/

Parser::Parser() 
{
    this->commands = new CommandWords();
}


/**
* destructor
* cleans up commands
*/

Parser::~Parser() 
{	
    // http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=/com.ibm.xlcpp8a.doc/language/ref/cplr380.htm
    // You can use a destructor explicitly to destroy objects, although this practice is not recommended.
    // However to destroy an object created with the placement new operator,

    // delete any stuff on the heap (stack is cleared automatically for us )

    delete this->commands;
}


/**
* Creates a new copy of command for use in the main loop
*
* @param string prefix to be added to the line at the user input
*
* @return command
*/

Command* Parser::getCommand(string prefix) 
{
    string word1;
    string word2;
    string word3;
    string buffer;
    vector<string> words;

    cout << endl << prefix << "> ";
    getline(cin, buffer, '\n');
    string::size_type pos = 0, last_pos = 0;

    buffer = this->RemoveMultipleWhiteSpaces(buffer);

    bool finished = false;
    while (!finished)
    {
        pos = buffer.find_first_of(' ', last_pos);
        if (pos == string::npos)
        {
            words.push_back(buffer.substr(last_pos));
            finished = true;
        }
        else
        {
            words.push_back(buffer.substr(last_pos, pos - last_pos));
            last_pos = pos + 1;
        }
    }

    if (words.size() == 1)
    {
        word1 = words[0];
    }
    else if (words.size() == 2)
    {
        word1 = words[0];
        word2 = words[1];
    }
    else if (words.size() >= 3)
    {
        word1 = words[0];
        word2 = words[1];
        word3 = words[2];
    }

    if (commands->isCommand(word1))
    {
        return new Command(word1, word2, word3);
    }
    else
    {
        return new Command("", word2, word3);
    }
}


/**
* Remove unwanted whitespace from input string
*
* @param s
*
* @return string
*/

string Parser::RemoveMultipleWhiteSpaces(string s)
{ 
    string search = "  ";
    size_t index;

    while((index = s.find(search)) != string::npos )
    {
        s.erase(index,1);
    }

    return s;
}


/**
* Shows all the commands
*
* @return void
*/

void Parser::showCommands() 
{
    commands->showAll();
}

