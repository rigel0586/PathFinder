#include "HoughMaximum3D.h"
#include <iostream>

using namespace std;
using namespace pathfinder;

HoughMaximum3D::HoughMaximum3D(double t, double d, double o)
    : HoughMaximum2D(t, d) , _third(o)
{
}

void HoughMaximum3D::print() const
{
    cout << " HoughMaximum3D::print: " << endl;
    cout << " " << _first << " " << _second << " " << _third << endl;
}
