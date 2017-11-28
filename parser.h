#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser
{
  public:
    Parser(Scanner scanner) : _scanner(scanner), _terms() {}

    Term *createTerm()
    {
        int token = _scanner.nextToken();
        _currentToken = token;
        if (token == VAR)
            return uniqueTerm(new Variable(symtable[_scanner.tokenValue()].first));
        else if (token == NUMBER)
            return new Number(_scanner.tokenValue());
        else if (token == ATOM || token == ATOMSC)
        {
            Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
            if (_scanner.currentChar() == '(')
                return structure();
            else
                return atom;
        }
        else if (token == '[')
            return list();
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
            throw string("unexpected token");
    }

    Term *list()
    {
        int startIndexOfListArgs = _terms.size();
        createTerms();
        if (_currentToken == ']')
        {
            vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
            _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
            return new List(args);
        }
        else
            throw string("unexpected token");
    }

    vector<Term *> &getTerms() { return _terms; }

    void matchings()
    {
        Term *term = createTerm();
        Node *left, *right, *root;
        if (term != nullptr)
        {
            _terms.push_back(term);
            _currentToken = _scanner.nextToken();
            while ((_currentToken == ';' || _currentToken == '=' || _currentToken == ','))
            {
                if (_currentToken == '=')
                {
                    left = new Node(TERM, _terms.back(), nullptr, nullptr);
                    _terms.push_back(createTerm());
                    right = new Node(TERM, _terms.back(), nullptr, nullptr);
                    root = new Node(EQUALITY, nullptr, left, right);
                    _tree = root;
                }
                else if (_currentToken == ',')
                {
                    left = _tree;
                    matchings();
                    right = _tree;
                    root = new Node(COMMA, nullptr, left, right);
                    _tree = root;
                }
                else if (_currentToken == ';')
                {
                    _termTable.clear();
                    left = _tree;
                    matchings();
                    right = _tree;
                    root = new Node(SEMICOLON, nullptr, left, right);
                    _tree = root;
                }
                _currentToken = _scanner.nextToken();
            }
        }
    }

    Node *expressionTree() { return _tree; }

  private:
    FRIEND_TEST(ParserTest, createArgs);
    FRIEND_TEST(ParserTest, ListOfTermsEmpty);
    FRIEND_TEST(ParserTest, listofTermsTwoNumber);
    FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

    void createTerms()
    {
        Term *term = createTerm();
        if (term != nullptr)
        {
            _terms.push_back(term);
            while ((_currentToken = _scanner.nextToken()) == ',')
                _terms.push_back(createTerm());
        }
    }

    Term *uniqueTerm(Term *term)
    {
        for (int i = 0; i < _termTable.size(); i++)
        {
            if (_termTable[i]->symbol() == term->symbol())
                return _termTable[i];
        }
        _termTable.push_back(term);
        return term;
    }

    vector<Term *> _terms;
    vector<Term *> _termTable;
    Scanner _scanner;
    int _currentToken;
    Node *_tree;
};
#endif