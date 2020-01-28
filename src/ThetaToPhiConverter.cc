#include "ThetaToPhiConverter.h"
#include <cmath>

using namespace pathfinder;

ThetaToPhiConverter::ThetaToPhiConverter(double _theta, double _d0) : theta(_theta), d0(_d0)
{
    CalculatePhi();
}

ThetaToPhiConverter::ThetaToPhiConverter(HoughMapMaximum* _intersection)
    : theta(_intersection->getFirst()), d0(_intersection->getSecond())
{
    CalculatePhi();
}

/*
ThetaToPhiConverter::ThetaToPhiConverter(HoughMaximum2D* _intersection)
  : theta(_intersection->getFirst()), d0(_intersection->getSecond())
{
  CalculatePhi();
}

ThetaToPhiConverter::ThetaToPhiConverter(HoughMaximum3D* _intersection)
  : theta(_intersection->getFirst()), d0(_intersection->getSecond())
{
  CalculatePhi();
}
*/
void ThetaToPhiConverter::CalculatePhi()
{
    if(d0 <= 0.)
    {
        phi = M_PI_2 + theta;//Note: M_PI_2 = pi/2
    }
    else
    {
        phi = -M_PI_2 + theta;
    }
    if(phi < -M_PI)
    {
        phi = 2 * M_PI + phi;
    }
    if(phi > M_PI)
    {
        phi = phi - 2 * M_PI;
    }
}
