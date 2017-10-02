#ifndef UTTERM_H
#define UTTERM_H
#include "number.h"

//test Number.value()
TEST(Number, ctor)
{
    Number num(20);
    ASSERT_EQ(20, num.value());
}
//test Number.symbol()
TEST(Number, symbol)
{
    Number num("number");
    ASSERT_EQ("number", num.symbol());
}
//?- 25=25.
//true.
TEST(Number, matchSuccess)
{
    Number num1(25);
    Number num2(25);
    ASSERT_TRUE(num1.match(num2));
}
//?- 25=0.
//false.
TEST(Number, matchFailureDiffValue)
{
    Number num1(25);
    Number num2(0);
    ASSERT_FALSE(num1.match(num2));
}
//?- 25=tom.
//false.
TEST(Number, matchFailureDiffConstant)
{
    Number num(25);
    Atom tom("tom");
    ASSERT_FALSE(num.match(tom));
}
//?- 25=X.
//true.
TEST(Number, matchSuccessToVar)
{
    Number num(25);
    Variable X("X");
    ASSERT_TRUE(num.match(X));
}

//?- tom=25.
//false.
TEST(Atom, matchFailureDiffConstant)
{
    Atom tom("tom");
    Number num(25);
    ASSERT_FALSE(num.match(tom));
}

// ?- tom = X.
// X = tom.
TEST(Atom, matchSuccessToVar)
{
    Atom tom("tom");
    Variable X("X");
    X.match(tom);

    ASSERT_EQ("tom", X.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST(Atom, matchSuccessToVarInstantedToDiffConstant)
{
    Variable X("X");
    Atom tom("tom");

    X.match(tom);
    X.match(tom);
    ASSERT_EQ("tom", X.value());
}

// ?- X=jerry, tom=X.
// false.
TEST(Atom, matchFailureToVarInstantedToDiffConstant)
{
    Variable X("X");
    Atom tom("tom");
    Atom jerry("jerry");

    X.match(jerry);
    ASSERT_FALSE(X.match(tom));
}

// ?- X = 5.
// X = 5.
TEST(Var, matchSuccessToNumber)
{
    // Variable X("X");
    // Number num(5);
    // num.match(X);

    // ASSERT_EQ(5, X.value());
}

// ?- X=25, X= 100.
// false.
TEST(Var, matchFailureToTwoDiffNumbers)
{
}

// ?- X=tom, X= 25.
// false.
TEST(Var, matchSuccessToAtomThenFailureToNumber)
{
}
//?- tom=X, 25=X.
//false.
TEST(Var, matchSuccessToAtomThenFailureToNumber2)
{
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom)
{
}
#endif
