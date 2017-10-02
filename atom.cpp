#include "atom.h"
#include "number.h"
#include "variable.h"

using std::string;

Atom::Atom(string symbol) : _symbol(symbol) {}
string Atom::symbol() { return _symbol; }

bool Atom::match(Number num) { return false; }
bool Atom::match(Variable &var)
{
    if (_symbol == var.value())
        return true;
    else
    {
        bool ret = var.assignable();
        if (var.assignable())
        {
            var.setValue(_symbol);
            var.setAssignable(false);
        }
        return ret;
    }
}