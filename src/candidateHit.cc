#include "candidateHit.h"
#include <iostream>
using namespace std;
using namespace pathfinder;

candidateHit::candidateHit(basicHit b) : basicHit(b), pathLength(0.)
{
}

candidateHit::candidateHit(basicHit b, double S)
    : basicHit(b), pathLength(S)
{
}


void candidateHit::print() const
{
    cout << "[candidateHit]::[x,y,z]=[" << getX() << "," << getY() << "," << getZ() << "]" << endl;
    vector<double> cov = getCovariance();
    cout << "[candidateHit]::[cov]=[";
    for(vector<double>::const_iterator it = cov.begin(); it < cov.end(); ++it)
        cout << *it << ",";
    cout << "]" << endl;
    cout << "[candidateHit]::S=" << pathLength << endl;

    cout << "[candidateHit]::[flag] = " << getFlag() << endl;
}
