#ifndef EXP_H
#define EXP_H

#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

using namespace std;

TEST(Sort, sortByIncreasingPerimeter)
{
    vertex v1 = {1, 4}, v2 = {2, 1}, v3 = {4, 3};

    Rectangle rec(1, 2, 2, 2);
    Circle cir1(1, 2, 2);
    Circle cir2(2, 2, 5);
    Triangle tri(v1, v2, v3);

    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&cir1);
    Shapes.push_back(&cir2);
    Shapes.push_back(&tri);

    Sort sort;
    sort.sortByIncreasingPerimeter(&Shapes);

    list<Shape *>::iterator left = Shapes.begin();
    ASSERT_EQ(&rec, *left);
    left++;
    ASSERT_EQ(&tri, *left);
    left++;
    ASSERT_EQ(&cir1, *left);
    left++;
    ASSERT_EQ(&cir2, *left);
}

TEST(Sort, sortByDecreasingPerimeter)
{
    vertex v1 = {1, 4}, v2 = {2, 1}, v3 = {4, 3};

    Rectangle rec(1, 2, 2, 2);
    Circle cir1(1, 2, 2);
    Circle cir2(2, 2, 5);
    Triangle tri(v1, v2, v3);

    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&cir1);
    Shapes.push_back(&cir2);
    Shapes.push_back(&tri);

    Sort sort;
    sort.sortByDecreasingPerimeter(&Shapes);

    list<Shape *>::iterator left = Shapes.begin();
    ASSERT_EQ(&cir2, *left);
    left++;
    ASSERT_EQ(&cir1, *left);
    left++;
    ASSERT_EQ(&tri, *left);
    left++;
    ASSERT_EQ(&rec, *left);
}

TEST(Sort, sortByIncreasingArea)
{
    vertex v1 = {1, 4}, v2 = {2, 1}, v3 = {4, 3};

    Rectangle rec(1, 2, 5, 2);
    Circle cir1(1, 2, 2);
    Circle cir2(2, 2, 5);
    Triangle tri(v1, v2, v3);

    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&cir1);
    Shapes.push_back(&cir2);
    Shapes.push_back(&tri);

    Sort sort;
    sort.sortByIncreasingArea(&Shapes);

    list<Shape *>::iterator left = Shapes.begin();
    ASSERT_EQ(&tri, *left);
    left++;
    ASSERT_EQ(&rec, *left);
    left++;
    ASSERT_EQ(&cir1, *left);
    left++;
    ASSERT_EQ(&cir2, *left);
}

TEST(Sort, sortByDecreasingArea)
{
    vertex v1 = {1, 4}, v2 = {2, 1}, v3 = {4, 3};

    Rectangle rec(1, 2, 5, 2);
    Circle cir1(1, 2, 2);
    Circle cir2(2, 2, 5);
    Triangle tri(v1, v2, v3);

    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&cir1);
    Shapes.push_back(&cir2);
    Shapes.push_back(&tri);

    Sort sort;
    sort.sortByDecreasingArea(&Shapes);

    list<Shape *>::iterator left = Shapes.begin();
    ASSERT_EQ(&cir2, *left);
    left++;
    ASSERT_EQ(&cir1, *left);
    left++;
    ASSERT_EQ(&rec, *left);
    left++;
    ASSERT_EQ(&tri, *left);
}

TEST(Sort, sortByIncreasingCompactness)
{
    vertex v1 = {1, 4}, v2 = {2, 1}, v3 = {4, 3};

    Rectangle rec(1, 2, 5, 2);
    Circle cir1(1, 2, 2);
    Circle cir2(2, 2, 15);
    Triangle tri(v1, v2, v3);

    list<Shape *> Shapes;
    Shapes.push_back(&rec);
    Shapes.push_back(&cir1);
    Shapes.push_back(&cir2);
    Shapes.push_back(&tri);

    Sort sort;
    sort.sortByIncreasingCompactness(&Shapes);

    list<Shape *>::iterator left = Shapes.begin();
    ASSERT_EQ(&tri, *left);
    left++;
    ASSERT_EQ(&rec, *left);
    left++;
    ASSERT_EQ(&cir1, *left);
    left++;
    ASSERT_EQ(&cir2, *left);
}

#endif
