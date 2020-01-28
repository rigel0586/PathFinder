#include "HoughSpacePoint.h"
#include <cmath>

using namespace pathfinder;

HoughSpacePoint::HoughSpacePoint(double _theta, double _d,
                                 HoughSpaceBinning _thetaBinning,
                                 HoughSpaceBinning _dBinning)
    : theta(_theta), d(_d)
{
    thetaBin = (int)ceil(_thetaBinning.getNBins() / (_thetaBinning.getHigh() - _thetaBinning.getLow()) * (_theta - _thetaBinning.getLow()));
    dBin = (int)ceil(_dBinning.getNBins() / (_dBinning.getHigh() - _dBinning.getLow()) * (_d - _dBinning.getLow()));

    index = (thetaBin << 20) | (dBin << 10);
}


HoughSpacePoint::HoughSpacePoint(int _thetabin, int _dbin,
                                 HoughSpaceBinning _thetaBinning,
                                 HoughSpaceBinning _dBinning)
    : thetaBin(_thetabin), dBin(_dbin)
{
    index = (_thetabin << 20) | (_dbin << 10);

    theta = _thetaBinning.getLow() + (double)_thetabin * (_thetaBinning.getHigh() - _thetaBinning.getLow()) / _thetaBinning.getNBins();

    d = _dBinning.getLow() + (double)_dbin * (_dBinning.getHigh() - _dBinning.getLow()) / _dBinning.getNBins();

}

HoughSpacePoint::HoughSpacePoint(int _index,
                                 HoughSpaceBinning _thetaBinning,
                                 HoughSpaceBinning _dBinning)
    : index(_index)
{
    dBin = (_index >> 10) & 1023;
    thetaBin = (_index >> 20);

    theta = _thetaBinning.getLow() + (double)thetaBin * (_thetaBinning.getHigh() - _thetaBinning.getLow()) / _thetaBinning.getNBins();

    d = _dBinning.getLow() + (double)dBin * (_dBinning.getHigh() - _dBinning.getLow()) / _dBinning.getNBins();

}

void HoughSpacePoint::Print()
{
    std::cout << "HoughSpacePoint Information:" << std::endl;
    std::cout << "(theta,d): " << theta << ", " << d << std::endl;
    std::cout << "(thetabin,dbin): " << thetaBin << ", " << dBin << std::endl;
    std::cout << "(index): " << index << std::endl;
}

