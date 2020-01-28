#include "TrackParameterFull.h"
#include <iostream>
using namespace std;
using namespace pathfinder;

TrackParameterFull::TrackParameterFull(const double p, const double d0, const double w, const double tl, const double z0)
    : TrackParameterXY(p, d0, w), TrackParameterSZ(tl, z0)
{
}

TrackParameterFull::TrackParameterFull(const double p, const double d0, const double w, const double tl, const double z0,
                                       const double perr, const double d0err, const double werr, const double tlerr, const double z0err)

    : TrackParameterXY(p, d0, w, perr, d0err, werr), TrackParameterSZ(tl, z0, tlerr, z0err)
{
}

TrackParameterFull::TrackParameterFull(const TrackParameterXY& tpXY, const TrackParameterSZ& tpSZ)
    : TrackParameterXY(tpXY), TrackParameterSZ(tpSZ)
{
}



TrackParameterFull::TrackParameterFull(const TrackParameterFull& tpF)
    : TrackParameterXY(tpF.getPhi(),
                       tpF.getDZero(),
                       tpF.getOmega(),
                       tpF.getPhiError(),
                       tpF.getDZeroError(),
                       tpF.getOmegaError()),
    TrackParameterSZ(tpF.getTanLambda(),
                     tpF.getZZero(),
                     tpF.getTanLambdaError(),
                     tpF.getZZeroError())
{
    slope = tpF.getSlopeXY();
    slope_err = tpF.getSlopeXYError();
    offset = tpF.getOffsetXY();
    offset_err = tpF.getOffsetXYError();
}


void TrackParameterFull::print() const
{
    cout << "TrackParameterFull: " << endl;
    cout << "Phi: " << phi << " +- " << phi_err << endl;
    cout << "DZero: " << dzero << " +- " << dzero_err << endl;
    cout << "Omega: " << omega << " +- " << omega_err << endl;
    cout << "TanLambda: " << tanlambda << " +- " << tanlambda_err << endl;
    cout << "ZZero: " << zzero << " +- " << zzero_err << endl;
}
