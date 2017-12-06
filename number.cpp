#include "number.h"
#include "iterator.h"

Iterator<Term *> *Number::createIterator()
{
    return new NullIterator(this);
}