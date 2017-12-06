#include "atom.h"
#include "iterator.h"

Iterator<Term *> *Atom::createIterator()
{
    return new NullIterator(this);
}