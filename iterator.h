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
    virtual T *currentItem() const = 0;
    virtual bool isDone() const = 0;
};

template <class T>
class NullIterator : public Iterator<T>
{
  public:
    NullIterator(T *n) {}
    void first() {}
    void next() {}
    T *currentItem() const { return nullptr; }
    bool isDone() const { return true; }
};

template <class T>
class StructIterator : public Iterator<T>
{
  public:
    friend class Struct;
    void first() { _index = 0; }

    T *currentItem() const { return _s->args(_index); }
    bool isDone() const { return _index >= _s->arity(); }
    void next() { _index++; }

  private:
    StructIterator(Struct *s) : _index(0), _s(s) {}
    int _index;
    Struct *_s;
};

template <class T>
class ListIterator : public Iterator<T>
{
  public:
    friend class List;
    void first() { _index = 0; }

    T *currentItem() const { return _list->args(_index); }
    bool isDone() const { return _index >= _list->arity(); }
    void next() { _index++; }

  private:
    ListIterator(List *l) : _index(0), _list(l) {}
    int _index;
    List *_list;
};

template <class T>
class BFSIterator : public Iterator<T>
{
  public:
    friend class Struct;
    friend class List;
    void first() { _index = 1; }

    T *currentItem() const { return _terms[_index]; }
    bool isDone() const { return _index >= _terms.size() - 1; }
    void next() { _index++; }

  private:
    BFSIterator(T *term) : _index(0), _term(term) { BFS(); }

    int _index;
    T *_term;
    std::vector<T *> _terms;

    void BFS()
    {
        queue<T *> q;
        q.push(_term);
        while (!q.empty())
        {
            T *n = q.front();
            q.pop();
            _terms.push_back(n);
            for (int i = 0; i < n->arity(); i++)
                q.push(n->args(i));
        }
    }
};

template <class T>
class DFSIterator : public Iterator<T>
{
  public:
    friend class Struct;
    friend class List;
    void first() { _index = 1; }

    T *currentItem() const { return _terms[_index]; }
    bool isDone() const { return _index >= _terms.size() - 1; }
    void next() { _index++; }

  private:
    DFSIterator(T *term) : _index(0), _term(term) { DFS(_term); }

    int _index;
    T *_term;
    std::vector<T *> _terms;

    void DFS(T *term)
    {
        _terms.push_back(term);
        for (int i = 0; i < term->arity(); i++)
            DFS(term->args(i));
    }
};

#endif