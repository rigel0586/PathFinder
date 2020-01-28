#include "basicHit.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;
using namespace pathfinder;

basicHit::basicHit(double X, double Y, double Z, const std::vector<double>& covMatrix, void* hitAddress)
    :  x(X), y(Y), z(Z), covarianceMatrix(covMatrix), initialHit(hitAddress), flag(0)
{
    if(covMatrix.size() != 5)
        throw invalid_argument("[basicHit::constructor]:: Invalid size of the covariance matrix.");
}



basicHit::basicHit(const vector<double>& hitPositions, const std::vector<double>& covMatrix, void* hitAddress) :  initialHit(NULL) , flag(0)
{
    if(hitPositions.size() != 3)
        throw invalid_argument("[basicHit::constructor]:: Invalid length of the initial hit vector! (Must be 3D).");

    basicHit(hitPositions.at(0), hitPositions.at(1), hitPositions.at(2), covMatrix, hitAddress);
}



basicHit::basicHit(const vector<double>& hitPositions, void* hitAddress) :  initialHit(NULL), flag(0)
{
    if(hitPositions.size() != 3 && covarianceMatrix.size() != 0)
        throw invalid_argument("[basicHit::constructor]:: Invalid length of the initial hit position vector.");
    basicHit(hitPositions.at(0), hitPositions.at(1), hitPositions.at(2), hitAddress);
}



basicHit::basicHit(double X, double Y, double Z, void* hitAddress)
    :  x(X), y(Y), z(Z), initialHit(hitAddress), flag(0)
{
}



basicHit::basicHit(const basicHit& bh)
    : x(bh.getX()), y(bh.getY()), z(bh.getZ()), covarianceMatrix(bh.getCovariance()), initialHit(bh.getInitialHit()), flag(bh.getFlag())
{
}



void basicHit::print() const
{
    cout << "[basicHit]::[x,y,z]=[" << x << "," << y << "," << z << "]" << endl;
    if(covarianceMatrix.size() > 0)
    {
        cout << "[basicHit]::[cov]=[";
        for(vector<double>::const_iterator it = covarianceMatrix.begin(); it < covarianceMatrix.end(); ++it)
            cout << *it << ",";
        cout << "]" << endl;
    }
    cout << "[basicHit]::[flag] = " << flag << endl;
}



bool basicHit::operator==(basicHit const hit) const
{
    if(abs(hit.getX() - x) < 0.001
            &&  abs(hit.getY() - y) < 0.001
            && abs(hit.getZ() - z) < 0.001)
        return true;
    else
        return false;
}
