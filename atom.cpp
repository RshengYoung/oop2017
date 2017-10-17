#include <string>
#include "atom.h"

using std::string;

Atom::Atom(string s) : _symbol(s) {}
string Atom::symbol() const { return _symbol; }
string Atom::value() const { return _symbol; }