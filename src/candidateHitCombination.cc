#include "candidateHitCombination.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace pathfinder;

candidateHitCombination::candidateHitCombination(vector<basicHit> theHits,
                                                 TrackParameterXY tpXY,
                                                 FinderParameter FinderParameter) :
    _basicHits(theHits),  _isHelix(FinderParameter.getIsHelix())
{
    //calculate pca
    _pca = new basicHit(-tpXY.getDZero()*sin(tpXY.getPhi()) , tpXY.getDZero()*cos(tpXY.getPhi()), 0.);

}



candidateHitCombination::~candidateHitCombination()
{
    if(_pca)
        delete _pca;
}


vector<candidateHit> candidateHitCombination::getCombination(TrackParameterXY tpXY)
{

    /*
      0. get pca from xy track parameters (done in constructor)
      1. use pca in xy plane to calculate s for all hits
      2. check if it is a curler and if so correct s
      3. return this
    */


    //1.
    vector<candidateHit> tempCandidates;
    for(vector<basicHit>::const_iterator aHit = _basicHits.begin(); aHit < _basicHits.end(); ++aHit)
    {
        candidateHit cand(*aHit);
        //cout<<"calculate s"<<endl;
        cand.setS(calculateS(*aHit, *_pca, tpXY));

        tempCandidates.push_back(cand);
    }


    //3.
    return tempCandidates;
}



void candidateHitCombination::print()
{
    cout << "[candidateHitCombination]::info - Basis vector has " << _basicHits.size() << " entries." << endl;
}


double candidateHitCombination::calculateS(basicHit aHit, basicHit refHit, TrackParameterXY tpXY)
{
    double s_xy = 0.;
    double hitPos[3];
    double refHitPos[3];

    hitPos[0] = aHit.getX();
    hitPos[1] = aHit.getY();
    hitPos[2] = aHit.getZ();

    refHitPos[0] = refHit.getX();
    refHitPos[1] = refHit.getY();
    refHitPos[2] = refHit.getZ();



    double phi = tpXY.getPhi();
    double dzero = tpXY.getDZero();
    double omega = tpXY.getOmega();

    if(!_isHelix)
    {
        s_xy = sqrt((hitPos[0] - refHitPos[0]) * (hitPos[0] - refHitPos[0]) +
                    (hitPos[1] - refHitPos[1]) * (hitPos[1] - refHitPos[1]));

        if((-1.25 * M_PI <= phi && phi <= -0.75 * M_PI) ||
                (-0.25 * M_PI <= phi && phi <= 0.25 * M_PI) ||
                (0.75 * M_PI <= phi && phi <= 1.25 * M_PI))
        {
            if(refHitPos[0] < hitPos[0])
            {
                s_xy = (-1.) * s_xy;
            }
        }
        else
        {
            if(refHitPos[1] < hitPos[1])
            {
                s_xy = (-1.) * s_xy;
            }
        }
        s_xy = -s_xy;//Not needed for Hough Transformation itself, but to make it look correctly on CEDViewer this needs to be here
    }
    else
    {
        //if curvature is zero calculate s as if track is a straight line
        if(omega != 0.)
        {
            double r = 1 / omega;

            //center of circle
            double xm, ym;
            xm = (r - dzero) * sin(phi);
            ym = -(r - dzero) * cos(phi);

            s_xy = r * (
                       atan2(refHitPos[1] - ym , refHitPos[0] - xm)
                       -
                       atan2(hitPos[1] - ym , hitPos[0] - xm)
                   );


            double s_xy_1, s_xy_2;

            s_xy_1 = s_xy;
            if(s_xy < 0)
            {
                s_xy_2 = s_xy + fabs(2 * M_PI / omega);
            }
            else
            {
                s_xy_2 = s_xy - fabs(2 * M_PI / omega);
            }

            if(fabs(s_xy_1) <= fabs(s_xy_2)) s_xy = s_xy_1;
            else s_xy = s_xy_2;

        }//if(omega != 0.)
        else
        {
            s_xy = sqrt(
                       (hitPos[0] - refHitPos[0]) * (hitPos[0] - refHitPos[0]) +
                       (hitPos[1] - refHitPos[1]) * (hitPos[1] - refHitPos[1]));

            if((-1.25 * M_PI <= phi && phi <= -0.75 * M_PI) ||
                    (-0.25 * M_PI <= phi && phi <= 0.25 * M_PI) ||
                    (0.75 * M_PI <= phi && phi <= 1.25 * M_PI))
            {
                if(refHitPos[0] < hitPos[0])
                {
                    s_xy = (-1.) * s_xy;
                }
            }
            else
            {
                if(refHitPos[1] < hitPos[1])
                {
                    s_xy = (-1.) * s_xy;
                }
            }
            s_xy = -s_xy;//Not needed for Hough Transformation itself, but to make it look correctly on CEDViewer this needs to be here

        }
    }

    //  cout<<"Hit Positions: "<<refHitPos[0]<<" "<<refHitPos[1]<<"   "<<hitPos[0]<<" "<<hitPos[1]<<"   "<<s_xy<<"   "<<2*M_PI/omega<<"   "<<fabs(fabs(s_xy) - fabs(2*M_PI/omega))<<endl;

    return s_xy;

}//double candidateHitCombination::claculateSxy(basicHit aHit, basicHit refHit, TrackParameterXY tpXY)

vector<candidateHit> candidateHitCombination::sortByZ(vector<candidateHit> unsortedHits)
{
    vector<candidateHit> sortedHits = unsortedHits;

    sort(sortedHits.begin(), sortedHits.end(), sortZ);

    return sortedHits;
}//vector<candidateHit> candidateHitCombination::sortByZ(vector<candidateHit> unsortedHits)
