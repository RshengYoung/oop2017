#ifndef NUMBER_H
#define NUMBER_H
#include <string>
using std::string;

class Atom;
class Variable;

class Number
{

public:
  Number(string, string);
  Number(int value);
  string value();
  string symbol();

  bool match(Number num);
  bool match(Atom atom);
  bool match(Variable &var);

private:
  string const _symbol;
  string const _value;


};

#endif