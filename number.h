#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
#include "variable.h"

using std::string;

class Number
{

public:
  Number(string s) : _symbol(s){};
  Number(int v) : _value(v){};

  int value() { return _value; }
  string symbol() { return _symbol; }

  bool match(Number num)
  {
    if (_value == num.value())
      return true;
    else
      return false;
  }

  bool match(Atom atom)
  {
    return false;
  }

  bool match(Variable var)
  {
    if (_symbol == var._symbol)
      return true;
    else
    {
      bool ret = _assignable;
      if (_assignable)
      {
        _symbol = var._symbol;
        _assignable = false;
      }
      return ret;
    }
  }

private:
  int _value;
  string _symbol;
  bool _assignable = true;
};

#endif