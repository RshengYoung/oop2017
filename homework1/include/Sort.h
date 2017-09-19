#include <list>
#include "Shapes.h"

using namespace std;

class Sort
{

  public:
    static void sortByIncreasingPerimeter(std::list<Shape *> *shapeList)
    {
        list<Shape *>::iterator left = shapeList->begin();
        list<Shape *>::iterator right = shapeList->end();
        right--;

        list<Shape *>::iterator shift;
        Shape *temp;

        while (left != right)
        {
            for (list<Shape *>::iterator i = left; i != right; ++i)
            {
                list<Shape *>::iterator next = i;
                next++;
                if ((*i)->perimeter() > (*next)->perimeter())
                {
                    temp = *i;
                    *i = *next;
                    *next = temp;
                    shift = i;
                }
            }
            right = shift;
            for (list<Shape *>::iterator i = right; i != left; i--)
            {
                list<Shape *>::iterator last = i;
                last--;
                if ((*i)->perimeter() < (*last)->perimeter())
                {
                    temp = *i;
                    *i = *last;
                    *last = temp;
                    shift = i;
                }
            }
            left = shift;
        }

        // for (list<Shape *>::iterator i = shapeList->begin(); i != shapeList->end(); i++)
        // {
        //     cout << (*i)->perimeter() << endl;
        // }
    }

  public:
    static void sortByDecreasingPerimeter(std::list<Shape *> *shapeList)
    {
        list<Shape *>::iterator left = shapeList->begin();
        list<Shape *>::iterator right = shapeList->end();
        right--;

        list<Shape *>::iterator shift;
        Shape *temp;

        while (left != right)
        {
            for (list<Shape *>::iterator i = left; i != right; ++i)
            {
                list<Shape *>::iterator next = i;
                next++;
                if ((*i)->perimeter() < (*next)->perimeter())
                {
                    temp = *i;
                    *i = *next;
                    *next = temp;
                    shift = i;
                }
            }
            right = shift;
            for (list<Shape *>::iterator i = right; i != left; i--)
            {
                list<Shape *>::iterator last = i;
                last--;
                if ((*i)->perimeter() > (*last)->perimeter())
                {
                    temp = *i;
                    *i = *last;
                    *last = temp;
                    shift = i;
                }
            }
            left = shift;
        }
    }

  public:
    static void sortByIncreasingArea(std::list<Shape *> *shapeList) {
        list<Shape *>::iterator left = shapeList->begin();
        list<Shape *>::iterator right = shapeList->end();
        right--;

        list<Shape *>::iterator shift;
        Shape *temp;

        while (left != right)
        {
            for (list<Shape *>::iterator i = left; i != right; ++i)
            {
                list<Shape *>::iterator next = i;
                next++;
                if ((*i)->area() > (*next)->area())
                {
                    temp = *i;
                    *i = *next;
                    *next = temp;
                    shift = i;
                }
            }
            right = shift;
            for (list<Shape *>::iterator i = right; i != left; i--)
            {
                list<Shape *>::iterator last = i;
                last--;
                if ((*i)->area() < (*last)->area())
                {
                    temp = *i;
                    *i = *last;
                    *last = temp;
                    shift = i;
                }
            }
            left = shift;
        }
    }

  public:
    static void sortByDecreasingArea(std::list<Shape *> *shapeList) {
        list<Shape *>::iterator left = shapeList->begin();
        list<Shape *>::iterator right = shapeList->end();
        right--;

        list<Shape *>::iterator shift;
        Shape *temp;

        while (left != right)
        {
            for (list<Shape *>::iterator i = left; i != right; ++i)
            {
                list<Shape *>::iterator next = i;
                next++;
                if ((*i)->area() < (*next)->area())
                {
                    temp = *i;
                    *i = *next;
                    *next = temp;
                    shift = i;
                }
            }
            right = shift;
            for (list<Shape *>::iterator i = right; i != left; i--)
            {
                list<Shape *>::iterator last = i;
                last--;
                if ((*i)->area() > (*last)->area())
                {
                    temp = *i;
                    *i = *last;
                    *last = temp;
                    shift = i;
                }
            }
            left = shift;
        }
    }

  public:
    static void sortByIncreasingCompactness(std::list<Shape *> *shapeList) {
        list<Shape *>::iterator left = shapeList->begin();
        list<Shape *>::iterator right = shapeList->end();
        right--;

        list<Shape *>::iterator shift;
        Shape *temp;

        while (left != right)
        {
            for (list<Shape *>::iterator i = left; i != right; ++i)
            {
                list<Shape *>::iterator next = i;
                next++;
                if ((*i)->compactness() > (*next)->compactness())
                {
                    temp = *i;
                    *i = *next;
                    *next = temp;
                    shift = i;
                }
            }
            right = shift;
            for (list<Shape *>::iterator i = right; i != left; i--)
            {
                list<Shape *>::iterator last = i;
                last--;
                if ((*i)->compactness() < (*last)->compactness())
                {
                    temp = *i;
                    *i = *last;
                    *last = temp;
                    shift = i;
                }
            }
            left = shift;
        }
    }
};
