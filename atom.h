#ifndef ATOM_H
#define ATOM_H

#include "term.h"
#include <string>

template <class T>
class Iterator;

class Atom : public Term
{
  public:
    Atom(string s) : Term(s) {}
    Iterator<Term *> *createIterator();
};

#endif
