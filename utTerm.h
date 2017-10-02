#ifndef UTTERM_H
#define UTTERM_H
#include "number.h"
#include "atom.h"
#include "variable.h"

//test Number.value()
TEST(Number, ctor)
{
    Number num("number", "20");
    ASSERT_EQ("20", num.value());
}
//test Number.symbol()
TEST(Number, symbol)
{
    Number num("number", "25");
    ASSERT_EQ("number", num.symbol());
}
//?- 25=25.
//true.
TEST(Number, matchSuccess)
{
    Number num1("number1", "25");
    Number num2("number2", "25");
    ASSERT_TRUE(num1.match(num2));
}
//?- 25=0.
//false.
TEST(Number, matchFailureDiffValue)
{
    Number num1("number1", "25");
    Number num2("number2", "0");
    ASSERT_FALSE(num1.match(num2));
}
//?- 25=tom.
//false.
TEST(Number, matchFailureDiffConstant)
{
    Number num("number", "25");
    Atom tom("tom");
    ASSERT_FALSE(num.match(tom));
}
//?- 25=X.
//true.
TEST(Number, matchSuccessToVar)
{
    Number num("number", "25");
    Variable X("X");
    ASSERT_TRUE(num.match(X));
}

//?- tom=25.
//false.
TEST(Atom, matchFailureDiffConstant)
{
    Atom tom("tom");
    Number num("number", "25");
    ASSERT_FALSE(tom.match(num));
}

// ?- tom = X.
// X = tom.
TEST(Atom, matchSuccessToVar)
{
    Atom tom("tom");
    Variable X("X");

    tom.match(X);
    ASSERT_EQ("tom", X.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST(Atom, matchSuccessToVarInstantedToDiffConstant)
{
    Variable X("X");
    Atom tom("tom");

    X.match(tom);
    tom.match(X);
    ASSERT_EQ("tom", X.value());
}

// ?- X=jerry, tom=X.
// false.
TEST(Atom, matchFailureToVarInstantedToDiffConstant)
{
   Variable X("X");
   Atom jerry("jerry");
   Atom tom("tom");

   ASSERT_TRUE(X.match(jerry));
   ASSERT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST(Var, matchSuccessToNumber)
{
    Variable X("X");
    Number num("number", "5");

    X.match(num);
    ASSERT_EQ("5", X.value());
}

// ?- X=25, X= 100.
// false.
TEST(Var, matchFailureToTwoDiffNumbers)
{
    Variable X("X");
    Number num1("number1", "25");
    Number num2("number2", "100");

    ASSERT_TRUE(X.match(num1));
    ASSERT_FALSE(X.match(num2));
}

// ?- X=tom, X= 25.
// false.
TEST(Var, matchSuccessToAtomThenFailureToNumber)
{
    Variable X("X");
    Atom tom("tom");
    Number num("number", "25");

    ASSERT_TRUE(X.match(tom));
    ASSERT_FALSE(X.match(num));
}
//?- tom=X, 25=X.
//false.
TEST(Var, matchSuccessToAtomThenFailureToNumber2)
{
    Atom tom("tom");
    Variable X("X");
    Number num("number", "25");

    ASSERT_TRUE(tom.match(X));
    ASSERT_FALSE(num.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom)
{
    Variable X("X");
    Atom tom("tom");

    ASSERT_TRUE(X.match(tom));
    ASSERT_TRUE(X.match(tom));
}
#endif
