#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <vector>

using std::vector;
using std::string;

class List : public Term
{
  public:
    string symbol() const
    {
        if (_elements.empty())
            return "[]";
        string ret = "[";
        vector<Term *>::const_iterator it = _elements.begin();
        for (; it != _elements.end() - 1; ++it)
            ret += (*it)->symbol() + ", ";
        return ret + (*it)->symbol() + "]";
    }

    string value() const
    {
        if (_elements.empty())
            return "[]";
        string ret = "[";
        vector<Term *>::const_iterator it = _elements.begin();
        for (; it != _elements.end() - 1; ++it)
            ret += (*it)->value() + ", ";
        return ret + (*it)->value() + "]";
    }

    bool match(Term &term)
    {
        List *p = dynamic_cast<List *>(&term);
        if (p)
        {
            if (_elements.size() != p->size())
                return false;
            if (_elements.empty())
                return true;
            if (head()->match(*(p->head())))
                return tail()->match(*(p->tail()));
            else
                return false;
        }
        else
            return term.match(*this);
    }

    List() : _elements() {}
    List(vector<Term *> const &elements) : _elements(elements) {}
    Term *head() const
    {
        if (_elements.empty())
            throw string("Accessing head in an empty list");
        return _elements.front();
    }

    List *tail() const
    {
        if (_elements.empty())
            throw string("Accessing tail in an empty list");
        vector<Term *> vector;
        vector.assign(++_elements.begin(), _elements.end());
        List *ptr = new List(vector);
        return ptr;
    }

    bool inList(Term &term) const
    {
        vector<Term *>::const_iterator it = _elements.begin();
        for (; it != _elements.end() - 1; ++it)
        {
            if (*it == &term)
                return true;
        }
        return false;
    }

    bool isEmpty() const { return _elements.empty(); }
    int size() const { return _elements.size(); }

  private:
    vector<Term *> _elements;
};

#endif