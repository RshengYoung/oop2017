#include "variable.h"
#include "atom.h"
#include "number.h"

#include <string>
using std::string;
Variable::Variable(string symbol) : _symbol(symbol) {}
string Variable::value() { return _value; }
string Variable::symbol() { return _symbol; }

void Variable::setValue(string value) { _value = value; }

bool Variable::assignable() { return _assignable; }
void Variable::setAssignable(bool flg) { _assignable = flg; }

bool Variable::match(Number num)
{
    if (_value == num.value())
        return true;
    else
    {
        bool ret = _assignable;
        if (_assignable)
        {
            _value = num.value();
            _assignable = false;
        }
        return ret;
    }
}

bool Variable::match(Atom atom)
{
    if (_value == atom.symbol())
        return true;
    else
    {
        bool ret = _assignable;
        if (_assignable)
        {
            _value = atom.symbol();
            _assignable = false;
        }
        return ret;
    }
}