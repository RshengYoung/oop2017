#include "number.h"
#include "variable.h"
#include "atom.h"

#include <string>
using std::string;

Number::Number(string symbol, string value) : _symbol(symbol), _value(value) {}
Number::Number(int value) : _value(std::to_string(value)) {}

string Number::value() { return _value; }
string Number::symbol() { return _symbol; }

bool Number::match(Number num) { return _value == num.value(); }
bool Number::match(Atom atom) { return false; }
bool Number::match(Variable &var)
{
    if (_value == var.value())
        return true;
    else
    {
        bool ret = var.assignable();
        if (var.assignable()) {
            var.setValue(_value);
            var.setAssignable(false);
        }
        return ret;
    }
}