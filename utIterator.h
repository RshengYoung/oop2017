#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "term.h"
#include "number.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"

TEST(iterator, firstStruct)
{
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});
    Iterator<Term *> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator)
{
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});
    Iterator<Term *> *it = s.createIterator();
    it->first();
    it->next();
    Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

    Iterator<Term *> *it2 = s2->createIterator();
    it2->first();
    ASSERT_EQ("X", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_EQ("2", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList)
{
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), {&X, &two});
    List l({&one, &t, &Y});
    Iterator<Term *> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator)
{
    Number one(1);
    NullIterator nullIterator(&one);
    nullIterator.first();
    ASSERT_TRUE(nullIterator.isDone());
    Iterator<Term *> *it = one.createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, NumberIterator)
{
    Number one(1);
    Iterator<Term *> *it = one.createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, AtomIterator)
{
    Atom tom("tom");
    Iterator<Term *> *it = tom.createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, VarIterator)
{
    Variable X("X");
    Iterator<Term *> *it = X.createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
}

//  s(1, t(X, 2), Y)
TEST(iterator, structBFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});

    Iterator<Term *> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

//  [2, [X, Y], [], 1]
TEST(iterator, listBFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    List list1({&X, &Y}), emptyList;
    List list2({&two, &list1, &emptyList, &one});

    Iterator<Term *> *it = list2.createBFSIterator();
    it->first();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

//  s(1, t(X, 2), Y)
TEST(iterator, structDFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});

    Iterator<Term *> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

//  [2, [X, Y], [], 1]
TEST(iterator, listDFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    List list1({&X, &Y}), emptyList;
    List list2({&two, &list1, &emptyList, &one});

    Iterator<Term *> *it = list2.createDFSIterator();
    it->first();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

#endif