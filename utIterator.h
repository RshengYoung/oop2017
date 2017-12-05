#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "term.h"
#include "number.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"

// //  s(1, t(X, 2), Y)
// TEST(iterator, first)
// {
//     Number one(1), two(2);
//     Variable X("X"), Y("Y");
//     Struct t(Atom("t"), {&X, &two});
//     Struct s(Atom("s"), {&one, &t, &Y});

//     Iterator<Term> *it = s.createIterator();
//     it->first();
//     ASSERT_EQ("1", it->currentItem()->symbol());
//     ASSERT_FALSE(it->isDone());
//     it->next();
//     ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
//     ASSERT_FALSE(it->isDone());
//     it->next();
//     ASSERT_EQ("Y", it->currentItem()->symbol());
//     it->next();
//     ASSERT_TRUE(it->isDone());
// }

// //  [1, t(X, 2), Y]
// TEST(iterator, firstList)
// {
//     Number one(1), two(2);
//     Variable X("X"), Y("Y");
//     Struct t(Atom("t"), {&X, &two});
//     List l({&one, &t, &Y});

//     Iterator<Term> *it = l.createIterator();
//     it->first();
//     ASSERT_EQ("1", it->currentItem()->symbol());
//     ASSERT_FALSE(it->isDone());
//     it->next();
//     ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
//     ASSERT_FALSE(it->isDone());
//     it->next();
//     ASSERT_EQ("Y", it->currentItem()->symbol());
//     it->next();
//     ASSERT_TRUE(it->isDone());
// }

//  s(1, t(X, 2), Y)
TEST(iterator, structBFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});

    Iterator<Term> *it = s.createBFSIterator();
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

    Iterator<Term> *it = list2.createBFSIterator();
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

//  s(X, [2, Y], 1)
TEST(iterator, structlistBFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    List list({&two, &Y});
    Struct s(Atom("s"), {&X, &list, &one});

    Iterator<Term> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[2, Y]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

//  [s(1, X), [2, Y], 1]
TEST(iterator, liststructBFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    Struct s(Atom("s"), {&one, &X});
    List list1({&two, &Y});
    List list2({&s, &list1, &one});

    Iterator<Term> *it = list2.createBFSIterator();
    it->first();
    ASSERT_EQ("s(1, X)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[2, Y]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
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

//  s(1, t(X, 2), Y)
TEST(iterator, structDFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});

    Iterator<Term> *it = s.createDFSIterator();
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

    Iterator<Term> *it = list2.createDFSIterator();
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

//  s(X, [2, Y], 1)
TEST(iterator, structlistDFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    List list({&two, &Y});
    Struct s(Atom("s"), {&X, &list, &one});

    Iterator<Term> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[2, Y]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

//  [s(1, X), [2, Y], 1]
TEST(iterator, liststructDFS)
{
    Number one(1), two(2);
    Variable X("X"), Y("Y");
    Struct s(Atom("s"), {&one, &X});
    List list1({&two, &Y});
    List list2({&s, &list1, &one});

    Iterator<Term> *it = list2.createDFSIterator();
    it->first();
    ASSERT_EQ("s(1, X)", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("[2, Y]", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

#endif