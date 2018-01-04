#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>

using std::stack;

class Parser
{
  public:
    Parser(Scanner scanner) : _scanner(scanner), _terms() {}

    Term *createTerm()
    {
        int token = _scanner.nextToken();
        _currentToken = token;
        if (token == VAR)
        {
            for (int i = 0; i < _variableTemp.size(); i++)
                if (symtable[_scanner.tokenValue()].first == _variableTemp[i]->symbol())
                    return _variableTemp[i];
            Variable *var = new Variable(symtable[_scanner.tokenValue()].first);
            _variableTemp.push_back(var);
            return var;
        }
        else if (token == NUMBER)
        {
            return new Number(_scanner.tokenValue());
        }
        else if (token == ATOM || token == ATOMSC)
        {
            Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
            if (_scanner.currentChar() == '(')
            {
                return structure();
            }
            else
                return atom;
        }
        else if (token == '[')
        {
            return list();
        }

        return nullptr;
    }

    Term *structure()
    {
        Atom structName = Atom(symtable[_scanner.tokenValue()].first);
        int startIndexOfStructArgs = _terms.size();
        _scanner.nextToken();
        createTerms();
        if (_currentToken == ')')
        {
            vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
            _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
            return new Struct(structName, args);
        }
        else
        {
            throw string("Unbalanced operator");
        }
    }

    Term *list()
    {
        int startIndexOfListArgs = _terms.size();
        createTerms();
        if (_currentToken == ']')
        {
            vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
            _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
            if (args.size() == 0)
            {
                return new Atom("[]");
            }
            return new List(args);
        }
        else
        {
            throw string("Unbalanced operator");
        }
    }

    vector<Term *> &getTerms()
    {
        return _terms;
    }

    void buildExpression()
    {
        // createTerm();
        disjunctionMatch();
        restDisjunctionMatch();
        if (createTerm() != nullptr || _currentToken != '.')
            throw string("Missing token '.'");
    }

    

    void restDisjunctionMatch()
    {
        if (_scanner.currentChar() == ';')
        {
            _variableTemp.clear();
            createTerm();
            disjunctionMatch();
            Exp *right = _expStack.top();
            _expStack.pop();
            Exp *left = _expStack.top();
            _expStack.pop();
            _expStack.push(new DisjExp(left, right));
            restDisjunctionMatch();
        }
    }

    void disjunctionMatch()
    {
        conjunctionMatch();
        restConjunctionMatch();
    }

    void restConjunctionMatch()
    {
        if (_scanner.currentChar() == ',')
        {
            createTerm();
            conjunctionMatch();
            Exp *right = _expStack.top();
            _expStack.pop();
            Exp *left = _expStack.top();
            _expStack.pop();
            _expStack.push(new ConjExp(left, right));
            restConjunctionMatch();
        }
    }

    void conjunctionMatch()
    {
        if (_scanner.currentChar() == '.')
        {
            std::stringstream strs;
            strs << (char)_currentToken;
            string _symbol = strs.str();
            throw string ("Unexpected '" + _symbol + "' before '.'");
        }

        Term *left = createTerm();
        if (createTerm() == nullptr && _currentToken == '=')
        {
            Term *right = createTerm();
            _expStack.push(new MatchExp(left, right));
        }
        else if (_currentToken == '.')
            throw string(left->symbol() + " does never get assignment");
        else if (_currentToken != '=')
        {
            std::stringstream strs;
            strs << (char)_currentToken;            
            string _symbol = strs.str();
            throw string ("Unexpected '" + _symbol + "' before '.'");
        }
    }

    Exp *getExpressionTree()
    {
        return _expStack.top();
    }

    string getResult()
    {
        return getExpressionTree()->getResult() + ".";
    }

  private:
    FRIEND_TEST(ParserTest, createArgs);
    FRIEND_TEST(ParserTest, ListOfTermsEmpty);
    FRIEND_TEST(ParserTest, listofTermsTwoNumber);
    FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
    FRIEND_TEST(ParserTest, createTerms);

    void createTerms()
    {
        Term *term = createTerm();
        if (term != nullptr)
        {
            _terms.push_back(term);
            while ((_currentToken = _scanner.nextToken()) == ',')
            {
                _terms.push_back(createTerm());
            }
        }
    }

    vector<Term *> _terms;
    vector<Variable *> _variableTemp;
    Scanner _scanner;
    int _currentToken;
    //MatchExp* _root;
    stack<Exp *> _expStack;
};
#endif
