#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"

#include <vector>
#include <string>

using std::string;

template <class T>
class Iterator;

class Struct : public Term
{
  public:
    Struct(Atom name, std::vector<Term *> args) : _name(name) { _args = args; }
    Atom &name() { return _name; }

    Term *args(int index) { return _args[index]; }
    int arity() { return _args.size(); }

    Iterator<Term> *createIterator();
    Iterator<Term> *createBFSIterator();
    Iterator<Term> *createDFSIterator();

    string symbol() const
    {
        string ret = _name.symbol() + "(";
        std::vector<Term *>::const_iterator it = _args.begin();
        if (_args.size() == 0)
            return ret + ")";
        for (; it != _args.end() - 1; ++it)
            ret += (*it)->symbol() + ", ";
        ret += (*it)->symbol() + ")";
        return ret;
    }

    string value() const
    {
        string ret = _name.symbol() + "(";
        std::vector<Term *>::const_iterator it = _args.begin();
        for (; it != _args.end() - 1; ++it)
            ret += (*it)->value() + ", ";
        ret += (*it)->value() + ")";
        return ret;
    }

  private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif
