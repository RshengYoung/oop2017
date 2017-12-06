#include "variable.h"
#include "iterator.h"

Iterator<Term *> *Variable::createIterator()
{
    return new NullIterator(this);
}