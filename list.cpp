#include "list.h"
#include "iterator.h"

Iterator<Term *> *List::createIterator()
{
    return new ListIterator(this);
}
Iterator<Term *> *List::createBFSIterator()
{
    return new BFSIterator(this);
}
Iterator<Term *> *List::createDFSIterator()
{
    return new DFSIterator(this);
}