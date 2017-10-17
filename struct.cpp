#include "term.h"
#include "struct.h"
#include <vector>
#include <string>

using std::string;

Struct::Struct(Atom name, std::vector<Term *> args) : _name(name), _args(args) {}

Term* Struct::args(int index) const { return _args[index]; }

Atom Struct::name() const { return _name; }

string Struct::symbol() const {
    string ret = _name.symbol() + "(";
    for (int i = 0; i < _args.size() - 1; i++)
        ret += _args[i]->symbol() + ", ";
    ret += _args[_args.size() - 1]->symbol() + ")";
    return ret;
}

string Struct::value() const {
    string s = name().value() + "(" + _args[0]->value();
    for (auto i = _args.begin() + 1; i != _args.end(); i++)
        s += ", " + (*i)->value();
    s += ")";
    return s;
}

bool Struct::match(Term &term) {
    Struct *ps = dynamic_cast<Struct *>(&term);
    if (ps)
    {
        if (!_name.match(ps->_name))
            return false;
        if (_args.size() != ps->_args.size())
            return false;
        for (int i = 0; i < _args.size(); i++)
            if (_args[i]->symbol() != ps->_args[i]->symbol())
                return false;
        return true;
    }
    return false;
}