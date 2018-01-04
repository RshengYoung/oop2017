#include <iostream>
#include <string>
#include "parser.h"
#include "scanner.h"

using namespace std;

int main()
{
    string input;
    while (input != "halt.")
    {
        input = "";
        string parserString = "";
        while (input == "" && input != "halt.")
        {
            cout << "?- ";
            getline(cin, input);
            if (input != "")
            {
                parserString += input;
                while (parserString.find(".") == string::npos && input != "halt.")
                {
                    cout << "|  ";
                    getline(cin, input);
                    if (input != "")
                        parserString += input;
                }
                if (input != "halt.")
                {
                    Scanner s(parserString);
                    Parser p(s);
                    try
                    {
                        p.buildExpression();
                        cout << p.getResult() << endl;
                    }
                    catch (std::string &msg)
                    {
                        cout << "Some Error: " << msg << endl;
                    }
                }
            }
        }
    }

    return 0;
}