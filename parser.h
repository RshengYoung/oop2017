#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"

class Parser
{
  public:
    Parser(Scanner scanner) : _scanner(scanner) {}
    Term *createTerm()
    {
        // int token = _scanner.nextToken();
        _currentToken = _scanner.nextToken();
        _scanner.skipLeadingWhiteSpace();
        if (_currentToken == VAR)
            return new Variable(symtable[_scanner.tokenValue()].first);
        else if (_currentToken == NUMBER)
            return new Number(_scanner.tokenValue());
        else if (_currentToken == ATOM || _currentToken == ATOMSC)
        {
            Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
            if (_scanner.currentChar() == '(')
            {
                _scanner.nextToken();
                vector<Term *> terms = {};
                if (_scanner.currentChar() == ')')
                {
                    _scanner.nextToken();
                    return new Struct(*atom, terms);
                }
                else
                {
                    terms = getArgs();
                    if (_currentToken == ')')
                        return new Struct(*atom, terms);
                }                
            }
            return atom;
        }
        else if (_currentToken == '[')
        {
            vector<Term *> terms = {};
            if (_scanner.currentChar() != ']')
            {
                terms = getArgs();
                if (_currentToken == ']')
                    return new List(terms);
                else
                    throw std::string("unexpected token");
            }
            else
            {
                _scanner.nextToken();
                return new List(terms);
            }
        }
        return nullptr;
    }

    vector<Term *> getArgs()
    {
        Term *term = createTerm();
        vector<Term *> args;
        if (term)
            args.push_back(term);
        while ((_currentToken = _scanner.nextToken()) == ',')
            args.push_back(createTerm());
        return args;
    }

  private:
    Scanner _scanner;
    int _currentToken;
};
#endif