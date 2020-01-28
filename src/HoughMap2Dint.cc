#include "HoughMap2Dint.h"
#include "RootFileWriter.h"
#include "ThetaToPhiConverter.h"
#include "DistanceHitTrackCalculator.h"
#include "HoughMapMaximumCandidateFinder.h"
#include "HoughSpaceAnalyzer.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;
using namespace pathfinder;

HoughMap2Dint::HoughMap2Dint(vector<basicHit> initialHits, FinderParameter FinderParameter)
{
    Map_Maximum = 0;
    Parameter = FinderParameter;
    initialBasicHits = initialHits;
    _useXY = true;

    trangexy = new HoughSpaceBinning(Parameter.getNumberXYThetaBins(), -M_PI, 0.);
    HoughMap2Dint::calculateDRangeXY();

    trackfound = HoughMap2Dint::fill();
}

HoughMap2Dint::HoughMap2Dint(vector<candidateHit> initialHits, FinderParameter FinderParameter)
{
    Map_Maximum = 0;
    Parameter = FinderParameter;
    initialCandidateHits = initialHits;
    _useXY = false;

    trangesz = new HoughSpaceBinning(FinderParameter.getNumberSZThetaBins(), -M_PI, 0.);
    HoughMap2Dint::calculateDRangeSZ();

    trackfound = HoughMap2Dint::fill();
}

bool HoughMap2Dint::fill()
{
    //if xy projection
    if(_useXY)
    {
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
        //      std::cout<<"New Hough Map: Vector sizes: "<<aVec.size()<<" "<<initialBasicHits.size()<<std::endl;
        //std::cout<<"Ranges: "<<drangexy->getLow()<<" "<<drangexy->getHigh()<<std::endl;
        //2.
        //do conversion of Hough Space Points to bin index and fill the Hough Map
        for(unsigned int iHit = 0; iHit < initialBasicHits.size(); iHit++)
        {
            double pos[2];
            pos[0] = initialBasicHits[iHit].getX();
            pos[1] = initialBasicHits[iHit].getY();
            for(vector<double>::iterator itera = aVec.begin(); itera < aVec.end(); itera++)
            {
                double tmpD = cos(*itera) * pos[0] + sin(*itera) * pos[1];
                HoughSpacePoint* tmpPoint = new HoughSpacePoint((*itera), tmpD, *trangexy, *drangexy);

                if(tmpD > drangexy->getLow() && tmpD < drangexy->getHigh())
                {
                    ++HoughMapInt[tmpPoint->getIndex()];
                }
                delete tmpPoint;
            }
        }
        //      cout<<"Size of xy Hough Map: "<<HoughMapInt.size()<<endl;
        if(Parameter.getSaveRootFile() == true)
        {
            HoughSpaceAnalyzer Analyzer(HoughMapInt, *trangexy, *drangexy);
            Analyzer.Analyze();
            Analyzer.WriteRootFile("IntersectionHoughSpace.root");
            Analyzer.WritePdfFile("IntersectionHoughSpace.pdf");
            cout << "Hough space was written to file IntersectionHoughSpace.root" << endl;
            /*
                  RootFileWriter Writer1;
                  bool FileDoesNotExists1;
                  FileDoesNotExists1 = Writer1.writeRootFile(&HoughMapInt, "XYLinearHoughMap_test1.root");
                  if(!FileDoesNotExists1)
                  {
                      Writer1.writeRootFile(&HoughMapInt, "XYLinearHoughMap_test2.root");

                  }
            */
        }

    }//if(_useXY)


    //if sz projection
    else
    {
        /*
        1. calculate bins for theta
        2. fill HoughMap for all Hits
        3. rounding of the calculated d0 to create a binning in this direction
             */


        //1.
        vector<double> aVec;
        for(float a = trangesz->getLow(); a <= trangesz->getHigh(); a += trangesz->getBinWidth())
            //            for(float a = (-1) * M_PI; a <= 0.; a +=  M_PI / Parameter.getNumberSZThetaBins())
        {
            aVec.push_back(a);
        }



        //do conversion of Hough Space Points to bin index and fill the Hough Map
        for(unsigned int iHit = 0; iHit < initialCandidateHits.size(); iHit++)
        {
            double pos[2];
            pos[0] = initialCandidateHits[iHit].getS();
            pos[1] = initialCandidateHits[iHit].getZ();
            for(vector<double>::iterator itera = aVec.begin(); itera < aVec.end(); itera++)
            {

                double tmpD = cos(*itera) * pos[0] + sin(*itera) * pos[1];
                HoughSpacePoint* tmpPoint = new HoughSpacePoint((*itera), tmpD, *trangesz, *drangesz);

                if(tmpD > drangesz->getLow() && tmpD < drangesz->getHigh())
                {
                    ++HoughMapInt[tmpPoint->getIndex()];
                }
                delete tmpPoint;
            }
        }
        //            cout<<"Size of sz Hough Map: "<<HoughMapInt.size()<<endl;
        if(Parameter.getSaveRootFile() == true)
        {
            RootFileWriter Writer1;
            bool FileDoesNotExists1;
            FileDoesNotExists1 = Writer1.writeRootFile(&HoughMapInt, "SZLinearHoughMap_test1.root");
            if(!FileDoesNotExists1)
            {
                Writer1.writeRootFile(&HoughMapInt, "SZLinearHoughMap_test2.root");

            }
        }

    }//else

    if(HoughMapInt.size() != 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}//bool 2DHoughMap::fill





HoughMaximum2D* HoughMap2Dint::findMaximum()
{

    //if xy projection
    if(_useXY)
    {
        //using new class HoughMapMaximumCandidateFinder to find maxima in Hough map
        HoughMapMaximumCandidateFinder* maxCandidateFinder = new HoughMapMaximumCandidateFinder(HoughMapInt, trangexy, drangexy, false, Parameter.getSearchNeighborhood());
        vector<HoughMaximum2D> MapMaximumVec = maxCandidateFinder->getMaximumCandidates();
        delete maxCandidateFinder;

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

    }//if(_useXY)

    //if sz projection
    else
    {
        //using new class HoughMapMaximumCandidateFinder to find maxima in Hough map
        HoughMapMaximumCandidateFinder* maxCandidateFinder = new HoughMapMaximumCandidateFinder(HoughMapInt, trangesz, drangesz, false, Parameter.getSearchNeighborhood());
        vector<HoughMaximum2D> MapMaximumVec = maxCandidateFinder->getMaximumCandidates();
        delete maxCandidateFinder;

        double _maxDistanceToTrack = Parameter.getMaxSZDistance();

        int nhits = 0;
        for(unsigned int i = 0; i < MapMaximumVec.size(); i++)
        {
            double trackDZero = (MapMaximumVec.at(i)).getSecond();

            ThetaToPhiConverter* angleConverter = new ThetaToPhiConverter(&(MapMaximumVec.at(i)));
            double trackPhi = angleConverter->getPhi();
            delete angleConverter;

            int hitCounter = 0;
            for(unsigned int iHit = 0; iHit < initialCandidateHits.size(); iHit++)
            {
                DistanceHitTrackCalculator* distanceCalculator = new DistanceHitTrackCalculator(&initialCandidateHits.at(iHit), trackPhi, trackDZero);

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
    }


    return Map_Maximum;
}//2DHoughMaximum 2DHoughMap::findMaximum


void HoughMap2Dint::calculateDRangeXY()
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
        double pos[2];
        pos[0] = initialBasicHits[iHit].getX();
        pos[1] = initialBasicHits[iHit].getY();
        for(vector<double>::iterator itert = thetaVec.begin(); itert < thetaVec.end(); itert++)
        {
            pair<double, double> temppair;
            temppair.first = *itert;
            temppair.second = cos(*itert) * pos[0] + sin(*itert) * pos[1];

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

}//HoughMap2Dint::calculateDRangeXY()


void HoughMap2Dint::calculateDRangeSZ()
{
    double maxD = Parameter.getMaxDsz() + Parameter.getMaxDsz() / 4.;
    double minD = (-1.) * Parameter.getMaxDsz() - Parameter.getMaxDsz() / 4.;

    std::pair<double, double> dzeroRange;
    dzeroRange.first = 100000000.;
    dzeroRange.second = -100000000.;

    vector<double> thetaVec;
    for(float t1 = trangesz->getLow(); t1 <= trangesz->getHigh(); t1 += trangesz->getBinWidth())
    {
        thetaVec.push_back(t1);
    }

    for(unsigned int iHit = 0; iHit < initialCandidateHits.size() - 1; iHit++)
    {
        double pos[2];
        pos[0] = initialCandidateHits[iHit].getS();
        pos[1] = initialCandidateHits[iHit].getZ();
        for(vector<double>::iterator itert = thetaVec.begin(); itert < thetaVec.end(); itert++)
        {
            pair<double, double> temppair;
            temppair.first = *itert;
            temppair.second = cos(*itert) * pos[0] + sin(*itert) * pos[1];

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

    drangesz = new HoughSpaceBinning(Parameter.getNumberSZDzeroBins(), dzeroRange);

}//HoughMap2Dint::calculateDRange()

void HoughMap2Dint::print() const
{
    map<int, unsigned int>::const_iterator mapIter;

    cout << "Key:      Value:" << endl;
    for(mapIter = HoughMapInt.begin(); mapIter != HoughMapInt.end(); mapIter++)
    {
        cout << (*mapIter).first << " " << (*mapIter).second << endl;
    }
}//void 2DHoughMap::print()
