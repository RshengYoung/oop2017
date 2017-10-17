#include <string>
#include "atom.h"

using std::string;

Atom::Atom(string s) : _symbol(s) {}
string Atom::symbol() const { return _symbol; }
string Atom::value() const { return _symbol; }

bool Atom::match(Variable &var) {
    return var.match(*this);
}

bool Atom::match(Term& term){
    return this->symbol() == term.symbol();
}