#include "TrackParameterSZ.h"
#include <iostream>

using namespace std;
using namespace pathfinder;


TrackParameterSZ::TrackParameterSZ(double tl, double z0)
    : tanlambda(tl), zzero(z0), tanlambda_err(0.), zzero_err(0.)
{
}

TrackParameterSZ::TrackParameterSZ(double tl, double z0, double tlerr, double z0err)
    : tanlambda(tl), zzero(z0), tanlambda_err(tlerr), zzero_err(z0err)
{
}

TrackParameterSZ::TrackParameterSZ(const TrackParameterSZ &tpsz)
{
    tanlambda = tpsz.getTanLambda();
    zzero = tpsz.getZZero();
    tanlambda_err = tpsz.getTanLambdaError();
    zzero_err = tpsz.getZZeroError();
}

void TrackParameterSZ::print() const
{
    cout << "TrackParameterSZ: " << endl;
    cout << "TanLambda: " << tanlambda << " +- " << tanlambda_err << endl;
    cout << "ZZero: " << zzero << " +- " << zzero_err << endl;
}
