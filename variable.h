#ifndef VARIABLE_H
#define VARIABLE_H

#include "atom.h"
#include "list.h"
#include <string>
#include <typeinfo>

using std::string;

class Variable : public Term
{
  public:
    Variable(string s) : Term(s), _inst(0) {}
    string value() const
    {
        if (_inst)
            return _inst->value();
        else
            return Term::value();
    }

    bool match(Term &term)
    {
        if (typeid(term) == typeid(List))
        {
            List *p = dynamic_cast<List *>(&term);
            if (p->inList(*this))
                return false;
        }

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
