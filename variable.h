#ifndef VARIABLE_H
#define VARIABLE_H

#include "atom.h"
#include "list.h"
#include <string>
#include <typeinfo>

using std::string;

template <class T>
class Iterator;

class Variable : public Term
{
  public:
    Variable(string s) : Term(s), _inst(0) {}
    Iterator<Term *> *createIterator();

    string value() const
    {
        if (_inst)
            return _inst->value();
        else
            return Term::value();
    }

    bool match(Term &term)
    {
        if (this == &term)
            return true;
        if (!_inst)
        {
            _inst = &term;
            return true;
        }
        return _inst->match(term);
    }

  private:
    Term *_inst;
};

#endif
