#ifndef ITERATOR_H
#define ITERATOR_H

#include "term.h"
#include "struct.h"
#include "list.h"
#include <queue>

using std::queue;

template <class T>
class Iterator
{
  public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual T currentItem() const = 0;
    virtual bool isDone() const = 0;
};

class NullIterator : public Iterator<Term *>
{
  public:
    NullIterator(Term *n) {}
    void first() {}
    void next() {}
    Term *currentItem() const { return nullptr; }
    bool isDone() const { return true; }
};

class StructIterator : public Iterator<Term *>
{
  public:
    friend class Struct;
    void first() { _index = 0; }

    Term *currentItem() const { return _s->args(_index); }
    bool isDone() const { return _index >= _s->arity(); }
    void next() { _index++; }

  private:
    StructIterator(Struct *s) : _index(0), _s(s) {}
    int _index;
    Struct *_s;
};

class ListIterator : public Iterator<Term *>
{
  public:
    friend class List;
    void first() { _index = 0; }

    Term *currentItem() const { return _list->args(_index); }
    bool isDone() const { return _index >= _list->arity(); }
    void next() { _index++; }

  private:
    ListIterator(List *l) : _index(0), _list(l) {}
    int _index;
    List *_list;
};

class BFSIterator : public Iterator<Term *>
{
  public:
    friend class Struct;
    friend class List;
    void first() { _index = 1; }

    Term *currentItem() const { return _terms[_index]; }
    bool isDone() const { return _index >= _terms.size(); }
    void next() { _index++; }

  private:
    BFSIterator(Term *term) : _index(0), _term(term) { BFS(); }

    int _index;
    Term *_term;
    std::vector<Term *> _terms;

    void BFS()
    {
        queue<Term *> q;
        q.push(_term);
        while (!q.empty())
        {
            Term *n = q.front();
            q.pop();
            _terms.push_back(n);
            for (int i = 0; i < n->arity(); i++)
                q.push(n->args(i));
        }
    }
};

class DFSIterator : public Iterator<Term *>
{
  public:
    friend class Struct;
    friend class List;
    void first() { _index = 1; }

    Term *currentItem() const { return _terms[_index]; }
    bool isDone() const { return _index >= _terms.size(); }
    void next() { _index++; }

  private:
    DFSIterator(Term *term) : _index(0), _term(term) { DFS(_term); }

    int _index;
    Term *_term;
    std::vector<Term *> _terms;

    void DFS(Term *term)
    {
        _terms.push_back(term);
        for (int i = 0; i < term->arity(); i++)
            DFS(term->args(i));
    }
};

#endif