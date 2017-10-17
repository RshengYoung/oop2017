#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "term.h"

using std::string;

class Variable : public Term {
  public:
    Variable(string s);
    string symbol() const;
    string value() const;
    bool match(Term &term);

    string *_value = new string;
    bool _assignable = true;

    string const _symbol;
};

#endif
