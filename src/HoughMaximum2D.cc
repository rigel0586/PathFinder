#include "HoughMaximum2D.h"
#include <iostream>

using namespace std;
using namespace pathfinder;

HoughMaximum2D::HoughMaximum2D(double t, double d)
    : _first(t), _second(d)
{
}

void HoughMaximum2D::print() const
{
    cout << " HoughMaximum2D::print:  " << endl;
    cout << " " << _first << " " << _second << endl;
}
