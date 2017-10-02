#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

class Variable;
class Number;

class Atom {
public:
  Atom(string);
  string symbol();
  bool match(Variable &var);
  bool match(Number num);
  bool match(Atom atom);

private:
  string const _symbol;
};

#endif
