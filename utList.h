#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST(List, constructor)
{
    List list;
    ASSERT_EQ("[]", list.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers)
{
    Number number1(8128);
    Number number2(496);
    vector<Term *> v = {&number2, &number1};
    List list(v);
    ASSERT_EQ("[496, 8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms)
{
    Atom terence_tao("terence_tao");
    Atom alan_mathison_turing("alan_mathison_turing");
    vector<Term *> v = {&terence_tao, &alan_mathison_turing};
    List list(v);
    ASSERT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars)
{
    Variable X("X");
    Variable Y("Y");
    vector<Term *> v = {&X, &Y};
    List list(v);
    ASSERT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail)
{
    Atom tom("tome");

    Number number(496);
    Variable X("X");
    Atom terence_tao("terence_tao");

    vector<Term *> v = {&number, &X, &terence_tao};
    List list(v);

    ASSERT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail)
{
    Number num(8128);

    Number num1(496);
    Variable X("X");
    Atom terence_tao("terence_tao");

    vector<Term *> v = {&num1, &X, &terence_tao};
    List list(v);

    ASSERT_FALSE(num.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail)
{
    Atom name("s");

    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");

    vector<Term *> v1 = {&X};
    vector<Term *> v2 = {&num, &X, &terence_tao};

    Struct s(name, v1);
    List list(v2);

    ASSERT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed)
{
    Variable Y("Y");

    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");

    vector<Term *> v = {&num, &X, &terence_tao};
    List list(v);

    ASSERT_TRUE(Y.match(list));
    ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail)
{
    Variable X("X");

    Number num(496);
    Atom terence_tao("terence_tao");

    vector<Term *> v = {&num, &X, &terence_tao};
    List list(v);

    ASSERT_FALSE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed)
{
    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");

    vector<Term *> v = {&num, &X, &terence_tao};
    List list1(v), list2(v);

    ASSERT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed)
{
    Number num(496);
    Variable X("X"), Y("Y");
    Atom terence_tao("terence_tao");

    vector<Term *> v1 = {&num, &X, &terence_tao};
    vector<Term *> v2 = {&num, &Y, &terence_tao};

    List list1(v1), list2(v2);

    ASSERT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed)
{
    Number num1(496), num2(8128);
    Variable X("X");
    Atom terence_tao("terence_tao");

    vector<Term *> v1 = {&num1, &X, &terence_tao};
    vector<Term *> v2 = {&num1, &num2, &terence_tao};

    List list1(v1), list2(v2);

    ASSERT_TRUE(list1.match(list2));
    ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed)
{
    Number num(496);
    Variable X("X"), Y("Y");
    Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");

    vector<Term *> v1 = {&num, &X, &terence_tao};
    vector<Term *> v2 = {&num, &alan_mathison_turing, &terence_tao};

    List list1(v1), list2(v2);

    ASSERT_TRUE(Y.match(list1));
    ASSERT_TRUE(X.match(alan_mathison_turing));
    ASSERT_TRUE(Y.match(list2));
    ASSERT_EQ("alan_mathison_turing", X.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1)
{
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);

    EXPECT_EQ(string("first"), l.head()->symbol());
    EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2)
{
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);

    EXPECT_EQ(string("second"), l.tail()->head()->value());
    EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3)
{
    Atom first("first"), second("second"), third("third");

    vector<Term *> fv = {&first};
    List fl(fv);
    vector<Term *> v = {&fl, &second, &third};
    List list(v);

    ASSERT_EQ(string("[first]"), list.head()->symbol());
    ASSERT_EQ(string("[second, third]"), list.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4)
{
    Atom first("first"), second("second"), third("third");

    vector<Term *> v = {&first, &second, &third};
    List list(v);

    ASSERT_EQ(string("third"), list.tail()->tail()->head()->value());
    ASSERT_EQ("[]", list.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST(List, emptyExecptionOfHead)
{
    List list;
    try
    {
        list.head();
    }
    catch (string error)
    {
        ASSERT_EQ(string("Accessing head in an empty list"), error);
    }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST(List, emptyExecptionOfTail)
{
    List list;
    try
    {
        list.tail();
    }
    catch (string error)
    {
        ASSERT_EQ(string("Accessing tail in an empty list"), error);
    }
}

#endif
