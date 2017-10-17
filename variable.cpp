#include "variable.h"
#include "atom.h"
#include "term.h"
#include "number.h"
#include <string>

#include <iostream>

using std::string;

Variable::Variable(string s): _symbol(s) {
    *_value = s;
}
string Variable::symbol() const { return _symbol; }
string Variable::value() const { return *_value; }

bool Variable::match(Term &term) {
    bool ret = _assignable;
    if (_assignable) {
        Variable *var = dynamic_cast<Variable *>(&term);
        // Atom *atom = dynamic_cast<Atom *>(&term);
        if (var) {
            if (var->_assignable)
                var->_value = _value;
            else
                _value = var->_value;
        // } else if (atom) {
        //     _value = &(atom->_symbol);
        //     _assignable = false;
        } else {
            *_value = term.symbol();
            _assignable = false;
        }        
    }
    return ret;
}