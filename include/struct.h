#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include "term.h"
#include <vector>
#include <string>

using std::vector;

class Struct : public Term {
  public:
    Struct(Atom name, vector<Term *> args);
    Term *args(int index) const;
    Atom name() const;
    string symbol() const;
    string value() const;

    bool match(Term &term);

  private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif
