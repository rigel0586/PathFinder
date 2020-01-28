#include "HoughMap2DCircleint.h"
#include "RootFileWriter.h"
#include "ThetaToPhiConverter.h"
#include "DistanceHitTrackCalculator.h"
#include "HoughMapMaximumCandidateFinder.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;
using namespace pathfinder;

HoughMap2DCircleint::HoughMap2DCircleint(vector<basicHit> initialHits, FinderParameter FinderParameter)
{
    Map_Maximum = 0;
    Parameter = FinderParameter;
    initialBasicHits = initialHits;

    trangexy = new HoughSpaceBinning(FinderParameter.getNumberXYThetaBins(), -M_PI, 0.);
    HoughMap2DCircleint::calculateDRangeXY();

    trackfound = HoughMap2DCircleint::fill();
}

bool HoughMap2DCircleint::fill()
{
    //if xy projection
    /*
      1. calculate bins for theta
      2. fill HoughMap for all Hits
      3. rounding of the calculated d0 to create a binning in this direction
    */

    //1.
    vector<double> aVec;
    for(float a = trangexy->getLow(); a <= trangexy->getHigh(); a += trangexy->getBinWidth())
    {
        aVec.push_back(a);
    }

    //do conversion of Hough Space Points to bin index and fill the Hough Map
    //for(unsigned int bins = 0; bins < Bins.size(); bins++)
    for(unsigned int iHit = 0; iHit < initialBasicHits.size(); iHit++)
    {
        double pos[2];
        pos[0] = initialBasicHits[iHit].getX();
        pos[1] = initialBasicHits[iHit].getY();

        //conformal mapping, asume vertex at (0,0,0)
        double cmpos[2];
        double r2 = pos[0] * pos[0] + pos[1] * pos[1];
        cmpos[0] = pos[0] / r2;
        cmpos[1] = -1 * pos[1] / r2;

        for(vector<double>::iterator itera = aVec.begin(); itera < aVec.end(); itera++)
        {
            double tmpD = cos(*itera) * cmpos[0] + sin(*itera) * cmpos[1];
            HoughSpacePoint* tmpPoint = new HoughSpacePoint((*itera), tmpD, *trangexy, *drangexy);
            if(tmpD > drangexy->getLow() && tmpD < drangexy->getHigh())
            {
                ++HoughMapInt[tmpPoint->getIndex()];
            }
            delete tmpPoint;
        }
    }


    if(Parameter.getSaveRootFile() == true)
    {
        RootFileWriter Writer1;
        bool FileDoesNotExists1 = Writer1.writeRootFile(&HoughMapInt, "XYLinearHoughMap_test1.root");
        if(!FileDoesNotExists1)
        {
            Writer1.writeRootFile(&HoughMapInt, "XYLinearHoughMap_test2.root");
        }


    }

    if(HoughMapInt.size() != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}//bool 2DHoughMap::fill





HoughMaximum2D* HoughMap2DCircleint::findMaximum()
{
    //using new class HoughMapMaximumCandidateFinder to find maxima in Hough map
    HoughMapMaximumCandidateFinder* maxCandidateFinder = new HoughMapMaximumCandidateFinder(HoughMapInt, trangexy, drangexy, false, Parameter.getSearchNeighborhood());
    vector<HoughMaximum2D> MapMaximumVec = maxCandidateFinder->getMaximumCandidates();
    delete maxCandidateFinder;

    //Find the correct maximum by counting how many hits can be assigned to the track
    double _maxDistanceToTrack = Parameter.getMaxXYDistance();

    int nhits = 0;

    for(unsigned int i = 0; i < MapMaximumVec.size(); i++)
    {
        double trackDZero = (MapMaximumVec.at(i)).getSecond();
        ThetaToPhiConverter* angleConverter = new ThetaToPhiConverter(&MapMaximumVec.at(i));
        double trackPhi = angleConverter->getPhi();
        delete angleConverter;

        int hitCounter = 0;
        for(unsigned int iHit = 0; iHit < initialBasicHits.size(); iHit++)
        {
            DistanceHitTrackCalculator* distanceCalculator = new DistanceHitTrackCalculator(&initialBasicHits.at(iHit), trackPhi, trackDZero);

            double distance = distanceCalculator->getDistance();

            if(distance < _maxDistanceToTrack)
            {
                hitCounter++;
            }
            delete distanceCalculator;
        }//for(unsigned int iHit = 0; iHit<initialHits.size(); iHit++)

        if(hitCounter >= nhits)
        {
            Map_Maximum = new HoughMaximum2D(MapMaximumVec.at(i));
            nhits = hitCounter;
        }

    }//for(unsigned int i = 0; i< MapMaximumVec.size();i++)

    //9.
    return Map_Maximum;
}//2DHoughMaximum 2DHoughMap::findMaximum

void HoughMap2DCircleint::calculateDRangeXY()
{
    double maxD = Parameter.getMaxDxy() + Parameter.getMaxDxy() / 4.;
    double minD = (-1.) * Parameter.getMaxDxy() - Parameter.getMaxDxy() / 4.;

    std::pair<double, double> dzeroRange;
    dzeroRange.first = 100000000.;
    dzeroRange.second = -100000000.;

    vector<double> thetaVec;
    for(float t1 = trangexy->getLow(); t1 <= trangexy->getHigh(); t1 += trangexy->getBinWidth())
    {
        thetaVec.push_back(t1);
    }

    for(unsigned int iHit = 0; iHit < initialBasicHits.size() - 1; iHit++)
    {
        //cout<<"loop 1 over hit "<<iHit<<endl;
        double pos[2];
        pos[0] = initialBasicHits[iHit].getX();
        pos[1] = initialBasicHits[iHit].getY();

        double cmpos[2];
        double r2 = pos[0] * pos[0] + pos[1] * pos[1];
        cmpos[0] = pos[0] / r2;
        cmpos[1] = -1 * pos[1] / r2;

        for(vector<double>::iterator itert = thetaVec.begin(); itert < thetaVec.end(); itert++)
        {
            pair<double, double> temppair;
            temppair.first = *itert;
            temppair.second = cos(*itert) * cmpos[0] + sin(*itert) * cmpos[1];

            if(temppair.second > minD && temppair.second < maxD)
            {

                if(temppair.second > dzeroRange.second)
                {
                    dzeroRange.second = temppair.second;
                }
                if(temppair.second < dzeroRange.first)
                {
                    dzeroRange.first = temppair.second;
                }
            }//if(temppair.second>-4000. && temppair.second<4000.)
        }
    }//for(unsigned int iHit = 0; iHit< allHits_copy.size() - 1; iHit++)

    drangexy = new HoughSpaceBinning(Parameter.getNumberXYDzeroBins(), dzeroRange);

}//void HoughMap2DCircleint::calculateDRangeXY()

void HoughMap2DCircleint::print() const
{
    map<int, unsigned int>::const_iterator mapIter;

    cout << "Key:      Value:" << endl;
    for(mapIter = HoughMapInt.begin(); mapIter != HoughMapInt.end(); mapIter++)
    {
        cout << (*mapIter).first << " " << (*mapIter).second << endl;
    }
}//void 2DHoughMap::print()
