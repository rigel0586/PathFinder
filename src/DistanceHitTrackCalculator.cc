#include "DistanceHitTrackCalculator.h"
#include "ThetaToPhiConverter.h"
#include <cmath>

using namespace pathfinder;

DistanceHitTrackCalculator::DistanceHitTrackCalculator(basicHit* _hit, TrackParameterXY* _trackparameter)
    : hitX(_hit->getX()), hitY(_hit->getY()),
      phi(_trackparameter->getPhi()), d0(_trackparameter->getDZero()), omega(_trackparameter->getOmega())
{
    if(fabs(omega) > 1e-10)
    {
        CalculateDistanceCircleXY();
    }
    else
    {
        CalculateDistanceStraightLineXY();
    }
}

DistanceHitTrackCalculator::DistanceHitTrackCalculator(basicHit* _hit, HoughMaximum2D* _trackparameter)
    : hitX(_hit->getX()), hitY(_hit->getY()), d0(_trackparameter->getSecond())
{
    ThetaToPhiConverter* thetaPhiConverter = new ThetaToPhiConverter(_trackparameter);
    phi = thetaPhiConverter->getPhi();
    delete thetaPhiConverter;

    CalculateDistanceStraightLineXY();
}

DistanceHitTrackCalculator::DistanceHitTrackCalculator(basicHit* _hit, HoughMaximum3D* _trackparameter)
    : hitX(_hit->getX()), hitY(_hit->getY()), d0(_trackparameter->getSecond()), omega(_trackparameter->getThird())
{
    ThetaToPhiConverter* thetaPhiConverter = new ThetaToPhiConverter(_trackparameter);
    phi = thetaPhiConverter->getPhi();
    delete thetaPhiConverter;

    if(fabs(omega) > 1e-10)
    {
        CalculateDistanceCircleXY();
    }
    else
    {
        CalculateDistanceStraightLineXY();
    }
}

DistanceHitTrackCalculator::DistanceHitTrackCalculator(basicHit* _hit, double _phi, double _d0)
    : hitX(_hit->getX()), hitY(_hit->getY()), phi(_phi), d0(_d0), omega(0.)
{
    CalculateDistanceStraightLineXY();
}

DistanceHitTrackCalculator::DistanceHitTrackCalculator(basicHit* _hit, double _phi, double _d0, double _omega)
    : hitX(_hit->getX()), hitY(_hit->getY()), phi(_phi), d0(_d0), omega(_omega)
{
    if(fabs(omega) > 1e-10)
    {
        CalculateDistanceCircleXY();
    }
    else
    {
        CalculateDistanceStraightLineXY();
    }
}

DistanceHitTrackCalculator::DistanceHitTrackCalculator(candidateHit* _hit, TrackParameterSZ* _trackparameter)
    : hitZ(_hit->getZ()), hitS(_hit->getS()),
      tanl(_trackparameter->getTanLambda()), z0(_trackparameter->getZZero())
{
    CalculateDistanceStraightLineSZ();
}

DistanceHitTrackCalculator::DistanceHitTrackCalculator(candidateHit* _hit, HoughMaximum2D* _trackparameter)
    : hitZ(_hit->getZ()), hitS(_hit->getS()), d0(_trackparameter->getSecond()), omega(0.)
{
    ThetaToPhiConverter* thetaPhiConverter = new ThetaToPhiConverter(_trackparameter);
    phi = thetaPhiConverter->getPhi();
    delete thetaPhiConverter;

    //Note: yes, it has to be CalculateDistanceStraightLineXY. This constructor is called in HoughMap2Dint, which is used for straight lines in xy and sz and these two cases are not handled differently in that class (except of using s,z instead of x,y).
    CalculateDistanceStraightLineXY();
}

DistanceHitTrackCalculator::DistanceHitTrackCalculator(candidateHit* _hit, double _phi, double _d0)
    : hitZ(_hit->getZ()), hitS(_hit->getS()), phi(_phi), d0(_d0), omega(0.)
{
    //Note: yes, it has to be CalculateDistanceStraightLineXY. This constructor is called in HoughMap2Dint, which is used for straight lines in xy and sz and these two cases are not handled differently in that class (except of using s,z instead of x,y).
    CalculateDistanceStraightLineXY();
}

void DistanceHitTrackCalculator::CalculateCircleCenter()
{
    centerX = (1. / omega - d0) * sin(phi);
    centerY = -(1. / omega - d0) * cos(phi);
}

void DistanceHitTrackCalculator::CalculateDistanceStraightLineXY()
{
    distance = fabs(
                   -hitX * sin(phi) +
                   hitY * cos(phi) -
                   d0
               );
}

void DistanceHitTrackCalculator::CalculateDistanceCircleXY()
{
    CalculateCircleCenter();

    double d_p = fabs(
                     sqrt(
                         (hitX - centerX) *
                         (hitX - centerX) +
                         (hitY - centerY) *
                         (hitY - centerY)
                     )
                     - 1. / omega
                 );
    double d_m = fabs(
                     (-1.) * sqrt(
                         (hitX - centerX) *
                         (hitX - centerX) +
                         (hitY - centerY) *
                         (hitY - centerY)
                     )
                     - 1. / omega
                 );
    if(d_p <= d_m) distance = d_p;
    else distance = d_m;

}


void DistanceHitTrackCalculator::CalculateDistanceStraightLineSZ()
{
    distance = fabs(
                   hitZ * cos(atan2(tanl, 1)) -
                   hitS * sin(atan2(tanl, 1)) -
                   z0 * cos(atan2(tanl, 1))
               );
}
