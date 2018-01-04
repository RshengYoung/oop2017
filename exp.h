#ifndef EXP_H
#define EXP_H

#include "atom.h"

class Exp
{
  public:
    virtual bool evaluate() = 0;
    virtual string getResult() = 0;
};

class MatchExp : public Exp
{
  public:
    MatchExp(Term *left, Term *right) : _left(left), _right(right) {}

    bool evaluate()
    {
        return _left->match(*_right);
    }

    string getResult()
    {
        if (evaluate())
        {
            if (_left->symbol() != _right->symbol())
            {
                if (_left->getVariable() != nullptr)
                    return _left->symbol() + " = " + _right->value();
                else if (_right->getVariable() != nullptr)
                    return _left->value() + " = " + _right->symbol();
            }
            return "true";
        }
        return "false";
    }

  private:
    Term *_left;
    Term *_right;
};

class ConjExp : public Exp
{
  public:
    ConjExp(Exp *left, Exp *right) : _left(left), _right(right)
    {
    }

    bool evaluate()
    {
        return (_left->evaluate() && _right->evaluate());
    }

    string getResult()
    {
        if (evaluate())
        {
            if (_left->getResult() == "true" && _right->getResult() == "true")
                return "true";
            if (_left->getResult() == _right->getResult())
                return _left->getResult();
            if (_left->getResult().find(_right->getResult()) != string::npos)
                return _left->getResult();
            if (_left->getResult() != _right->getResult() && _left->getResult() == "true")
                return _right->getResult();
            if (_left->getResult() == "true")
                return _right->getResult();
            if (_right->getResult() == "true")
                return _left->getResult();

            string str = _left->getResult() + ", " + _right->getResult();
            return _left->getResult() + ", " + _right->getResult();
        }
        return "false";
    }

  private:
    Exp *_left;
    Exp *_right;
};

class DisjExp : public Exp
{
  public:
    DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

    bool evaluate()
    {
        return (_left->evaluate() || _right->evaluate());
    }

    string getResult()
    {
        if (_left->getResult() == "false")
            return _right->getResult();
        else if (_right->getResult() == "false")
            return _left->getResult();
        return _left->getResult() + "; " + _right->getResult();
    }

  private:
    Exp *_left;
    Exp *_right;
};
#endif
