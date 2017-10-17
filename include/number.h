#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"

using std::string;
class Number : public Term {
  public:
    Number(double num);
    string symbol() const;
    double value();

  private:
    string _symbol;
    double _value;
};

#endif
