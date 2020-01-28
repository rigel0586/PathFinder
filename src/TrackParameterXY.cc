#include "TrackParameterXY.h"
#include <iostream>

using namespace std;
using namespace pathfinder;


TrackParameterXY::TrackParameterXY(double p, double d0, double w)
    : phi(p), dzero(d0), omega(w), phi_err(0.), dzero_err(0.), omega_err(0.),
      slope(0.), offset(0.), slope_err(0.), offset_err(0.)
{
}

TrackParameterXY::TrackParameterXY(double p, double d0, double w, double perr, double d0err, double werr)
    : phi(p), dzero(d0), omega(w), phi_err(perr), dzero_err(d0err), omega_err(werr),
      slope(0.), offset(0.), slope_err(0.), offset_err(0.)
{
}

TrackParameterXY::TrackParameterXY(const TrackParameterXY &tpxy)
{
    phi = tpxy.getPhi();
    dzero = tpxy.getDZero();
    omega = tpxy.getOmega();
    phi_err = tpxy.getPhiError();
    dzero_err = tpxy.getDZeroError();
    omega_err = tpxy.getOmegaError();

    slope = tpxy.getSlopeXY();
    slope_err = tpxy.getSlopeXYError();
    offset = tpxy.getOffsetXY();
    offset_err = tpxy.getOffsetXYError();
}

void TrackParameterXY::print() const
{
    cout << "TrackParameterXY: " << endl;
    cout << "Phi: " << phi << " +- " << phi_err << endl;
    cout << "DZero: " << dzero << " +- " << dzero_err << endl;
    cout << "Omega: " << omega << " +- " << omega_err << endl;
}
