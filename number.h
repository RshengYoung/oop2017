#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include "iterator.h"

template <class T>
class Iterator;

class Number : public Term
{
  public:
    Number(double db) : Term(db) {}
    Iterator<Term *> *createIterator();
};

#endif