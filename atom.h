#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
#include "variable.h"

using std::string;
class Atom : public Term {
public:
  Atom(string s);
  string symbol() const;
  string value() const;
  bool match(Term &term);
  bool match(Variable &var);

  string _symbol;
};

#endif
