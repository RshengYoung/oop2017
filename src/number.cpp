#include <string>
#include "../include/number.h"

using std::string;

Number::Number(double num) {
    _symbol = std::to_string(num);

    for (int i = _symbol.length() - 1; i > 0; i--)
    {
        if (_symbol[i] == '0' || _symbol[i] == '.')
            _symbol.pop_back();
        else
            break;
    }
    _value = num;
}
string Number::symbol() const { return _symbol; }
double Number::value() { return _value; }