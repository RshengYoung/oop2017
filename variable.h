#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
using std::string;

class Atom;
class Number;

class Variable
{
  public:
    Variable(string);
    string value();
    string symbol();
    
    void setValue(string value);

    bool assignable();
    void setAssignable(bool flg);

    bool match(Number num);
    bool match(Atom atom);

  private:
    string const _symbol;
    string _value;
    bool _assignable = true;
};

#endif